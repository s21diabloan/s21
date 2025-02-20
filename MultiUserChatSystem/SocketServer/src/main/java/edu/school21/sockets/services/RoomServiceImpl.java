package edu.school21.sockets.services;


import edu.school21.sockets.models.ChatRoom;
import edu.school21.sockets.repositories.ChatRoomsRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Optional;

@Component
public class RoomServiceImpl implements RoomService {

    private final ChatRoomsRepository chatRoomsRepository;
    private final PasswordEncoder passwordEncoder;

    @Autowired
    public RoomServiceImpl(ChatRoomsRepository chatRoomsRepository, PasswordEncoder passwordEncoder) {
        this.chatRoomsRepository = chatRoomsRepository;
        this.passwordEncoder = passwordEncoder;
    }

    @Override
    public boolean saveRoom(String name, String password, Long ownerId) {
        ChatRoom chatRoom = new ChatRoom(name, ownerId, password);
        if (password!=null) {
        chatRoom.setPassword(passwordEncoder.encode(chatRoom.getPassword()));}
        chatRoomsRepository.save(chatRoom);
        return true;
    }

    @Override
    public boolean signIn(Long id, String password) {
        Optional<ChatRoom> chatRoom = chatRoomsRepository.findById(id);
        if (!chatRoom.isPresent()) {
            System.err.println("ChatRoom with id " + id + " not found.");
            return false;
        }
        return passwordEncoder.matches(password, chatRoom.get().getPassword());
    }


    @Override
    public List<ChatRoom> findAll() {
        return (List<ChatRoom>) chatRoomsRepository.findAll();
    }
}