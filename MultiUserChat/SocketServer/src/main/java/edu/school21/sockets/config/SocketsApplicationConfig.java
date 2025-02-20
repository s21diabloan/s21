package edu.school21.sockets.config;

import edu.school21.sockets.models.User;
import edu.school21.sockets.server.Server;
import edu.school21.sockets.server.ThreadConnectionFactory;
import edu.school21.sockets.services.MessagesService;
import edu.school21.sockets.services.RoomService;
import edu.school21.sockets.services.UsersService;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.*;
import org.springframework.jdbc.core.JdbcTemplate;
import com.zaxxer.hikari.HikariDataSource;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import javax.sql.DataSource;

@Configuration
@PropertySource("classpath:db.properties")
@ComponentScan(basePackages = "edu.school21.sockets")
public class SocketsApplicationConfig {

    @Value("${db.url}")
    private String dbUrl;

    @Value("${db.username}")
    private String dbUsername;

    @Value("${db.password}")
    private String dbPassword;

    @Value("${db.driverClassName}")
    private String driverClassName;

    @Bean
    public DataSource dataSource() {
        HikariDataSource dataSource = new HikariDataSource();
        dataSource.setJdbcUrl(dbUrl);
        dataSource.setUsername(dbUsername);
        dataSource.setPassword(dbPassword);
        dataSource.setDriverClassName(driverClassName);
        return dataSource;
    }

    @Bean
    public JdbcTemplate jdbcTemplate(DataSource dataSource) {
        return new JdbcTemplate(dataSource);
    }

    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }

    @Bean
    public User user() {
        return new User();
    }

    @Bean
    public Server server(UsersService usersService,
                         MessagesService messagesService,
                         ThreadConnectionFactory threadConnectionFactory, RoomService roomService) {
        return new Server(usersService, threadConnectionFactory, messagesService, roomService);
    }
}