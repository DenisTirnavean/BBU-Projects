package org.example.skelet.repository;

import org.example.skelet.domain.entities.User;

import java.util.Optional;

public interface UserRepository extends Repository<Long,User> {
    public Optional<User> getUserByUsername(String username);
}
