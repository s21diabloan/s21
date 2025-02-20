package edu.school21.sockets.serialization;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.datatype.jsr310.JavaTimeModule;
import lombok.Data;

import java.time.LocalDateTime;

@Data
public class JsonConverter {
    private String messageText;
    private LocalDateTime dateTime;

    private static final ObjectMapper OBJECT_MAPPER = new ObjectMapper().registerModule(new JavaTimeModule());

    public JsonConverter(String messageText) {
        this.messageText = messageText;
        this.dateTime = LocalDateTime.now();
    }

    public JsonConverter() {
    }

    public static JsonConverter parseStringToObject(String msg) {
        if (msg == null || msg.trim().isEmpty()) {
            System.err.println("Input string is null or empty.");
            return null;
        }
        try {
            return OBJECT_MAPPER.readValue(msg, JsonConverter.class);
        } catch (JsonProcessingException e) {
            System.err.println("Error parsing JSON: " + e.getMessage());
            return null;
        }
    }

    public static String makeJSON(String msg) {
        try {
            JsonConverter jsonConverter = new JsonConverter(msg);
            return OBJECT_MAPPER.writeValueAsString(jsonConverter);
        } catch (JsonProcessingException e) {
            System.err.println("Error creating JSON: " + e.getMessage());
            return null;
        }
    }
}