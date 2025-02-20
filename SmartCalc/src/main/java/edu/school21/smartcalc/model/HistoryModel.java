package edu.school21.smartcalc.model;

import org.springframework.stereotype.Component;

import java.io.*;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;

@Component
public class HistoryModel {
    private static final Path HISTORY_FILE = Paths.get(System.getProperty("user.dir"), "history.txt");
    private final List<String> history = new ArrayList<>();

    public HistoryModel() {
        createFileIfNotExist();
        loadHistoryFromFile();
    }

    public void addRecord(String record) {
        if (!isDuplicate(record)) {
            history.add(record);
            saveHistoryToFile();
        }
    }

    private boolean isDuplicate(String record) {
        return record.trim().isEmpty() || history.contains(record);
    }

    public List<String> getHistory() {
        return new ArrayList<>(history);
    }

    public void clearHistory() {
        history.clear();
        saveHistoryToFile();
    }

    public void saveHistoryToFile() {
        try (BufferedWriter writer = Files.newBufferedWriter(HISTORY_FILE)) {
            for (String record : history) {
                writer.write(record);
                writer.newLine();
            }
        } catch (IOException e) {
            System.err.println("Error saving history to file: " + e.getMessage());
        }
    }

    private void loadHistoryFromFile() {
        if (!Files.exists(HISTORY_FILE)) {
            System.out.println("No history file found");
            return;
        }
        try (BufferedReader reader = Files.newBufferedReader(HISTORY_FILE)) {
            String line;
            while ((line = reader.readLine()) != null) {
                history.add(line);
            }
        } catch (IOException e) {
            System.err.println("Error loading history from file: " + e.getMessage());
        }
    }

    private void createFileIfNotExist() {
        if (!Files.exists(HISTORY_FILE)) {
            try {
                Files.createFile(HISTORY_FILE);
                System.out.println("History file created: " + HISTORY_FILE);
            } catch (IOException e) {
                System.err.println("Error creating history file: " + e.getMessage());
            }
        }
    }
}
