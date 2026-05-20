package org.example.skelet.controller;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import org.example.skelet.domain.entities.Produs;
import org.example.skelet.domain.entities.Status;
import org.example.skelet.repository.ProdusRepository;
import org.example.skelet.service.AsyncProdusService;
import org.example.skelet.service.ProdusService;
import org.example.skelet.utils.Observer;

import java.util.ArrayList;
import java.util.List;

public class AdminController implements Observer {

    private ProdusService produsService;

    @FXML
    TableView<Produs> tableView;

    @FXML
    TableColumn<Produs, Long> idColumn;

    @FXML
    TableColumn<Produs, String> skuColumn;

    @FXML
    TableColumn<Produs, String> titleColumn;

    @FXML
    TableColumn<Produs, String> descriptionColumn;

    @FXML
    TableColumn<Produs, Float> priceColumn;

//    @FXML
//    TableColumn<Produs, Integer> cantitateColumn;


    @FXML
    TableColumn<Produs, String> statusColumn;


    @FXML
    TextField idField;
    @FXML
    TextField skuField;
    @FXML
    TextField titleField;
    @FXML
    TextField descriptionField;
    @FXML
    TextField priceField;
    @FXML
    TextField cantitateField;
    ObservableList<Produs> observableList = FXCollections.observableArrayList();

    List<Produs> produsQueue = new ArrayList<>();

    @FXML
    public void initialize(){

        idColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new ReadOnlyObjectWrapper<>(produs.getId());
        });

        skuColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new  ReadOnlyObjectWrapper<>(produs.getSku());
        });
        titleColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new  ReadOnlyObjectWrapper<>(produs.getTitle());
        });
        descriptionColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new  ReadOnlyObjectWrapper<>(produs.getDescription());
        });

        priceColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new  ReadOnlyObjectWrapper<>(produs.getPrice());
        });

//        cantitateColumn.setCellValueFactory(data->
//        {
//            Produs produs = data.getValue();
//            return new  ReadOnlyObjectWrapper<>(produs.getCantitate());
//        });
        statusColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new  ReadOnlyObjectWrapper<>(produs.getStatus().toString());
        });

        tableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if(newValue != null){
                fillFields(newValue);
            }
        });

        idField.setDisable(true);
        tableView.setItems(observableList);
    }

    private void fillFields(Produs newValue){
        this.idField.setText(newValue.getId().toString());
        this.skuField.setText(newValue.getSku());
        this.titleField.setText(newValue.getTitle());
        this.descriptionField.setText(newValue.getDescription());
        this.priceField.setText(newValue.getPrice().toString());
        this.cantitateField.setText(Integer.toString(newValue.getCantitate()));

    }

    public void setServices(ProdusService produsService){
        this.produsService = produsService;
        produsService.registerObserver(this);
        reload();
    }

    @FXML
    public void onAdd(){
        Long id= idField.getText().isEmpty()?null:Long.parseLong(idField.getText());
        String sku = skuField.getText().isEmpty()?null:skuField.getText();
        String title = titleField.getText().isEmpty()?null:titleField.getText();
        String description = descriptionField.getText().isEmpty()?null:descriptionField.getText();
        Float price = Float.parseFloat(priceField.getText().isEmpty()?null:priceField.getText());
        Integer cantitate = cantitateField.getText().isEmpty()?null:Integer.parseInt(cantitateField.getText());
        Produs entity = new Produs(id,sku,title,description,price,cantitate);
        entity.setStatus(Status.PENDING);
        produsQueue.add(entity);
        observableList.add(entity);
        //AsyncProdusService produsService1 = new AsyncProdusService(produsService,entity, "ADD");
        //produsService1.start();
    }
    @FXML
    public void onUpdate(){
        Long id= idField.getText().isEmpty()?null:Long.parseLong(idField.getText());
        String sku = skuField.getText().isEmpty()?null:skuField.getText();
        String title = titleField.getText().isEmpty()?null:titleField.getText();
        String description = descriptionField.getText().isEmpty()?null:descriptionField.getText();
        Float price = Float.parseFloat(priceField.getText().isEmpty()?null:priceField.getText());
        Integer cantitate = cantitateField.getText().isEmpty()?null:Integer.parseInt(cantitateField.getText());
        Produs entity = new Produs(id,sku,title,description,price,cantitate);
        AsyncProdusService produsService1 = new AsyncProdusService(produsService,entity, "UPDATE");
        //entity.setStatus(Status.PENDING);
        reload();
        produsService1.start();
    }
    @FXML
    public void onDelete(){
        Long id= idField.getText().isEmpty()?null:Long.parseLong(idField.getText());
        String sku = skuField.getText().isEmpty()?null:skuField.getText();
        String title = titleField.getText().isEmpty()?null:titleField.getText();
        String description = descriptionField.getText().isEmpty()?null:descriptionField.getText();
        Float price = Float.parseFloat(priceField.getText().isEmpty()?null:priceField.getText());
        Integer cantitate = cantitateField.getText().isEmpty()?null:Integer.parseInt(cantitateField.getText());
        Produs entity = new Produs(id,sku,title,description,price,cantitate);
        produsService.delete(entity);

    }

    private void reload(){
        observableList.clear();
        var list =new ArrayList<Produs>();
        produsService.findAll().forEach(list::add);
        observableList.setAll(list);
    }

    @Override
    public void update() {
        reload();
    }
    @FXML
    public void onSync(){
        //produsService.synch();
        observableList.forEach(produs->{
            if(produs.getStatus().equals(Status.PENDING)){
                produs.setStatus(Status.PENDING);
            }
        });
        AsyncProdusService asyncProdusService1 = new AsyncProdusService(produsService,null,null);
        asyncProdusService1.setLag(asyncProdusService1.generateLag());
        produsQueue.forEach(
                produs->{produs.setStatus(Status.DONE);
                    asyncProdusService1.setEntity(produs);
                    asyncProdusService1.setAction("ADD");
                    asyncProdusService1.start();
                }
        );
    }
}
