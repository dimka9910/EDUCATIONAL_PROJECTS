import org.jetbrains.annotations.NotNull;

import java.sql.*;

public class Handler
{

    private Statement statement;

    public Handler(@NotNull Connection connection, int N) throws SQLException
    {
        this.statement = connection.createStatement();

        statement.executeUpdate("TRUNCATE TABLE  dimas.table_lab4");

        String query = "insert into table_lab4 (prodid, title, cost)" + "VALUES (?, ?, ?)";
        PreparedStatement preparedStmt = connection.prepareStatement(query);
        for (int i = 1; i <= N; i++){
            preparedStmt.setInt(1, i*10);
            preparedStmt.setString(2, "product" + i);
            preparedStmt.setInt(3, i*10+1000);
            preparedStmt.execute();
        }
    }


    private boolean exist( String title ) throws SQLException
    {
        ResultSet resultSet = statement.executeQuery("SELECT * FROM dimas.table_lab4 where title='" + title + "'");
        return resultSet.next();
    }

    public void add(int prodid, String title, double cost ) throws SQLException
    {
        if (!exist(title)) {
            String query = "insert into table_lab4 (prodid, title, cost) VALUES (" + prodid + ",'" + title + "'," + cost + ")";
            statement.executeUpdate(query);
            System.out.println(title + " is added");
        } else {
            System.out.println(title + " is already exist");
        }
    }

    public void delete(String title) throws SQLException
    {
        if (exist(title)) {
            String query = "delete from table_lab4 where title='" + title + "'";
            statement.executeUpdate(query);
            System.out.println(title + " is deleted");
        } else {
            System.out.println(title + " doesn't exist");
        }
    }

    public void show_all() throws SQLException
    {
        ResultSet resultSet = statement.executeQuery("SELECT * FROM dimas.table_lab4 ");
        while(resultSet.next())
        {
            int id = resultSet.getInt(1);
            int prodid = resultSet.getInt(2);
            String title = resultSet.getString(3);
            double cost = resultSet.getDouble(4);
            System.out.format("id: %-5d  | prodid: %-5d | title: %-15s  | cost: %-10.2f\n", id, prodid, title, cost);
        }
    }

    public void change_price(String title, double cost) throws SQLException
    {
        if (exist(title)) {
            String query = "UPDATE table_lab4 SET cost = " + cost + " WHERE title = '" + title + "'";
            statement.executeUpdate(query);
            System.out.println(title + " price updated to " + cost);
        } else {
            System.out.println(title + " doesn't exist");
        }
    }

    public void price(String title) throws SQLException
    {
        if (exist(title)) {
            ResultSet resultSet = statement.executeQuery("SELECT * FROM dimas.table_lab4 where title='" + title + "'");
            while (resultSet.next())
            {
                System.out.println(title + " price is " + resultSet.getDouble(4));
            }
        } else {
            System.out.println(title + " doesn't exist");
        }
    }

    public void filter_by_price(double a, double b) throws SQLException
    {
        if (a > b) { a += b; b = a - b; a -= b; }

        ResultSet resultSet = statement.executeQuery("SELECT * FROM table_lab4");
        while(resultSet.next())
        {
            double cost = resultSet.getDouble(4);
            if (cost < b && cost > a) {
                int id = resultSet.getInt(1);
                int prodid = resultSet.getInt(2);
                String title = resultSet.getString(3);
                System.out.format("id: %-5d  | prodid: %-5d | title: %-15s  | cost: %-10.2f\n", id, prodid, title, cost);
            }
        }
    }

}
