package org.example.jdbc;

import lombok.extern.slf4j.Slf4j;

import oracle.jdbc.driver.OracleDriver;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

@Slf4j
public class DbConnection {

    public static String jdbcUrl = "jdbc:oracle:thin:@localhost:1521:XE";
    private static DbConnection instance;
    private Connection connection;

    private DbConnection(){
        try {
            Class.forName("oracle.jdbc.driver.OracleDriver");
            this.connection = DriverManager.getConnection(jdbcUrl, "c##test", "MyPass");
            log.info("Successful DB connection");
        } catch (SQLException | ClassNotFoundException e) {
            log.error(e.getMessage());
        }
    }

    public static Connection getConnection(String ... str) {
        if (instance == null){
            instance = new DbConnection();
        }
        return instance.connection;
    }
}
