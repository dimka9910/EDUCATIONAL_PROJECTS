package com.example.demoRestController;

import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class BotController {

    @PostMapping(value = "/greet", consumes = "application/json")
    public String greet(@RequestBody UserInfo userInfo) {
        if (userInfo.isEnabled()) {
            return String.format("Hello! Nice to see you, %s!", userInfo.getName());
        } else return String.format("Hello! Nice to see you, %s! Your account is disabled", userInfo.getName());
    }
    
        @PostMapping(value = "/greet2", consumes = "application/json")
    public String greet2(@RequestBody List<UserInfo> userInfoList) {
        //logging out users
        return String.format("OK, %d of user have been log out!", userInfoList.size());
    }

}
