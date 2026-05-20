package org.example.skelet.domain.entities;

public class Produs extends Entity<Long>{
    private String sku;
    private String title;
    private String description;
    private Float price;
    private int cantitate;

    private Status status;

    public Produs(Long aLong, String sku, String title, String description, Float price, int cantitate) {
        super(aLong);
        this.sku = sku;
        this.title = title;
        this.description = description;
        this.price = price;
        this.cantitate = cantitate;
        this.status = Status.DONE;
    }

    public String getSku() {
        return sku;
    }

    public void setSku(String sku) {
        this.sku = sku;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Float getPrice() {
        return price;
    }

    public void setPrice(Float price) {
        this.price = price;
    }

    public int getCantitate() {
        return cantitate;
    }

    public void setCantitate(int cantitate) {
        this.cantitate = cantitate;
    }

    public Status getStatus() {
        return status;
    }

    public void setStatus(Status status) {
        this.status = status;
    }
}
