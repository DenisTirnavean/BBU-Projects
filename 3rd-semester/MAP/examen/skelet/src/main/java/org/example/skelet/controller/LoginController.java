package org.example.skelet.controller;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.stage.Stage;
import org.example.skelet.domain.entities.Admin;
import org.example.skelet.domain.entities.Cashier;
import org.example.skelet.domain.entities.User;
import org.example.skelet.service.LoginManager;
import org.example.skelet.service.ProdusService;

import java.io.IOException;

public class LoginController {

    @FXML
    private TextField username;
    @FXML
    private PasswordField password;


    @FXML
    private Button loginButton;


    private LoginManager loginManager;
    private ProdusService produsService;

    public void setServices(LoginManager loginManager,ProdusService produsService ) {
        this.loginManager = loginManager;
        this.produsService = produsService;
    }

    @FXML
    public void onLoginAction()
    {
        if (username.getText().isEmpty() || password.getText().isEmpty()) {
            showError("Please fill all fields.");
            return;
        }

        String user = username.getText();
        String pass = password.getText();

        var loggedUser =loginManager.authenticate(user, pass);

        if(loggedUser.isPresent()) {
            try {
                openUserWindow(loggedUser.get());
                Alert alert = new Alert(Alert.AlertType.INFORMATION, "Welcome", ButtonType.OK);
                alert.show();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        else{
            showError("Invalid username or password.");
        }
    }
    private void showError(String msg) {
        Alert alert = new Alert(Alert.AlertType.ERROR, msg, ButtonType.OK);
        alert.show();
    }
    private void openUserWindow(User loggedUser) throws IOException {

        try {

            if(loggedUser instanceof Admin) {

                FXMLLoader loader = new FXMLLoader(getClass().getResource("/org/example/skelet/admin_view.fxml"));
                Parent root = loader.load();

                AdminController controller = loader.getController();
                controller.setServices(produsService);
                Stage stage = new Stage();
                stage.setTitle("Admin Panel of:  " + loggedUser.getName().toUpperCase());
                stage.setScene(new Scene(root));
                stage.show();
            } else if (loggedUser instanceof Cashier traf) {

                FXMLLoader loader = new FXMLLoader(getClass().getResource("/org/example/skelet/dude_view.fxml"));
                Parent root = loader.load();

                CashierController tr = loader.getController();
                tr.setServices(produsService);
                Stage stage = new Stage();
                stage.setTitle("Viewer Panel of: " + loggedUser.getName().toUpperCase());
                stage.setScene(new Scene(root));
                stage.show();
            }
        } catch (IOException e) {
            showError("Cannot load user UI.");
        }
    }
}
