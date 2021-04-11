package engine;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class WebQuizEngine {

    public static void main(String[] args) throws InterruptedException {
        Thread.sleep(200);
        SpringApplication.run(WebQuizEngine.class, args);
    }
    
}
