package org.example.skelet.domain.entities;

public class Admin extends User
{
    public Admin(Long aLong, String username, String password) {
        super(aLong, username, password);
    }
    @Override
    public String getType() {
        return "ADMIN";
    }
}
