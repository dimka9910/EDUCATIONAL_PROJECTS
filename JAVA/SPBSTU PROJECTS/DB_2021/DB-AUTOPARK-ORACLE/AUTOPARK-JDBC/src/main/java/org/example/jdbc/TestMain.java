package org.example.jdbc;

import org.example.jdbc.jdbc.AutoDaoJdbc;

import java.sql.Connection;

public class TestMain {
    public static void main(String[] args) {
        Connection connection = DbConnection.getConnection();

        AutoDaoJdbc autoDaoJdbc = new AutoDaoJdbc();
        autoDaoJdbc.getAllCars().forEach(System.out::println);

    }
}
