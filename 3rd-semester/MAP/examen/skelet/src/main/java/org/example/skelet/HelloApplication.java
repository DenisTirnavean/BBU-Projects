package org.example.skelet;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.example.skelet.controller.LoginController;
import org.example.skelet.domain.validator.strategies.UserValidationStrategy;
import org.example.skelet.repository.ProdusDBRepository;
import org.example.skelet.repository.ProdusRepository;
import org.example.skelet.repository.UserDBRepository;
import org.example.skelet.service.LoginManager;
import org.example.skelet.service.ProdusService;
import org.example.skelet.service.UserService;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {

        String url="jdbc:postgresql://localhost:5432/practicmap";
        String username = "postgres";
        String password = "denis2004";

        UserDBRepository userDBRepository = new UserDBRepository(url, username, password);
        ProdusRepository produsRepository = new ProdusDBRepository(url, username, password);

        ProdusService produsService = new ProdusService(produsRepository);

        UserService userService = new UserService(userDBRepository);
        userService.initValidator(new UserValidationStrategy());

        LoginManager loginManager = new LoginManager(userService);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/org/example/skelet/login_view.fxml"));
        Parent root = loader.load();

        LoginController tr = loader.getController();
        tr.setServices(loginManager, produsService);
        stage.setScene(new Scene(root));
        stage.show();
    }
}
