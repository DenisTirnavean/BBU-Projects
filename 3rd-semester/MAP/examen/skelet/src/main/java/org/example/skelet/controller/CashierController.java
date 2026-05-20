package org.example.skelet.controller;

import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import org.example.skelet.domain.entities.Produs;
import org.example.skelet.service.ProdusService;
import org.example.skelet.utils.Observer;

import java.util.ArrayList;

public class CashierController implements Observer {
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

    @FXML
    TableColumn<Produs, Integer> cantitateColumn;

    @FXML
    TextField titleField;

    @FXML
    TextField cantitateField;

    ObservableList<Produs> observableList = FXCollections.observableArrayList();
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

        cantitateColumn.setCellValueFactory(data->
        {
            Produs produs = data.getValue();
            return new  ReadOnlyObjectWrapper<>(produs.getCantitate());
        });

        tableView.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            fillFields(newValue);
        });

        tableView.setItems(observableList);
    }

    private void fillFields(Produs newValue){
        this.titleField.setText(newValue.getTitle());
        this.cantitateField.setText(Integer.toString(newValue.getCantitate()));;
    }

    public void setServices(ProdusService produsService){
        this.produsService = produsService;
        produsService.registerObserver(this);
        reload();
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
    public void onSell(){
        var prod = tableView.getSelectionModel().getSelectedItem();
        if(prod == null){
            showError("Select something to sell");
        }
        else{
            try {
                prod.setCantitate(prod.getCantitate() - 1);
                produsService.update(prod);
            }
            catch (Exception e){
                showError(e.getMessage());
            }
        }
    }

    private void showError(String message){
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText(message);
        alert.showAndWait();

    }
}
