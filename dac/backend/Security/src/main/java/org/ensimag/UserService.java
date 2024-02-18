package org.ensimag;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.web.reactive.function.client.WebClient;

@Service
public class UserService {

    @Autowired
    WebClient.Builder webClientBuilder = WebClient.builder();

    @Autowired
    API api = new API(webClientBuilder);

    @Autowired
    JwtToken jwtToken = new JwtToken();

    @Autowired
    PasswordEncoder passwordEncoder;

    public UserDetails loadUserByEmail(String email) {
        Playerdto player = api.fetchPlayerByEmail(email);
        return new PrincipalPlayer(player);
    }

    public void checkAuthenticity(String token, Long playerId) {
        Playerdto player = api.fetchPlayerById(playerId);
        try {
            if (!token.equals(jwtToken.generateToken(player.getEmail()))) {
                throw new RuntimeException("Unauthorized");
            }
        } catch (NullPointerException e) {
            throw new NullPointerException("Player not found with id: " + playerId);
        }
    }

    public String login(String email, String encodedPassword) {
        Playerdto player = api.fetchPlayerByEmail(email);
        try {
            System.out.println(encodedPassword);
            System.out.println(player.getPassword());
            String playerPassword = player.getPassword();
            if (passwordEncoder.matches(encodedPassword, playerPassword)) {
                System.out.println("passwords match !!!!!!!!!!!");
                return jwtToken.generateToken(email);
            } else {
                throw new RuntimeException("Passwords do not match");
            }
        } catch (NullPointerException e) {
            throw new NullPointerException("Player not found with email: " + email);
        }
    }
}