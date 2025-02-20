package edu.school21.sockets.models;

import lombok.Getter;
import lombok.Setter;

@Setter
@Getter
public class User {

    private Long id;
    private String username;
    private String password;

    public User() {}

    public User(Long id, String username, String password) {
        this.id = id;
        this.username = username;
        this.password = password;
    }

}