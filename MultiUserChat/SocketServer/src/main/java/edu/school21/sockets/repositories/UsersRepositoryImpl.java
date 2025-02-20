package edu.school21.sockets.repositories;

import edu.school21.sockets.models.User;
import org.springframework.beans.factory.ObjectProvider;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Repository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Optional;

@Repository
public class UsersRepositoryImpl implements UsersRepository {

    private static final Logger logger = LoggerFactory.getLogger(UsersRepositoryImpl.class);

    private final JdbcTemplate jdbcTemplate;
    private final PasswordEncoder passwordEncoder;
    private final ObjectProvider<User> userProvider;

    public UsersRepositoryImpl(JdbcTemplate jdbcTemplate, PasswordEncoder passwordEncoder,
                               ObjectProvider<User> userProvider) {
        this.jdbcTemplate = jdbcTemplate;
        this.passwordEncoder = passwordEncoder;
        this.userProvider = userProvider;
    }

    @Override
    public Optional<User> findByUsername(String username) {
        try {
            User user = jdbcTemplate.queryForObject(
                    "SELECT * FROM chat.users WHERE username = ?",
                    (rs, rowNum) -> mapResultSetToUser(rs),
                    username
            );
            return Optional.ofNullable(user);
        } catch (EmptyResultDataAccessException e) {
            logger.error("User not found with username: {}", username);
            return Optional.empty();
        } catch (Exception e) {
            logger.error("Error finding user by username: {}", username, e);
            return Optional.empty();
        }
    }

    @Override
    public void save(User user) {
        if (user.getId() == null) {
            jdbcTemplate.update(
                    "INSERT INTO chat.users (username, password) VALUES (?, ?)",
                    user.getUsername(),
                    user.getPassword()
            );
        } else {
            jdbcTemplate.update(
                    "UPDATE chat.users SET username = ?, password = ? WHERE id = ?",
                    user.getUsername(),
                    user.getPassword(),
                    user.getId()
            );
        }
    }

    @Override
    public Optional<User> findById(Long id) {
        try {
            User user = jdbcTemplate.queryForObject(
                    "SELECT * FROM chat.users WHERE id = ?",
                    (rs, rowNum) -> mapResultSetToUser(rs),
                    id
            );
            assert user != null;
            return Optional.of(user);
        } catch (Exception e) {
            return Optional.empty();
        }
    }

    @Override
    public void update(User user) {
        jdbcTemplate.update(
                "UPDATE chat.users SET username = ?, password = ? WHERE id = ?",
                user.getUsername(),
                passwordEncoder.encode(user.getPassword()),
                user.getId()
        );
    }

    @Override
    public void delete(Long id) {
        jdbcTemplate.update("DELETE FROM chat.users WHERE id = ?", id);
    }

    @Override
    public Iterable<User> findAll() {
        return jdbcTemplate.query("SELECT * FROM chat.users", (rs, rowNum) -> mapResultSetToUser(rs));
    }

    private User mapResultSetToUser(ResultSet rs) throws SQLException {
        User user = userProvider.getObject();
        user.setId(rs.getLong("id"));
        user.setUsername(rs.getString("username"));
        user.setPassword(rs.getString("password"));
        return user;
    }
}