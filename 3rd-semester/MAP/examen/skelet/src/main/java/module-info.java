module org.example.skelet {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires org.kordamp.bootstrapfx.core;
    requires com.almasb.fxgl.all;
    requires java.sql;
//    requires gradle.api;
    requires javafx.graphics;
//    requires org.example.skelet;
    requires javafx.base;
    requires java.desktop;
//    requires org.example.skelet;

    opens org.example.skelet to javafx.fxml;
    exports org.example.skelet;
}