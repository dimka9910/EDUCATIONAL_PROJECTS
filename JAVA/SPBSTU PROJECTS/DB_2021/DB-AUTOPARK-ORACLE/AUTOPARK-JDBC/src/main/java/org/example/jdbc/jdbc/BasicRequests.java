package org.example.jdbc.jdbc;

import java.sql.*;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;

public interface BasicRequests<T> {
    T parser(ResultSet resultSet) throws SQLException;

    default List<T> getList(String stringQuery, Connection cn, Long ... id) throws SQLException {
        List<T> list = new LinkedList<>();
        try (PreparedStatement statement = cn.prepareStatement(stringQuery)) {

            for (int i = 0; i < statement.getParameterMetaData().getParameterCount(); i++){
                statement.setLong(i + 1, id[0]);
            }

            try (ResultSet result = statement.executeQuery()) {
                while (result.next()) {
                    list.add(parser(result));
                }
            }
        }
        return list;
    }

    default T getOne(String stringQuery, Connection cn, Long ... id) throws SQLException {
        try (PreparedStatement statement = cn.prepareStatement(stringQuery)) {
            for (int i = 0; i < statement.getParameterMetaData().getParameterCount(); i++) {
                statement.setLong(i + 1, id[0]);
            }
            try (ResultSet result = statement.executeQuery()) {
                if (result.next()) {
                    return parser(result);
                }
            }
        }
        throw new SQLException("NOT FOUND!!");
    }


    default Timestamp getCurrentTime(){
        return new Timestamp(new Date().getTime());
    }
}
