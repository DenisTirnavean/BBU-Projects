package org.example.skelet.domain.validator;

import org.example.skelet.domain.entities.Entity;
import org.example.skelet.domain.exceptions.ValidationException;

public interface ValidationStrategy<E extends Entity<Long>> {
    void validate(E entity) throws ValidationException;
}
