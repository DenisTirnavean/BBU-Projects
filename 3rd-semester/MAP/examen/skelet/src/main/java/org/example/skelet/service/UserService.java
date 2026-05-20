package org.example.skelet.service;

import org.example.skelet.domain.entities.User;
import org.example.skelet.domain.validator.ValidationStrategy;
import org.example.skelet.domain.validator.strategies.UserValidationStrategy;
import org.example.skelet.repository.Repository;
import org.example.skelet.repository.UserDBRepository;
import org.example.skelet.repository.UserRepository;
import org.example.skelet.utils.Observable;

import java.util.Optional;

public class UserService extends Service<User> {

    public Optional<User> getUser(String username) {
        return ((UserRepository)this.repository).getUserByUsername(username);
    }

    public UserService(Repository<Long, User> repository) {
        super(repository);
    }

    @Override
    public void initValidator(ValidationStrategy<User> strategy) {

    }
}
