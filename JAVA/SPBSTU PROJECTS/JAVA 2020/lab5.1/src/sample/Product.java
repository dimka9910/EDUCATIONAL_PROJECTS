package sample;

import javafx.beans.property.*;

public class Product
{

    private final IntegerProperty id = new SimpleIntegerProperty();
    private final IntegerProperty prodid = new SimpleIntegerProperty();
    private final StringProperty title = new SimpleStringProperty();
    private final StringProperty cost = new SimpleStringProperty();


    public int getId()
    {
        return id.get();
    }
    public int getProdid()
    {
        return prodid.get();
    }
    public String getTitle()
    {
        return title.get();
    }
    public String getCost()
    {
        return cost.get();
    }

    public void setId(int value){
        id.set(value);
    }
    public void setProdid(int value){
        prodid.set(value);
    }
    public void setTitle(String value){
        title.set(value);
    }
    public void setCost(String value){
        cost.set(value);
    }


    public IntegerProperty idProperty() {
        return id;
    }
    public IntegerProperty prodidProperty()
    {
        return prodid;
    }
    public StringProperty titleProperty()
    {
        return title;
    }
    public StringProperty costProperty()
    {
        return cost;
    }
}
