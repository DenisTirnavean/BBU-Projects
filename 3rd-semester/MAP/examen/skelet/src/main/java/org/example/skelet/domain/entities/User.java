package org.example.skelet.domain.entities;

public abstract class User extends Entity<Long> {

    private String name;
    private String password;

    public User(Long aLong, String name, String password) {
        super(aLong);
        this.name = name;
        this.password = password;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public abstract String getType();
}
