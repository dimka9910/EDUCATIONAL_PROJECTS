package course;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
    }
/*
    @Bean
    public CommandLineRunner test(RoleRepository Urepository){
        return args -> {
            Urepository.save(new Role((long) 1, "ADMIN"));

        };
    }*/

}
