package org.ensimag;

import java.security.SecureRandom;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.security.web.SecurityFilterChain;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

@Configuration
@EnableWebSecurity
public class SecurityConfig implements WebMvcConfigurer {

    @Override
    public void addCorsMappings(CorsRegistry registry) {
        registry.addMapping("/**") // Apply to all endpoints
                // .allowedOrigins("*") // Allow this origin
                .allowedMethods("GET", "POST", "PUT", "DELETE", "OPTIONS") // Allow these methods
                .allowedHeaders("*") // Allow all headers
                .allowCredentials(true)
                .allowedOriginPatterns("https://*");
    }

    @Bean
    public SecurityFilterChain securityFilterChain(HttpSecurity http) throws Exception {
        http
                .authorizeHttpRequests((authorize) -> authorize
                        .anyRequest().permitAll())
                .csrf().disable();

        return http.build();
    }

    private static final String SALT = "easybet";

    @Bean
    public PasswordEncoder encoder() {
        return new BCryptPasswordEncoder(10, new SecureRandom(SALT.getBytes()));
    }

}
