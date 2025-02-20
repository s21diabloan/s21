package edu.school21.sockets.services;

import edu.school21.sockets.models.User;
import edu.school21.sockets.repositories.UsersRepository;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.*;

@Service
public class UsersServiceImpl implements UsersService {
    private final UsersRepository usersRepository;
    private final PasswordEncoder passwordEncoder;

    public UsersServiceImpl(UsersRepository usersRepository, PasswordEncoder passwordEncoder) {
        this.usersRepository = usersRepository;
        this.passwordEncoder = passwordEncoder;
    }

    @Override
    public boolean signUp(String username, String password) {
        Optional<User> existingUser = usersRepository.findByUsername(username);
        if (existingUser.isPresent()) {
            return false;
        } else {
            String encodedPassword = passwordEncoder.encode(password);
            usersRepository.save(new User(null, username, encodedPassword));
            return true;
        }
    }

    @Override
    public boolean signIn(String username, String password) throws IllegalArgumentException {
        //
        Optional<User> userOptional = usersRepository.findByUsername(username);
        User user;
        if (userOptional.isPresent()) {
            user = userOptional.get();
        } else {
            throw new IllegalArgumentException("User does not exist!");
        }
        if (passwordEncoder.matches(password, user.getPassword())) {
            return true;
        } else {
            System.out.println("Invalid credentials!");
            return false;
        }
    }
}