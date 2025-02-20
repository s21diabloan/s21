package edu.school21.sockets.app;

import edu.school21.sockets.client.Client;
import edu.school21.sockets.config.ClientApplicationConfig;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

public class SocketClient {
    public static void main(String[] args) {
        try {
            if (args.length != 1 || !args[0].startsWith("--server-port=")) {
                throw new IllegalArgumentException();
            }
            int serverPort = Integer.parseInt(args[0].substring("--server-port=".length()));
            ApplicationContext context = new AnnotationConfigApplicationContext(ClientApplicationConfig.class);
            Client client = context.getBean(Client.class);
            client.start(serverPort);
        } catch (IllegalArgumentException e) {
            System.err.println("Usage: java -jar target/socket-client.jar --server-port=8081");
            System.exit(1);
        } catch (Exception e) {
            System.err.println("An unexpected error occurred: " + e.getMessage());
            System.exit(1);
        }
    }
}