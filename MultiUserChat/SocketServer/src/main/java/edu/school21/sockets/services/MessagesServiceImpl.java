package edu.school21.sockets.services;

import edu.school21.sockets.models.Message;
import edu.school21.sockets.repositories.MessagesRepository;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class MessagesServiceImpl implements MessagesService {

    private final MessagesRepository messagesRepository;
    public MessagesServiceImpl(MessagesRepository messagesRepository) {
        this.messagesRepository = messagesRepository;
    }

    @Override
    public void saveMessage(String messageText, Long chatId, String sender) {
        Message message = new Message(messageText, sender, chatId);
        messagesRepository.save(message);
    }

    @Override
    public List<Message> loadMessages(Long chatId) {
        return messagesRepository.loadMessages(chatId);
    }
}