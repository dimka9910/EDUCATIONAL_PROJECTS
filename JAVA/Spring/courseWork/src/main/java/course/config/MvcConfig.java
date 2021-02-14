package course.config;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.ViewControllerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
public class MvcConfig implements WebMvcConfigurer {

    @Override
    public void addViewControllers(ViewControllerRegistry registry) {
        registry.addViewController("/login").setViewName("login");
        registry.addViewController("/registration").setViewName("registration");
        registry.addViewController("/users").setViewName("users");
        registry.addViewController("/cars").setViewName("cars");
        registry.addViewController("/routes").setViewName("routes");
        registry.addViewController("/journal").setViewName("journal");
        registry.addViewController("/start").setViewName("start");
    }
}
