package org.example.skelet.domain.entities;

public class Cashier extends User{
    public Cashier(Long aLong, String name, String password) {
        super(aLong, name, password);
    }

    @Override
    public String getType() {
        return "CASHIER";
    }
}
