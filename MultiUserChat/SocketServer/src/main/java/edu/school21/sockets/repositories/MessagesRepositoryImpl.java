package edu.school21.sockets.repositories;

import edu.school21.sockets.models.Message;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;
import java.util.List;
import java.util.Optional;

@Repository
public class MessagesRepositoryImpl implements MessagesRepository {

    private final JdbcTemplate jdbcTemplate;

    public MessagesRepositoryImpl(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    @Override
    public void save(Message message) {
        jdbcTemplate.update(
                "INSERT INTO chat.messages (sender, text, timestamp, chatId) VALUES (?, ?, ?,?)",
                message.getSender(),
                message.getText(),
                message.getTimestamp(),
                message.getChatId()
        );
    }

    @Override
    public Optional<Message> findById(Long id) {
        return Optional.empty();
    }

    @Override
    public void update(Message entity) {

    }

    @Override
    public void delete(Long id) {

    }

    @Override
    public Iterable<Message> findAll() {
        return null;
    }

    @Override
    public List<Message> loadMessages(Long chatId) {
        String sql =
                "SELECT * " +
                        "FROM ( " +
                        "    SELECT * " +
                        "    FROM chat.messages " +
                        "    WHERE chatId = ? " +
                        "    ORDER BY timestamp DESC " +
                        "    LIMIT 30 " +
                        ") subquery " +
                        "ORDER BY timestamp ASC";

        return jdbcTemplate.query(
                sql,
                new Object[]{chatId},
                new BeanPropertyRowMapper<>(Message.class)
        );
    }
}