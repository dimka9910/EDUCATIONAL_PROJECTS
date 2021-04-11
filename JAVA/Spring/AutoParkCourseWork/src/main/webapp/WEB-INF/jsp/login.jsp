<%@ taglib prefix="sec" uri="http://www.springframework.org/security/tags" %>
<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>

<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>Log in with your account</title>
    <link rel="stylesheet" type="text/css" href="../../resources/css/style.css">
</head>

<sec:authorize access="isAuthenticated()">
    <% response.sendRedirect("/"); %>
</sec:authorize>
<div>
    <h1>Вход в систему</h1>
</div>
<div>
    <form method="POST" action="/login">
        <div>
            <input name="username" type="text" placeholder="Username"
                   autofocus="true"/>
        </div>
        <div>
            <input name="password" type="password" placeholder="Password"/>
        </div>
        <div>
            <button type="submit">Log In</button>
        </div>
    </form>
    <a href="/registration" class="button gray">Зарегистрироваться</a>
</div>
<div>
    <a href="/" class="button gray">Главная</a>
</div>
</body>
</html>