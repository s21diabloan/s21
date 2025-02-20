package edu.school21.sockets.services;

import edu.school21.sockets.models.ChatRoom;
import java.util.List;

public interface RoomService {
    boolean saveRoom(String name, String password, Long ownerId);
    boolean signIn(Long id, String password);
    List<ChatRoom> findAll();
}