package course.controller.rest;

import course.controller.response.SimpleResponse;
import course.entity.Role1;
import course.entity.User;
import course.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collections;

import static course.entity.Role1.ADMIN;

@RestController
public class RegistrationRestController {
    @Autowired
    private UserService service;

    @PostMapping(value = "/register")
    public SimpleResponse register(@RequestBody User user) {
        try {
            //user.setRoles(course.entity.Role1.values(1));
            //user.setRoles(Collections.singleton(ADMIN));
            service.addUser(user);
        } catch (javax.validation.ConstraintViolationException ex) {
            return new SimpleResponse(false, "Слишком короткий псевдоним. Минимум 4 знака");
        } catch (UnsupportedOperationException ex) {
            return new SimpleResponse(false, "Пользователь с таким именем уже существует");
        }
        return new SimpleResponse(true);
    }

}
