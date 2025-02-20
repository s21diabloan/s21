package edu.school21.sockets.services;

import edu.school21.sockets.models.Message;

import java.util.List;

public interface MessagesService {
    void saveMessage(String message, Long chatId, String sender);
    List<Message> loadMessages(Long chatId);
}