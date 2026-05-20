package org.example.skelet.domain.validator.strategies;

import org.example.skelet.domain.entities.User;
import org.example.skelet.domain.exceptions.ValidationException;
import org.example.skelet.domain.validator.ValidationStrategy;

public class UserValidationStrategy implements ValidationStrategy<User> {
    @Override
    public void validate(User entity) throws ValidationException {
        if (entity == null) {
            throw new ValidationException("entity is null");
        }
        if (entity.getId() == null) {
            throw new ValidationException("id is null");
        }
        if (entity.getName() == null || entity.getName().isEmpty()) {
            throw new ValidationException("name is null or empty");
        }
        if(entity.getPassword() == null || entity.getPassword().isEmpty()) {
            throw new ValidationException("password is null or empty");
        }
    }
}
