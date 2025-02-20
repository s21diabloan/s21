package edu.school21.sockets.server;

import edu.school21.sockets.serialization.JsonConverter;
import edu.school21.sockets.models.ChatRoom;
import edu.school21.sockets.models.Message;
import edu.school21.sockets.services.MessagesService;
import edu.school21.sockets.services.UsersService;
import edu.school21.sockets.services.RoomService;
import lombok.Getter;
import org.springframework.dao.EmptyResultDataAccessException;

import java.io.*;
import java.net.Socket;
import java.net.SocketException;
import java.util.List;
import java.util.Objects;

public class ThreadConnection extends Thread {
    private final Socket socket;
    private final UsersService usersService;
    private final RoomService roomService;

    private final MessagesService messagesService;
    private final BufferedReader bufferedReader;
    private final BufferedWriter bufferedWriter;
    private String username;
    private boolean isFinished;
    @Getter
    private Long chatId = 0L;

    public ThreadConnection(Socket socket, UsersService usersService,
                            MessagesService messagesService, RoomService roomService) throws IOException {
        this.socket = socket;
        this.usersService = usersService;
        this.messagesService = messagesService;
        this.roomService = roomService;
        this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        this.isFinished = false;
    }

    @Override
    public void run() {
        System.out.println("Client connected: " + socket.getInetAddress());
        try {
            while (!isFinished) {
                serverMenu();
                getClientAction();
            }
        } catch (IOException | EmptyResultDataAccessException | NullPointerException ex) {
            System.err.println("Error while closing connection: " + ex.getMessage());
        } finally {
            try {
                refuseConnection();
            } catch (IOException e) {
                System.err.println("Error while closing connection: " + e.getMessage());
            }
        }
    }

    private void serverMenu() throws IOException {
        sendMessageClient("Hello from Server!");
        sendMessageClient("1. SignIn");
        sendMessageClient("2. SignUp");
        sendMessageClient("3. Exit");
    }

    private void getClientAction() throws IOException {
        String clientResponse = Objects.requireNonNull(JsonConverter
                .parseStringToObject(bufferedReader.readLine())).getMessageText();
        if (clientResponse != null) {
            switch (clientResponse.toLowerCase()) {
                case "2":
                    signUp();
                    break;
                case "1":
                    signIn();
                    break;
                case "3":
                    refuseConnection();
                    break;
                default:
                    sendMessageClient("Unknown command: " + clientResponse);
            }
        }
    }

    private void startMessaging() {
        try {
            List<Message> messages = messagesService.loadMessages(chatId);

            for(Message message : messages) {
                String username = message.getSender();
                sendMessageClient(username + ": " + message.getText());
            }
            String message;
            while (!(message = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText())
                    .equalsIgnoreCase("exit")) {
                messagesService.saveMessage(message, chatId, username);
                Server.sendMessageToChat(message, username, this);
            }
            refuseConnection();
        } catch (IOException ioException) {
            System.err.println("Error while reading messages1: " + ioException.getMessage());
        }
    }



    private void signUp() throws IOException {
        try {
            sendMessageClient("Enter username:");
            username = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
            sendMessageClient("Enter password:");
            String password = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
            if (username == null || username.isEmpty() || password == null || password.isEmpty()) {
                sendMessageClient("Invalid data for signUp.");
            } else {
                if (!usersService.signUp(username, password)) {
                    sendMessageClient("Failed! User with this login already exists.");
                } else {
                    sendMessageClient("Successful!");
                }
            }
        } catch (IOException ioException) {
            System.out.println("Error: " + ioException.getMessage());
            refuseConnection();
        }
    }

    private void signIn() throws IOException {
        try {
            sendMessageClient("Enter username:");
            username = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
            sendMessageClient("Enter password:");
            String password = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
            if((usersService.signIn(username, password))) {
                roomMenu();
            } else {
                sendMessageClient("Failed!");
            }
        } catch (IOException e) {
            System.err.println("Error while signing in: " + e.getMessage());
        } catch (IllegalArgumentException e) {
            sendMessageClient("Invalid username");
            System.err.println("Error while signing in: " + e.getMessage());
        }

    }

    void sendMessageClient(String message) throws IOException {
        try {
            String jsonMessage = JsonConverter.makeJSON(message);
            assert jsonMessage != null;
            bufferedWriter.write(jsonMessage);
            bufferedWriter.newLine();
            bufferedWriter.flush();
        } catch (SocketException e) {
            System.out.println("Client disconnected unexpectedly: " + e.getMessage());
            try {
                refuseConnection();
            } catch (IOException ioException) {
                System.err.println("Error closing connection: " + ioException.getMessage());
            }
        } catch (IOException e) {
            System.err.println("Error while reading messages2: " + e.getMessage());
            refuseConnection();
        }
    }

    void refuseConnection() throws IOException {
        try {
            if (Server.removeConnection(this)) {
                sendMessageClient("You have left the chat.");///!!!!
                bufferedReader.close();
                bufferedWriter.close();
                socket.close();
                System.out.println("Connection closed: " + socket.getInetAddress());
            }
        } catch (IOException ioException) {
            System.err.println("Error during connection closure: " + ioException.getMessage());
        } finally {
            isFinished = true;
        }
    }

    private void roomMenu() throws IOException {
        sendMessageClient("1.       Create room");
        sendMessageClient("2.       Choose room");
        sendMessageClient("3.       Exit");

        String clientWord = Objects.requireNonNull(JsonConverter.
                parseStringToObject(bufferedReader.readLine())).getMessageText();
        if (clientWord != null) {
            switch (clientWord) {
                case "1":
                    createRoom();
                    break;
                case "2":
                    chooseRoomMenu();
                    break;
                case "3":
                    refuseConnection();
                    break;
                default:
                    sendMessageClient("Invalid option. Please choose again.");
                    roomMenu();
            }
        }
    }

    private void createRoom() {
        try {
            sendMessageClient("Enter room name:");
            String roomName = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
            if (roomName == null || roomName.isEmpty()) {
                sendMessageClient("Wrong data for creating room");
                return;
            }
            sendMessageClient("Create a password, enter y/n ? ");
            String clientWord = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
            String password;
            Long userId = 1L;
            if(clientWord.equalsIgnoreCase("Yes") || clientWord.equalsIgnoreCase("y")) {
                sendMessageClient("Enter room password:");
                password = Objects.requireNonNull(JsonConverter.parseStringToObject(bufferedReader.readLine())).getMessageText();
                if (password == null) {
                    sendMessageClient("Wrong password!");
                } else {
                    if(roomService.saveRoom(roomName, password, userId)) {
                        sendMessageClient("Successful!");
                        chooseRoomMenu();
                    } else {
                        sendMessageClient("Failed! Chat with this name already exists");
                    }
                }
            } else {
                password = null;
                if(roomService.saveRoom(roomName, password, userId)) {
                    sendMessageClient("Successful!");
                    chooseRoomMenu();
                } else {
                    sendMessageClient("Failed! Chat with this name already exists");
                }
            }
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    private void chooseRoomMenu() {
        try {
            int count = 0;
            List<ChatRoom> chatRoomList = roomService.findAll();
            if (chatRoomList == null) {
                sendMessageClient("There are no any rooms!");
            } else {
                sendMessageClient("Rooms:");
                for(ChatRoom room : chatRoomList) {
                    sendMessageClient(++count + ". " + room.getName());
                }
                sendMessageClient(++count + ". Exit");
                int room = chooseRoom();
                if(room < 0 || room > count) {
                    sendMessageClient("Choose correct room");
                } else {
                    if(room == count) {
                        refuseConnection();
                    } else {
                        ChatRoom chatRoom = chatRoomList.get(room - 1);
                        if(chatRoom.getPassword() != null) {
                            sendMessageClient("Enter password for chat:");
                            String password = Objects.requireNonNull(JsonConverter.
                                    parseStringToObject(bufferedReader.readLine())).getMessageText();
                            if(roomService.signIn(chatRoom.getId(), password)) {
                                sendMessageClient("Successful!");
                                startChatRoom(chatRoom);
                            } else {
                                sendMessageClient("Failed!");
                            }
                        } else {
                            startChatRoom(chatRoom);
                        }
                    }
                }
            }
        } catch (IOException ioException) {
            System.out.println(ioException.getMessage());
        }
    }

    private int chooseRoom() {
        try {
            try {
                return Integer.parseInt(Objects.requireNonNull(JsonConverter.
                        parseStringToObject(bufferedReader.readLine())).getMessageText());
            } catch (NumberFormatException exception) {
                System.out.println(exception.getMessage());
            }
        } catch (IOException ioException) {
            System.err.println("Error while reading messages3: " + ioException.getMessage());
        }
        return -1;
    }

    private void startChatRoom(ChatRoom chatRoom) throws IOException {
        chatId = chatRoom.getId();
        sendMessageClient(chatRoom.getName() + " --- ");
        startMessaging();
    }
}