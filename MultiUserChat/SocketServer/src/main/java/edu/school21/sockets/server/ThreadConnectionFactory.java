package edu.school21.sockets.server;

import edu.school21.sockets.services.RoomService;
import edu.school21.sockets.services.UsersService;
import edu.school21.sockets.services.MessagesService;
import org.springframework.stereotype.Component;

import java.io.IOException;
import java.net.Socket;

@Component
public class ThreadConnectionFactory {

    public ThreadConnection create(Socket socket, UsersService usersService, MessagesService messagesService, RoomService roomService) throws IOException {
        return new ThreadConnection(socket, usersService, messagesService, roomService);
    }
}