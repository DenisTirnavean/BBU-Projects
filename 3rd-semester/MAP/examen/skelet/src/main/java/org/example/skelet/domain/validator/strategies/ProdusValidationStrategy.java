package org.example.skelet.domain.validator.strategies;

import org.example.skelet.domain.entities.Produs;
import org.example.skelet.domain.exceptions.ValidationException;
import org.example.skelet.domain.validator.ValidationStrategy;

public class ProdusValidationStrategy implements ValidationStrategy<Produs> {
    @Override
    public void validate(Produs entity) throws ValidationException {
        if(entity == null)
            throw new ValidationException("Produs null");
        if(entity.getSku().isEmpty())
            throw new ValidationException("Sku empty");
        if(entity.getTitle().isEmpty())
            throw new ValidationException("Title empty");
        if(entity.getDescription().isEmpty())
            throw new ValidationException("Description empty");
        if(entity.getPrice() < 0)
            throw new ValidationException("Price < 0");
        if(entity.getCantitate()<0)
            throw new ValidationException("Cantitate < 0");
    }

}
