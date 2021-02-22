package platform;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RestController;

import java.util.Collections;

@SpringBootApplication
public class CodeSharingPlatform {

    public static void main(String[] args) {

        //SpringApplication.run(CodeSharingPlatform.class, args);
        SpringApplication app = new SpringApplication(CodeSharingPlatform.class);
        app.setDefaultProperties(Collections
                .singletonMap("server.port", "8080"));
        app.run(args);
    }

}
