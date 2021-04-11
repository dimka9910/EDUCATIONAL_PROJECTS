<%@ taglib prefix="form" uri="http://www.springframework.org/tags/form" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Регистрация</title>
    <link rel="stylesheet" type="text/css" href="../../resources/css/style.css">
</head>

<body>
<div>
    <h1>Регистрация</h1>
</div>
<div>
    <div>
        <div>
            <input id="register_username" name="username" type="text" placeholder="username"
                   autofocus="true"/>
        </div>
        <div>
            <input id="register_password" name="password" type="text" placeholder="password"/>
        </div>
        <div>
            <input id="register_passwordConfirm" name="passwordConfirm" type="text" placeholder="password confirm"/>
        </div>
        <div>
            <button id="register_button" type="submit">Register</button>
        </div>
    </div>
    <a href="/" class="button gray">Главная</a>
</div>

<script>
    document.getElementById('register_button').onclick = function add() {
        if (document.getElementById('register_username').value === '' || document.getElementById('register_password').value === '' || document.getElementById('register_passwordConfirm').value === '')
        {
            alert("Поле не может быть пустым");
            return;
        }

        if (document.getElementById('register_password').value !== document.getElementById('register_passwordConfirm').value)
        {
            alert("Пароли не совпадают");
            return;
        }

        let user = {
            username: document.getElementById('register_username').value,
            password: document.getElementById('register_password').value
        };

        fetch('/register', {
            method: 'post',
            headers: {
                'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify(user)
        })
            .then(res => res.json())
            .then(function (data) {
                console.log('Add user request succeeded with JSON response', data);
                if (data.success === false) {
                    alert(data.error)
                } else {
                    window.location.replace("/login");
                }
            })
            .catch(function (error) {
                console.error('Request FAILED ', error);
            });
    }
</script>

</body>
</html>