package org.example.skelet.controller;

import org.example.skelet.utils.Observer;

public abstract class AbstractController implements Observer {

    public abstract void reload();

    @Override
    public void update() {
        reload();
    }
}
