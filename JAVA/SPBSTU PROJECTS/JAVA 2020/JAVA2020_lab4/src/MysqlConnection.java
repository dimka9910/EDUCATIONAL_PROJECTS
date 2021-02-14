import java.sql.*;
import java.util.Properties;

public class MysqlConnection {

    //use singleton design patern
    private static MysqlConnection instance;
    public static MysqlConnection getInstance(){
        if(instance == null) {
            instance = new MysqlConnection();
        }
        return instance;
    }

    // init database constants
    private static final String DATABASE_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DATABASE_URL = "jdbc:mysql://localhost:3306/dimas?useUnicode=true&serverTimezone=UTC";
    private static final String USERNAME = "dimka";
    private static final String PASSWORD = "3939";

    // init connection object
    private Connection connection;
    // init properties object

    // connect database
    public Connection connect() {
        if (connection == null) {
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                connection = (Connection) DriverManager.getConnection(DATABASE_URL, USERNAME, PASSWORD);
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }
        }
        return connection;
    }

    /*/ disconnect  херь
    public void disconnect() {
        if(connection != null) {
            try {
                connection.close();
                connection = null;
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }*/

}