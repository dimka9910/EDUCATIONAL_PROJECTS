package sample;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.text.Text;
import javafx.util.Callback;
import java.net.URL;
import java.sql.*;
import java.util.Optional;
import java.util.ResourceBundle;

import javafx.scene.control.Button;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;


public class Controller implements Initializable
{

    // Тэйбл вивер и всё для него
    @FXML
    public TableView<Product> tableApp;
    @FXML
    public TableColumn<Product, Integer> id;
    @FXML
    public TableColumn<Product, Integer> prodid;
    @FXML
    public TableColumn<Product, String> title;
    @FXML
    public TableColumn<Product, String> cost;
    @FXML
    public TableColumn edit;

    private static Connection connection;
    private static Handler handler;
    private static Boolean created = false;

    //Создание Таблицы
    public Button create;
    public TextField create_val;
    public Button ok;
    public Button create_cancel;
    public Text create_err;

    //Очистка таблицы
    public Button clean;

    //Поиск
    public Button search;
    public TextField search_val;
    public Button search_cancel;

    //Фильтр по цене
    public Button fbp;
    public TextField fbp_from_val;
    public TextField fbp_to_val;
    public Text fbp_from;
    public Text fbp_to;
    public Button fbp_filt;
    public Button fbp_cancel;
    public Text fbp_err;

    //Добавление
    public Button plus;
    public TextField id_val;
    public TextField prodid_val;
    public TextField title_val;
    public TextField cost_val;
    public Button add;
    public Button add_cancel;
    public Button refresh;


    //Инициализация
    @Override
    public void initialize(URL url, ResourceBundle rb){
        MysqlConnection conn = MysqlConnection.getInstance();
        connection = conn.connect();

        //Делаем невидимым всё что пока не нужно
        search_cancel.setVisible(false);
        fbpVisible(false);
        addVisible(false);
        createVisible(false);
        create_err.setVisible(false);
        tableApp.setEditable(true);
        disableButtons(true);
        create.setDisable(false);
        fbp_err.setVisible(false);

        tableApp.setPrefHeight(287);
        create_val.setPromptText("input N");
        id_val.setPromptText("auto");
        id_val.setDisable(true);
        prodid_val.setPromptText("Product ID");
        title_val.setPromptText("Title");
        cost_val.setPromptText("Cost");

    }

    private void fbpVisible (boolean b) {
        fbp.setVisible(!b);
        fbp_cancel.setVisible(b);
        fbp_filt.setVisible(b);
        fbp_to.setVisible(b);
        fbp_from.setVisible(b);
        fbp_from_val.setVisible(b);
        fbp_to_val.setVisible(b);
    }
    private void createVisible (boolean b) {
        create_cancel.setVisible(b);
        create_val.setVisible(b);
        ok.setVisible(b);
        create.setVisible(!b);
    }
    private void addVisible (boolean b) {
        id_val.setVisible(b);
        prodid_val.setVisible(b);
        title_val.setVisible(b);
        cost_val.setVisible(b);
        add.setVisible(b);
        add_cancel.setVisible(b);
    }
    private void disableButtons(boolean b){
        search.setDisable(b);
        plus.setDisable(b);
        clean.setDisable(b);
        create.setDisable(b);
        fbp.setDisable(b);
    }
    private void resizeTable(boolean b) {
        tableApp.setPrefHeight(b ? 261 : 287);
    }
    private static boolean isNumeric(String strNum) {
        if (strNum == null) {
            return false;
        }
        try {
            int d = Integer.parseInt(strNum);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
    }

    //Search
    public void pressedSearch(ActionEvent event){
        disableButtons(true);
        search.setDisable(false);
        showTable(handler.price(search_val.getText()));
        search_cancel.setVisible(true);
    }
    public void pressedSearch_cancel(ActionEvent event){
        disableButtons(false);
        search_cancel.setVisible(false);
        formTable();
        search_val.setText("");
    }
    public void pressedRefresh(ActionEvent event){
        formTable();
    }

    //FILTER BY PRICE
    public void pressedFbp_cancel(ActionEvent event){
        disableButtons(false);
        fbpVisible(false);
        fbp_to_val.setText("");
        fbp_from_val.setText("");
        fbp_err.setVisible(false);
        formTable();
    }
    public void pressedFbp_filt(ActionEvent event){
            if (EditingCell.isNumeric(fbp_from_val.getText()) && EditingCell.isNumeric(fbp_to_val.getText())
                    && (Double.parseDouble(fbp_from_val.getText()) < Double.parseDouble(fbp_to_val.getText())))
            {
                try
                {
                    System.out.println("trt");
                    showTable(handler.filter_by_price(Double.parseDouble(fbp_from_val.getText()),
                            Double.parseDouble(fbp_to_val.getText())));
                    fbp_err.setVisible(false);
                    System.out.println("trt1");
                } catch (Exception e){ System.out.println("trt2"); }
            } else {
                fbp_err.setVisible(true);
            }
    }
    public void pressedFbp(ActionEvent event){
        disableButtons(true);
        fbpVisible(true);
    }

    //Добавление
    public void pressedPlus(ActionEvent event){
        resizeTable(true);
        addVisible(true);
        disableButtons(true);
    }
    public void pressedAdd(ActionEvent event){

        if (isNumeric(prodid_val.getText()))
        {
            if (!handler.exist(title_val.getText()))
            {
                if (EditingCell.isNumeric(cost_val.getText()))
                {
                    handler.add(Integer.parseInt(prodid_val.getText()), title_val.getText(), Double.parseDouble(cost_val.getText()));
                    formTable();
                    prodid_val.setText("");
                    title_val.setText("");
                    cost_val.setText("");
                    prodid_val.setPromptText("Product ID");
                    title_val.setPromptText("Title");
                    cost_val.setPromptText("Cost");
                } else {
                    cost_val.setText("");
                    cost_val.setPromptText("INPUT DOUBLE!");
                }
            } else {
                title_val.setText("");
                title_val.setPromptText("ALREADY EXIST");
            }
        } else {
            prodid_val.setText("");
            prodid_val.setPromptText("WRONG PROD. ID");
        }
    }
    public void pressedAdd_cancel(ActionEvent event){
        prodid_val.setText("");
        title_val.setText("");
        cost_val.setText("");
        prodid_val.setPromptText("Product ID");
        title_val.setPromptText("Title");
        cost_val.setPromptText("Cost");
        resizeTable(false);
        addVisible(false);
        disableButtons(false);
    }

    //Создание и удаление
    public void pressedOK(ActionEvent event){

        if (isNumeric(create_val.getText()))
        {
            int N = Integer.parseInt(create_val.getText());
            handler = new Handler(connection, N);
            formTable();
            create_err.setVisible(false);
            create_val.setText("");
            createVisible(false);
            disableButtons(false);
            created = true;

        } else {
            create_err.setVisible(true);
        }

    }
    public void pressedCreate(ActionEvent event){
        createVisible(true);
        disableButtons(true);
    }
    public void pressedCreateCancel(ActionEvent event){
        create_val.setText("");
        createVisible(false);
        create_err.setVisible(false);
        if (created) {
            disableButtons(false);
        }
        create.setDisable(false);
    }
    public void pressedClean(ActionEvent event){
        Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
        alert.setTitle("Clean table");
        alert.setHeaderText("Are you sure want to clean table");
        alert.setContentText("Sure??");
        alert.setContentText("Really sure??");
        Optional<ButtonType> option = alert.showAndWait();
        if (option.get() == ButtonType.OK) {
            handler.clearTable();
            formTable();
            created = false;
            disableButtons(true);
            create.setDisable(false);
        }
    }




    private void formTable(){
        try
        {
            ResultSet resultSet = handler.show_all();
            showTable(resultSet);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void showTable(ResultSet resultSet)
    {
            ObservableList<Product> list = FXCollections.observableArrayList();

            try
            {
                while (resultSet.next())
                {
                    Product product = new Product();
                    product.setId(resultSet.getInt(1));
                    product.setProdid(resultSet.getInt(2));
                    product.setTitle(resultSet.getString(3));
                    product.setCost(Double.toString(resultSet.getDouble(4)));
                    list.add(product);
                }
            } catch (Exception e) {}

            id.setCellValueFactory(new PropertyValueFactory<>("id"));
            prodid.setCellValueFactory(new PropertyValueFactory<>("prodid"));
            title.setCellValueFactory(new PropertyValueFactory<>("title"));
            cost.setCellValueFactory(new PropertyValueFactory<>("cost"));
            tableApp.setItems(list);

            Callback<TableColumn<Product, String>,TableCell<Product, String>> cellFactory_Edit=(param) -> {
                final TableCell<Product, String> cell = new TableCell<Product, String>(){
                    @Override
                    public void updateItem(String item, boolean empty){
                        super.updateItem(item, empty);
                        if (empty) {
                            setGraphic(null);
                            setText(null);
                        }
                        else {
                            final Button editButton= new Button("Delete");
                            editButton.setOnAction(event -> {
                                Product p = getTableView().getItems().get(getIndex());
                                Alert alert = new Alert(Alert.AlertType.CONFIRMATION);
                                alert.setTitle("Delete product");
                                alert.setHeaderText("Are you sure want to remove Product");
                                alert.setContentText(p.getTitle());
                                alert.setContentText(p.getTitle());
                                Optional<ButtonType> option = alert.showAndWait();
                                if (option.get() == ButtonType.OK) {
                                        handler.delete(p.getTitle());
                                        formTable();
                                }
                            });
                            setGraphic(editButton);
                            setText(null);
                        }
                    }
                };
                return cell;
            };
            edit.setCellFactory(cellFactory_Edit); //Добавление кнопочки EDIT

            //Редактирование в таблице
            Callback<TableColumn<Product, String>, TableCell<Product, String>> cellFactory = p ->
                    new EditingCell();
            cost.setCellFactory(cellFactory);
            cost.setOnEditCommit(t ->
            {
                ((Product) t.getTableView().getItems().get(
                        t.getTablePosition().getRow())
                ).setCost(t.getNewValue());

                handler.change_price(((Product) t.getTableView().getItems().get(
                        t.getTablePosition().getRow())
                ).getTitle(), Double.parseDouble(t.getNewValue()));
            });

    }
}
