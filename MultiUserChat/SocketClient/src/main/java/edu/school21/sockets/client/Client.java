package edu.school21.sockets.client;

import edu.school21.sockets.serialization.JsonConverter;

import java.io.*;
import java.net.Socket;
import java.util.Objects;
import java.util.Scanner;

public class Client {
    private Scanner reader;
    private Scanner bufferedReader;
    private BufferedWriter bufferedWriter;
    private volatile boolean exit = false;
    private final String serverAddress;

    public Client(String serverAddress) {
        this.serverAddress = serverAddress;
    }

    public void start(int port) {
        try (Socket socket = new Socket(serverAddress, port);
             Scanner bufferedReader = new Scanner(socket.getInputStream());
             BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()))) {
            this.reader = new Scanner(System.in);
            this.bufferedReader = bufferedReader;
            this.bufferedWriter = bufferedWriter;
            getMessageFromServer();

        } catch (IOException ioException) {
            System.out.println("Error: " + ioException.getMessage());
            System.exit(-1);
        }
    }

        private void getMessageFromServer() throws IOException {
            WriteMsg threadWrite = new WriteMsg();
            threadWrite.start();
            String serverMessage = null;
            do {
                if (bufferedReader.hasNextLine()) {
                    serverMessage = Objects.requireNonNull(JsonConverter.
                            parseStringToObject(bufferedReader.nextLine())).getMessageText();
                        System.out.print("\r" + "  " + "\r");
                        System.out.println(serverMessage);
                        if (!serverMessage.equals("You have left the chat.")) {
                            System.out.print("> ");
                        } else {
                            threadWrite.terminate();
                            System.exit(0);
                        }
                    }
                }
                while (!Objects.equals(serverMessage, "You have left the chat.")) ;
            }

    private class WriteMsg extends Thread {
        @Override
        public void run() {
            while (!exit) {
                try {
                    String message = reader.nextLine();
                    bufferedWriter.write(Objects.requireNonNull(JsonConverter.makeJSON(message)));
                    bufferedWriter.newLine();
                    bufferedWriter.flush();
                } catch (IOException e) {
                    System.out.println("Error: " + e.getMessage());
                }
            }
        }
        public void terminate() { exit = true; }
    }
}