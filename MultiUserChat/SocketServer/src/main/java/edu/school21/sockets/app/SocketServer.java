package edu.school21.sockets.app;

import edu.school21.sockets.server.Server;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import edu.school21.sockets.config.SocketsApplicationConfig;

import javax.sql.DataSource;

public class SocketServer {
    public static void main(String[] args) {
        try {
            Integer port = getPort(args);
            ApplicationContext context = new AnnotationConfigApplicationContext(SocketsApplicationConfig.class);
            Server server = context.getBean(Server.class);
            DataSource dataSource = context.getBean(DataSource.class);
            if (server.initDatabase(dataSource)) {
            server.start(port);}
        } catch (IllegalArgumentException e) {
            System.err.println("Usage: java -jar target/socket-server.jar --port=<PORT>");
            System.exit(1);
        } catch (Exception e) {
            System.err.println("An unexpected error occurred: " + e.getMessage());
            System.exit(1);
        }
    }

private static Integer getPort(String[] args) {
    if (args.length != 1 || !args[0].startsWith("--port=")) {
        throw new IllegalArgumentException();
    }
    try {
        return Integer.parseInt(args[0].substring("--port=".length()));
    } catch (NumberFormatException e) {
        throw new IllegalArgumentException();
    }
}
}