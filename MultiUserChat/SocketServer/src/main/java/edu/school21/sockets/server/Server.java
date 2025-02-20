package edu.school21.sockets.server;

import edu.school21.sockets.services.RoomService;
import edu.school21.sockets.services.UsersService;
import edu.school21.sockets.services.MessagesService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import javax.sql.DataSource;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.Connection;
import java.sql.Statement;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;
import java.util.logging.Logger;

@Component
public class Server {

    private static final Logger logger = Logger.getLogger(Server.class.getName());
    private final ThreadConnectionFactory threadConnectionFactory;
    private ServerSocket serverSocket;
    private static final List<ThreadConnection> connectionList = new LinkedList<>();

    private final UsersService usersService;
    private final MessagesService messagesService;
    private final RoomService roomService;

    @Autowired
    public Server(
            @Qualifier("usersServiceImpl") UsersService usersService,
            ThreadConnectionFactory threadConnectionFactory,
            MessagesService messagesService, RoomService roomService) {
        this.usersService = usersService;
        this.threadConnectionFactory = threadConnectionFactory;
        this.messagesService = messagesService;
        this.roomService = roomService;
    }

    public void start(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        Thread consoleThread = new Thread(this::readConsoleInput);
        consoleThread.start();
        try {
            logger.info("Server started, waiting for clients...");
            while (true) {
                Socket socket = serverSocket.accept();
                logger.info("Client connected: " + socket.getInetAddress());
                ThreadConnection connection = threadConnectionFactory.create(socket, usersService, messagesService,roomService);
                connection.start();
                connectionList.add(connection);
            }
        } catch (IOException ioException) {
            logger.severe("Error in server: " + ioException.getMessage());
            shutdownServer();
        }
    }

    public boolean initDatabase(DataSource dataSource) {
        String schemaFilePath = "/schema.sql";

        try {
            try (Connection connection = dataSource.getConnection();
                 Statement statement = connection.createStatement()) {

                InputStream inputStream = Server.class.getResourceAsStream(schemaFilePath);
                if (inputStream == null) {
                    System.err.println("Resource not found: " + schemaFilePath);
                    return false;
                }

                StringBuilder query = new StringBuilder();
                try (BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream))) {
                    String line;
                    while ((line = reader.readLine()) != null) {
                        query.append(line).append(System.lineSeparator());
                    }
                }

                String createTablesQuery = query.toString().trim();
                if (createTablesQuery.isEmpty()) {
                    System.err.println("Schema file is empty or invalid.");
                    return false;
                }

                statement.executeUpdate(createTablesQuery);
            }
            return true;

        } catch (Exception e) {
            System.err.println("An error occurred during database initialization: " + e.getMessage());
            return false;
        }
    }



    private void readConsoleInput() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        try {
            while (true) {
                String input = reader.readLine();
                if (input != null && input.equalsIgnoreCase("exit")) {
                    refuseAll();
                }
            }
        } catch (IOException e) {
            System.out.println("Error in server: " + e.getMessage());
        } finally {
            try {
                reader.close();
            } catch (IOException e) {
                System.out.println("Error in server: " + e.getMessage());
            }
        }
    }

    private synchronized void refuseAll() {
        try {
            for (ThreadConnection connection : connectionList) {
                connection.refuseConnection();
            }
            serverSocket.close();
        } catch (IOException ioException) {
            System.out.println("Error in server: " + ioException.getMessage());
            System.exit(-1);
        }
        System.exit(0);
    }

    public static boolean removeConnection(ThreadConnection connection) {
        boolean removed = connectionList.remove(connection);
        if (removed) {
            logger.info("Connection removed: " + connection.getChatId());
        }
        return removed;
    }

    static void sendMessageToChat(String message, String username, ThreadConnection connectionCurrent)
            throws IOException {
        Long chatId = connectionCurrent.getChatId();
        for (ThreadConnection connection : connectionList) {
            if (Objects.equals(connection.getChatId(), chatId)) {
                connection.sendMessageClient(username + ": " + message);
            }
        }
    }

    public void shutdownServer() {
        try {
            for (ThreadConnection connection : connectionList) {
                connection.refuseConnection();
            }
            serverSocket.close();
            logger.info("Server shut down.");
        } catch (IOException e) {
            logger.severe("Error during server shutdown: " + e.getMessage());
        }
    }
}