package org.example.skelet.service;

import org.example.skelet.domain.entities.User;
import org.example.skelet.repository.UserRepository;

import java.util.Optional;

public class LoginManager {
    private UserService userService;

    public LoginManager(UserService userService) {
        this.userService = userService;
    }
    public Optional<User> authenticate(String username,  String password) {
        var u = userService.getUser(username);
        if (u.isPresent()) {
            if (u.get().getPassword().equals(password)) {
                return u;
            }
        }
        return Optional.empty();
    }
}
