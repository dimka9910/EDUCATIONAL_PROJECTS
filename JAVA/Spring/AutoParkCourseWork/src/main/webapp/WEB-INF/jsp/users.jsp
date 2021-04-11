<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Пользователи</title>
    <link rel="stylesheet" type="text/css" href="../../resources/css/style.css">
    <link rel="stylesheet" type="text/css" href="../../resources/css/table.css">
</head>

<body>
<div>
    <h3>Список всех пользователь<a href="/" class="button brown">Главная</a></h3>

    <select id="sort_column_select">
        <option disabled selected value> -- Сортировать по -- </option>
        <option value="1">ID</option>
        <option value="2">UserName</option>
        <option value="3">Password</option>
        <option value="4">Role</option>
    </select>
    <select id="sort_type_select">
        <option value="1">по возрастанию</option>
        <option value="2">по убыванию</option>
    </select>


    <table id='users'>
        <tbody>
        <th>ID</th>
        <th>UserName</th>
        <th>Password</th>
        <th>Role</th>
        <th width="1"></th>
        </tbody>
    </table>
</div>

<script>
    window.onload = function initTable() {
        let tableData;
        let table = document.getElementById('users');

        fetch('/users/get/all', {
            method: 'get'
        })
            .then(res => res.json())
            .then(function (data) {
                console.log('Get users request succeeded with JSON response', data);
                tableData = data;
                let tbody = table.getElementsByTagName("TBODY")[0];

                for (let index = 0; index < data.length; index++) {
                    let row = document.createElement("TR")
                    let td1 = document.createElement("TD")
                    td1.appendChild(document.createTextNode(data[index].id))
                    let td2 = document.createElement("TD")
                    td2.appendChild(document.createTextNode(data[index].username))
                    let td3 = document.createElement("TD")
                    td3.appendChild(document.createTextNode(data[index].password))
                    let td4 = document.createElement("TD")
                    td4.appendChild(document.createTextNode(data[index].roles))
                    let td5 = document.createElement("BUTTON")
                    let text = document.createTextNode("Delete");
                    td5.appendChild(text);
                    td5.onclick = function Delete(){
                        let user = {
                            id: tableData[index].id
                        };
                        fetch('/users/delete/by/id', {
                            method: 'post',
                            headers: {
                                'Content-Type': 'application/json;charset=utf-8'
                            },
                            body: JSON.stringify(user)
                        })
                            .then(res => res.json())
                            .then(function (data) {
                                console.log('Delete user request succeeded with JSON response', data);
                                if (data.success === false) {
                                    alert(data.error)
                                } else {
                                    document.location.reload()
                                }
                            })
                            .catch(function (error) {
                                console.error('Request FAILED ', error);
                            });
                    }

                    row.appendChild(td1);
                    row.appendChild(td2);
                    row.appendChild(td3);
                    row.appendChild(td4);
                    row.appendChild(td5);
                    tbody.appendChild(row);
                }
            })
            .catch(function (error) {
                console.error('Request FAILED ', error);
            });
    }
</script>

<script>
    document.getElementById('sort_column_select').onchange = function () {
        let table = (document.getElementById('users'));
        let index = document.getElementById('sort_column_select').selectedIndex;
        let sortType = document.getElementById('sort_type_select').selectedIndex;
        let isNumber = (index === 1 || index === 3);
        sort(table, index - 1, sortType, isNumber);
    };

    document.getElementById('sort_type_select').onchange = function () {
        let table = (document.getElementById('users'));
        let index = document.getElementById('sort_column_select').selectedIndex;
        let sortType = document.getElementById('sort_type_select').selectedIndex;
        let isNumber = (index === 1 || index === 3);
        sort(table, index - 1, sortType, isNumber);
    };

    function sort(table, index, sortType, isNumber) {
        let sortedRows;
        if (sortType === 0) {
            if (isNumber){
                sortedRows = Array.from(table.rows)
                    .slice(1)
                    .sort((rowA, rowB) => (rowA.cells[index].innerHTML - rowB.cells[index].innerHTML > 0) ? 1 : -1);
            } else {
                sortedRows = Array.from(table.rows)
                    .slice(1)
                    .sort((rowA, rowB) => rowA.cells[index].innerHTML > rowB.cells[index].innerHTML ? 1 : -1);
            }
        } else if (sortType === 1){
            if (isNumber){
                sortedRows = Array.from(table.rows)
                    .slice(1)
                    .sort((rowA, rowB) => (rowA.cells[index].innerHTML - rowB.cells[index].innerHTML < 0) ? 1 : -1);
            } else {
                sortedRows = Array.from(table.rows)
                    .slice(1)
                    .sort((rowA, rowB) => rowA.cells[index].innerHTML < rowB.cells[index].innerHTML ? 1 : -1);
            }
        }
        table.tBodies[0].append(...sortedRows);
    }
</script>

</body>
</html>