package engine.controller;

import java.util.Arrays;
import java.util.List;

import engine.entity.QuizEntity;
import engine.entity.UserEntity;
import engine.response.Response;
import engine.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;


@Controller
public class UserRestController {

    @Autowired
    UserService userService;

    @PostMapping(path = "/api/register")
    public ResponseEntity addUser(@Valid @RequestBody UserEntity userEntity) {
        try {
            System.out.println("$$$$$$$$$" + userEntity.getEmail());
            userService.addUser(userEntity);
            return ResponseEntity.ok("ok");
        } catch (Exception e) {
            return ResponseEntity.badRequest().build();
        }
    }

//    @RequestMapping(path = "/user/{id}", method = RequestMethod.GET)
//    public ResponseEntity listUser(@PathVariable(value = "id") String id) {
//        return new ResponseEntity(getUsers().stream().filter(user -> user.getId().equals(id)).findFirst().orElse(null), HttpStatus.OK);
//
//    }
//
//    @RequestMapping(path = "/user", method = RequestMethod.POST)
//    public ResponseEntity listUser(@RequestBody User user) {
//        return new ResponseEntity("18", HttpStatus.OK);
//    }
}