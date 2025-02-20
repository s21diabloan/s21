package edu.school21.sockets.config;

import edu.school21.sockets.client.Client;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;

@Configuration
@ComponentScan(basePackages = "edu.school21.sockets")
public class ClientApplicationConfig {

    @Bean
    public Client socketClient() {
        return new Client("localhost");
    }
}