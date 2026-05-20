package org.example.skelet.domain.validator;

import org.example.skelet.domain.entities.Entity;
import org.example.skelet.domain.exceptions.ValidationException;

public class Validator<E extends Entity<Long>> {
    private ValidationStrategy<E> strategy;

    public Validator(ValidationStrategy<E> strategy) {
        this.strategy = strategy;
    }


    public void validate(E entity) throws ValidationException{
        strategy.validate(entity);
    };
}
