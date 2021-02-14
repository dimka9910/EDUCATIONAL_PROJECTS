import java.sql.*;
import java.util.Scanner;

public class CreateDBJdbc {


    private static Connection connection;
    private static Statement statement;
    private static ResultSet resultset;
    static String query = "";


    public static void main(String[] args) throws SQLException
    {
        MysqlConnection conn = MysqlConnection.getInstance();
        connection = conn.connect();

        Scanner in0 = new Scanner(System.in);
        System.out.print("Input N: ");
        int N = in0.nextInt();
        Handler handler = new Handler(connection, N);


        Scanner in = new Scanner(System.in);
        System.out.print("Input a command: ");
        while(in.hasNextLine()) {

            String command = in.nextLine();
            String[] s = command.split(" ");

            try
            {
                switch (s[0])
                {
                    case "/add":

                        handler.add(Integer.parseInt(s[1]), s[2], Double.parseDouble(s[3]));
                        break;

                    case "/d": //case "/delete":

                        handler.delete(s[1]);
                        break;

                    case "/sa": //case "/show_all":

                        handler.show_all();
                        break;

                    case "/p": //case "/price":

                        handler.price(s[1]);
                        break;

                    case ("/cp"): //case ("/change_price"):

                        handler.change_price(s[1], Double.parseDouble(s[2]));
                        break;

                    case "/fbp": //case "/filter_by_price":

                        handler.filter_by_price(Double.parseDouble(s[1]), Double.parseDouble(s[2]));
                        break;

                    case "exit":
                        System.exit(0);

                    default:
                        System.out.println("Wrong command!");
                        break;
                }
            } catch (Exception e) {
                System.out.println("ERROR!");
            }
            System.out.println("Input a command: ");
        }


    }
}
