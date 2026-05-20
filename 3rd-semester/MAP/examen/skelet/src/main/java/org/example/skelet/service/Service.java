package org.example.skelet.service;

import org.example.skelet.domain.entities.Entity;
import org.example.skelet.domain.validator.ValidationStrategy;
import org.example.skelet.domain.validator.Validator;
import org.example.skelet.repository.Repository;
import org.example.skelet.utils.Observable;
import org.example.skelet.utils.Observer;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public abstract class Service<E extends Entity<Long>> implements Observable {
    List<Observer> observers = new ArrayList<Observer>();

    protected Validator<E> validator;

    public abstract void initValidator(ValidationStrategy<E> strategy);

    @Override
    public void registerObserver(Observer o) {
        observers.add(o);
    }

    @Override
    public void removeObserver(Observer o) {
        observers.remove(o);
    }

    @Override
    public void notifyObservers() {
        observers.forEach(Observer::update);
    }

    protected Repository<Long, E> repository;

    public Service(Repository<Long, E> repository) {
        this.repository = repository;
    }

    public Optional<E> getById(Long id) {
        return repository.findOne(id);
    }

    public void save(E entity) {
        repository.save(entity);
        notifyObservers();
    }

    public void delete(E entity) {
        repository.delete(entity.getId());
        notifyObservers();
    }

    public void update(E entity) {
        repository.update(entity);
        notifyObservers();
    }




}
