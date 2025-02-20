package edu.school21.sockets.repositories;

import edu.school21.sockets.models.ChatRoom;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;
import java.sql.Types;
import java.util.List;
import java.util.Optional;

@Repository
public class ChatRoomsRepositoryImpl implements ChatRoomsRepository {

    private final JdbcTemplate jdbcTemplate;

    @Autowired
    public ChatRoomsRepositoryImpl(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }
    
    @Override
    public Optional<ChatRoom> findById(Long id) {
        ChatRoom chatRoom = jdbcTemplate.query("SELECT * FROM chat.chatroom WHERE id=?",
                new Object[]{id},
                new int[]{Types.INTEGER},
                new BeanPropertyRowMapper<>(ChatRoom.class)).stream().findAny().orElse(null);
        return Optional.ofNullable(chatRoom);
    }

    @Override
    public List<ChatRoom> findAll() {
        return jdbcTemplate.query("SELECT * FROM chat.chatroom",
                new BeanPropertyRowMapper<>(ChatRoom.class));
    }

    @Override
    public void save(ChatRoom chatRoom) {
        int result = jdbcTemplate.update("INSERT INTO chat.chatroom(name, owner, password) VALUES(?, ?, ?)",
                chatRoom.getName(),
                chatRoom.getOwner(),
                chatRoom.getPassword());
        if(result == 0) {
            System.err.println("Entity hasn't saved");
        }
    }

    @Override
    public void update(ChatRoom chatRoom) {
        if(chatRoom == null || chatRoom.getId() == null) {
            System.err.println("Entity doesn't exist for these parameters");
        }

        assert chatRoom != null;
        int result = jdbcTemplate.update("UPDATE chat.chatroom SET name = ?, owner = ?, password = ? WHERE id = ?",
                chatRoom.getName(),
                chatRoom.getOwner(),
                chatRoom.getPassword(),
                chatRoom.getId());

        if(result == 0) {
            System.err.println("Entity hasn't downloaded");
        }
    }

    @Override
    public void delete(Long id) {
        int result = jdbcTemplate.update("DELETE FROM chat.chatroom WHERE id = ?", id);
        if(result == 0) {
            System.err.println("Entity hasn't downloaded");
        }
    }
}
