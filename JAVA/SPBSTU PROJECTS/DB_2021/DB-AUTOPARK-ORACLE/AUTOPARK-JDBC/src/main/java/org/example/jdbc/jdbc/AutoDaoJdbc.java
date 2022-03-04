package org.example.jdbc.jdbc;

import com.github.dimka9910.documents.dto.user.UserDto;
import com.github.dimka9910.documents.dto.user.UserRolesEnum;
import lombok.extern.slf4j.Slf4j;
import org.example.dto.AutoDto;
import org.example.jdbc.DbConnection;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.List;

@Slf4j
public class AutoDaoJdbc implements BasicRequests{
    Connection cn = DbConnection.getConnection();

    @Override
    public AutoDto parser(ResultSet resultSet) throws SQLException {
        int id = resultSet.getInt("id");
        String num = resultSet.getString("num");
        String color = resultSet.getString("color");
        String mark = resultSet.getString("mark");
        int personnel_id = resultSet.getInt("personnel_id");
        return AutoDto.builder()
                .id(id)
                .num(num)
                .color(color)
                .mark(mark)
                .personnel_id(personnel_id)
                .build();
    }


    public List<AutoDto> getAllCars() {
        String stringQuery = "SELECT * FROM AUTO";
        List<AutoDto> list = new LinkedList<>();
        try {
            return getList(stringQuery, cn);
        } catch (SQLException e) {
            log.error(e.getMessage());
        }
        return list;
    }

}
