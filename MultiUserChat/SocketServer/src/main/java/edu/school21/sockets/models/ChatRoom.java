package edu.school21.sockets.models;

import lombok.Data;
import lombok.ToString;

@Data
@ToString
public class ChatRoom {

    public ChatRoom() {
    }
    private Long id;
    private String name;
    private Long owner;
    private String password;

    public ChatRoom(String name, Long owner, String password) {
        this.name = name;
        this.owner = owner;
        this.password = password;
    }
}