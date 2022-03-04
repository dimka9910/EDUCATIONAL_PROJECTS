package org.example.xfront;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.Group;
import javafx.scene.text.Text;

import java.io.IOException;
import java.net.URL;

public class Main extends Application{

    private static Stage currentStage;

    @Override
    public void start(Stage stage) throws IOException {

        currentStage = stage;
        replaceStageContent("ui/resources/main2.fxml");
        currentStage.show();
    }

    public static void replaceStageContent(String fxml) throws IOException {
        FXMLLoader loader = new FXMLLoader(Main.class.getResource(fxml));
        Parent page = loader.load();
        Scene scene = currentStage.getScene();
        if (scene == null) {
            scene = new Scene(page);
            currentStage.setScene(scene);
        } else {
            currentStage.setScene(new Scene(page));
        }
    }
}