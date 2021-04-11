<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>


<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Автомобили</title>
    <link rel="stylesheet" type="text/css" href="../../resources/css/style.css">
    <link rel="stylesheet" type="text/css" href="../../resources/css/table.css">
</head>
<body>
<div>
    <h2>АВТОМОБИЛИ  <a href="/" class="button brown">Главная</a></h2>
</div>

<div>

    <h3>Добавить машину</h3>
    <div>
        <div>
            <input id="add_num" name="num" type="text" placeholder="Num"
                   autofocus="true"/>
        </div>
        <div>
            <input id="add_color" name="color" type="text" placeholder="Color" autofocus="true"/>
            <button id="add_button" type="submit" class="button green">Add</button>
        </div>
        <div>
            <input id="add_mark" name="mark" type="text" placeholder="Mark" autofocus="true"/>
        </div>
    </div>

    <h3>Удалить автомобидль по ID</h3>
    <div>
        <div>
            <input id="delete_id" name="id" type="number" placeholder="id"
                   autofocus="true"/>
            <button id="delete_button" type="submit" class="button red">Delete</button>
        </div>

    </div>

</div>


<div>
    <h2>Список всех автомобидлей</h2>

    <select id="sort_column_select">
        <option disabled selected value> -- Сортировать по -- </option>
        <option value="1">ID</option>
        <option value="2">Num</option>
        <option value="3">Color</option>
        <option value="4">Mark</option>
    </select>
    <select id="sort_type_select">
        <option value="1">по возрастанию</option>
        <option value="2">по убыванию</option>
    </select>

    <table id='cars'>
        <tbody>
        <th>ID</th>
        <th>Num</th>
        <th>Color</th>
        <th>Mark</th>
        <th>User</th>
        <th width="1"></th>
        </tbody>
    </table>
    <button id="delete_all_button" type="submit" class="button red">Delete all</button>
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
        let table = document.getElementById('cars');

        fetch('/cars/get/all', {
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
                    td2.appendChild(document.createTextNode(tableInitData[index].num))
                    let td3 = document.createElement("TD")
                    td3.appendChild(document.createTextNode(tableInitData[index].color))
                    let td4 = document.createElement("TD")
                    td4.appendChild(document.createTextNode(tableInitData[index].mark))
                    let td5 = document.createElement("TD")
                    let tmp = (tableInitData[index].person == null) ? "FREE" : tableInitData[index].person.username
                    td5.appendChild(document.createTextNode(tmp))

                    let td6 = document.createElement("BUTTON");
                    td6.align="center"; td6.valign="center";
                    let text = document.createTextNode("Delete");
                    td6.appendChild(text);
                    td6.parentElement = row;
                    td6.onclick = function Delete(){
                        let good = {
                            id: tableInitData[index].id
                        };
                        fetch('/cars/delete/by/id', {
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
    document.getElementById('add_button').onclick = function add() {
        if (document.getElementById('add_num').value.trim() === ''
            || document.getElementById('add_color').value.trim() === ''
            || document.getElementById('add_mark').value.trim() === '') {
            alert("поле не может быть пустым");
            return;
        }

        //document.getElementById('add_button').style.visibility = 'hidden';

        let car = {
            num: document.getElementById('add_num').value.trim(),
            color: document.getElementById('add_color').value.trim(),
            mark: document.getElementById('add_mark').value.trim()
        };

        fetch('/cars/add', {
            method: 'post',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(car)
        })
            .then(res => res.json())
            .then(function (data) {
                console.log('Add car request succeeded with JSON response', data);
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
    document.getElementById('delete_button').onclick = function deleteByID() {
        if (document.getElementById('delete_id').value.trim() === '') {
            alert("поле не может быть пустым");
            return;
        }

        let car = {
            id: document.getElementById('delete_id').value.trim()
        };

        fetch('/cars/delete/by/id', {
            method: 'post',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(car)
        })
            .then(res => res.json())
            .then(function (data) {
                console.log('Delete by ID request succeeded with JSON response', data);
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
    document.getElementById('delete_all_button').onclick = function deleteAll() {
        fetch('/cars/delete/all', {
            method: 'post',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: ""
        })
            .then(res => res.json())
            .then(function (data) {
                console.log('Delete all cars request succeeded with JSON response', data);
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
        let table = (document.getElementById('cars'));
        let index = document.getElementById('sort_column_select').selectedIndex;
        let sortType = document.getElementById('sort_type_select').selectedIndex;
        let isNumber = (index === 1 || index === 3);
        sort(table, index - 1, sortType, isNumber);
    };

    document.getElementById('sort_type_select').onchange = function () {
        let table = (document.getElementById('cars'));
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