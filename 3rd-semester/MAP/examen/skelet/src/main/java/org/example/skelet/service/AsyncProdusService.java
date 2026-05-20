package org.example.skelet.service;

import org.example.skelet.domain.entities.Produs;

import javax.swing.*;
import java.util.Random;

public class AsyncProdusService extends Thread {
    ProdusService produsService;
    String action;
    Produs entity;
    int lag;

    public AsyncProdusService(ProdusService produsService, Produs entity, String action) {
        this.produsService = produsService;
        this.entity = entity;
        this.action = action;
    }

    public String getAction() {
        return action;
    }

    public void setAction(String action) {
        this.action = action;
    }

    public Produs getEntity() {
        return entity;
    }

    public void setEntity(Produs entity) {
        this.entity = entity;
    }

    public void setLag(int delay) {
        this.lag = delay;
    }

    public void run() {

        try {
            if (action.equals("ADD")) {
                Thread.sleep(lag);
                produsService.save(entity);
            }
            if (action.equals("REMOVE")) {
                Thread.sleep(lag);
                produsService.delete(entity);
            }
            if (action.equals("UPDATE")) {
                Thread.sleep(lag);
                produsService.update(entity);
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }
    public int generateLag(){
        Random random = new Random();
        var delay = random.nextInt(200, 1000);
        return delay;
    }

}
