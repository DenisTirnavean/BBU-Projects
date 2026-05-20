package org.example.skelet.service;

import org.example.skelet.domain.entities.Produs;
import org.example.skelet.domain.entities.Status;
import org.example.skelet.domain.validator.ValidationStrategy;
import org.example.skelet.domain.validator.Validator;
import org.example.skelet.repository.Repository;

import java.util.ArrayList;

public class ProdusService extends Service<Produs>{
    public ProdusService(Repository<Long, Produs> repository) {
        super(repository);
    }

    @Override
    public void initValidator(ValidationStrategy<Produs> strategy) {
        this.validator = new Validator<>(strategy);
    }

    public Iterable<Produs> findAll(){
        return repository.findAll();

    }
    public void synch(){
        var list = new ArrayList<Produs>();
        repository.findAll().forEach(product -> product.setStatus(Status.DONE));
        notifyObservers();
    }
}
