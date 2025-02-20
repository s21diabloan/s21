package edu.school21.sockets.models;

import lombok.Getter;
import lombok.Setter;

import java.time.LocalDateTime;

@Getter
@Setter
public class Message {
    private Long ownerId;
    private Long chatId;
    private String sender;
    private String text;
    private LocalDateTime timestamp;

    public Message() {
    }

    public Message(String messageText, String sender, Long chatId) {
        this.text = messageText;
        this.sender = sender;
        this.chatId = chatId;
        this.timestamp = LocalDateTime.now();
    }
}