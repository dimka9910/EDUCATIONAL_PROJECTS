<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>


<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Журнал</title>
    <link rel="stylesheet" type="text/css" href="../../resources/css/style.css">
    <link rel="stylesheet" type="text/css" href="../../resources/css/table.css">
</head>
<body>
<div>
    <h2>ЖУРНАЛ <a href="/" class="button brown">Главная</a></h2>
</div>

<div>


</div>


<div>

    <select id="sort_column_select">
        <option disabled selected value> -- Сортировать по -- </option>
        <option value="1">ID</option>
        <option value="2">time out</option>
        <option value="3">time in</option>
        <option value="4">car</option>
        <option value="5">road</option>
    </select>
    <select id="sort_type_select">
        <option value="1">по возрастанию</option>
        <option value="2">по убыванию</option>
    </select>

    <table id='journal'>
        <tbody>
        <th>ID</th>
        <th>time out</th>
        <th>time in</th>
        <th>car</th>
        <th>road</th>
        <th width="1"></th>
        </tbody>
    </table>


    <div>
        <button id="delete_all_button" class="button red">Delete all</button>
    </div>

</div>

<script>
    window.onkeydown = function(event){
        if (event.key === 'Enter') {
            let edit = document.getElementById('edit');
            if (edit !== null) {
                edit.blur();
            }
        }
    }
</script>


<script>
    window.onload = function initTable() {
        let table = document.getElementById('journal');

        fetch('/journal/get/all', {
            method: 'get'
        })
            .then(res => res.json())
            .then(function (tableInitData) {
                console.log('Get cars request succeeded with JSON response', tableInitData);

                let tbody = table.getElementsByTagName("TBODY")[0];

                for (let index = 0; index < tableInitData.length; index++) {
                    let row = document.createElement("TR")
                    let td1 = document.createElement("TD")
                    td1.appendChild(document.createTextNode(tableInitData[index].id))
                    let td2 = document.createElement("TD")
                    //let date = (tableInitData[index].time_out).slice(0,10)
                    let time = (tableInitData[index].time_out).slice(0,10) + ' ' + (tableInitData[index].time_out).slice(11,19)
                    td2.appendChild(document.createTextNode(time))
                    let td3 = document.createElement("TD")
                    let tmp0 = (tableInitData[index].time_in == null) ? "В ПУТИ" : ((tableInitData[index].time_in).slice(0,10) + ' ' + (tableInitData[index].time_in).slice(11,19))
                    td3.appendChild(document.createTextNode(tmp0))

                    let td4 = document.createElement("TD")
                    td4.appendChild(document.createTextNode(tableInitData[index].auto.num))
                    let td5 = document.createElement("TD")
                    td5.appendChild(document.createTextNode(tableInitData[index].route.name))

                    let td6 = document.createElement("BUTTON");
                    td6.align="center"; td6.valign="center";
                    let text = document.createTextNode("Delete");
                    td6.appendChild(text);
                    td6.parentElement = row;
                    td6.onclick = function Delete(){
                        let good = {
                            id: tableInitData[index].id
                        };
                        fetch('/journal/delete/by/id', {
                            method: 'post',
                            headers: {
                                'Content-Type': 'application/json;charset=utf-8'
                            },
                            body: JSON.stringify(good)
                        })
                            .then(res => res.json())
                            .then(function (data) {
                                console.log('Delete sale request succeeded with JSON response', data);
                                if (data.success === false) {
                                    alert(data.error)
                                } else {
                                    row.remove();
                                    document.location.reload();
                                }
                            })
                            .catch(function (error) {
                                console.error('Request FAILED ', error);
                            });
                    };

                    row.appendChild(td1);
                    row.appendChild(td2);
                    row.appendChild(td3);
                    row.appendChild(td4);
                    row.appendChild(td5);
                    row.appendChild(td6);
                    tbody.appendChild(row);
                }
            })
            .catch(function (error) {
                console.error('Request FAILED ', error);
            });
    }
</script>

<script>
    document.getElementById('delete_all_button').onclick = function deleteAll() {
        fetch('/journal/delete/all', {
            method: 'post',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: ""
        })
            .then(res => res.json())
            .then(function (data) {
                console.log('Delete all goods request succeeded with JSON response', data);
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
</script>

<script>
    document.getElementById('sort_column_select').onchange = function () {
        let table = (document.getElementById('journal'));
        let index = document.getElementById('sort_column_select').selectedIndex;
        let sortType = document.getElementById('sort_type_select').selectedIndex;
        let isNumber = (index === 1 || index === 3);
        sort(table, index - 1, sortType, isNumber);
    };

    document.getElementById('sort_type_select').onchange = function () {
        let table = (document.getElementById('journal'));
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