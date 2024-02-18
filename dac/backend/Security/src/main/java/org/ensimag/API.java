package org.ensimag;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.core.ParameterizedTypeReference;
import org.springframework.http.MediaType;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.web.reactive.function.BodyInserters;
import org.springframework.web.reactive.function.client.WebClient;

@Service
public class API {

    private static String playerApiUrl = "http://localhost:8084";
    private static String rouletteApiUrl = "http://localhost:8081";
    private static String blackjackApiUrl = "http://localhost:8083";
    private static String chipsApiUrl = "http://localhost:8082";

    private static WebClient playerClient;
    private static WebClient rouletteClient;
    private static WebClient blackjackClient;
    private static WebClient chipsClient;

    @Bean
    public static WebClient.Builder webClientBuilder() {
        return WebClient.builder();
    }

    @Bean
    public static JwtToken newJwtToken() {
        return new JwtToken();
    }

    @Autowired
    public PasswordEncoder passwordEncoder;

    public API(WebClient.Builder webClientBuilder) {
        playerClient = webClientBuilder.baseUrl(playerApiUrl).build();
        rouletteClient = webClientBuilder.baseUrl(rouletteApiUrl).build();
        blackjackClient = webClientBuilder.baseUrl(blackjackApiUrl).build();
        chipsClient = webClientBuilder.baseUrl(chipsApiUrl).build();
    }

    public Playerdto fetchPlayerByEmail(String email) {
        try {
            return playerClient.get().uri(playerApiUrl + "/player/{email}", email)
                    .retrieve().bodyToMono(Playerdto.class).block();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public List<Playerdto> fetchAllPlayers() {
        playerClient = webClientBuilder().baseUrl(playerApiUrl).build();
        try {
            List<Playerdto> result = new ArrayList<>();
            playerClient.get().uri(playerApiUrl + "/players")
                    .retrieve().bodyToFlux(Playerdto.class).toIterable().forEach(result::add);
            return result;
        } catch (RuntimeException e) {
            throw e;
        }

    }

    public Playerdto fetchPlayerById(Long playerId) {
        try {
            return playerClient.get().uri(playerApiUrl + "/players/{playerId}", playerId)
                    .retrieve().bodyToMono(Playerdto.class).block();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public Playerdto createPlayer(Playerdto newPlayer) {
        Playerdto encodedPlayer = new Playerdto(newPlayer.getId(),
                newPlayer.getEmail(), passwordEncoder.encode(newPlayer.getPassword()),
                newPlayer.getFirstName(), newPlayer.getSurname(), newPlayer.getDateOfBirth(), 0L);
        try {
            return playerClient.post().uri(playerApiUrl + "/players")
                    .contentType(MediaType.APPLICATION_JSON)
                    .body(BodyInserters.fromValue(encodedPlayer))
                    .retrieve().bodyToMono(Playerdto.class).block();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public Playerdto updatePlayer(Playerdto newPlayer, String token) {
        try {
            Playerdto currentPlayer = getPlayerByToken(token);
            newPlayer.setPassword(currentPlayer.getPassword());
            Playerdto encodedPlayer = new Playerdto(newPlayer.getId(),
                    newPlayer.getEmail(), passwordEncoder.encode(newPlayer.getPassword()),
                    newPlayer.getFirstName(), newPlayer.getSurname(), newPlayer.getDateOfBirth(),
                    newPlayer.getNbChip());
            return playerClient.put()
                    .uri(playerApiUrl + "/players/{playerId}", currentPlayer.getId())
                    .contentType(MediaType.APPLICATION_JSON)
                    .body(BodyInserters.fromValue(encodedPlayer))
                    .retrieve().bodyToMono(Playerdto.class).block();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public void deletePlayer(String token) {
        try {
            Playerdto currentPlayer = getPlayerByToken(token);
            playerClient.delete()
                    .uri(playerApiUrl + "players/{playerId}", currentPlayer.getId())
                    .retrieve()
                    .bodyToMono(Void.class)
                    .block();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public Playerdto getPlayerChips(String token) {
        try {
            System.out.println("ici");
            Playerdto currentPlayer = getPlayerByToken(token);
            return playerClient.get()
                    .uri(playerApiUrl + "/player/{playerEmail}", currentPlayer.getEmail())
                    .retrieve()
                    .bodyToMono(Playerdto.class)
                    .block();
        } catch (RuntimeException e) {
            System.out.println("erreur");
            System.out.println(e);
            throw e;
        }
    }

    public Playerdto addPlayerChips(String token, Long nbChip) {
        try {
            Playerdto currentPlayer = getPlayerByToken(token);
            currentPlayer.setNbChip(currentPlayer.getNbChip() + nbChip);
            return updatePlayer(currentPlayer, token);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public List<Integer> getRouletteResults(List<RouletteBetdto> rouletteBetList) {
        try {
            List<Integer> result = new ArrayList<>();
            rouletteClient.post().uri(rouletteApiUrl + "/roulette/bet")
                    .contentType(MediaType.APPLICATION_JSON)
                    .body(BodyInserters.fromValue(rouletteBetList))
                    .retrieve().bodyToFlux(Integer.class).toIterable().forEach(integer -> result.add(integer));
            return result;
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public List<Gamedto> startBlackJack() {
        try {
            List<Gamedto> result = new ArrayList<>();
            blackjackClient.get().uri(blackjackApiUrl + "/blackjack/start-game")
                    .retrieve().bodyToFlux(Gamedto.class).toIterable().forEach(gamedto -> result.add(gamedto));
            return result;
        } catch (RuntimeException e) {
            throw e;
        }

    }

    public double getBlackJackPayoff(EndGamedto endGame) {
        try {
            return blackjackClient.post().uri(blackjackApiUrl + "/blackjack/getPayoff")
                    .contentType(MediaType.APPLICATION_JSON)
                    .body(BodyInserters.fromValue(endGame))
                    .retrieve().bodyToMono(Double.class).block();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    public long getNewChips(double profit, List<RouletteBetdto> rouletteBetList) {
        int bets = 0;
        for (RouletteBetdto rouletteBet : rouletteBetList) {
            bets += rouletteBet.getAmount();
        }
        return (long) (profit - bets);
    }

    public double getPrice(ChipsConversiondto chipsConversion) {
        try {
            return chipsClient.post().uri(chipsApiUrl + "/getPrice")
                    .contentType(MediaType.APPLICATION_JSON)
                    .body(BodyInserters.fromValue(chipsConversion))
                    .retrieve().bodyToMono(Double.class).block();
        } catch (NullPointerException e) {

            throw e;
        }

    }

    public Map<String, Double> getAllPrices() {
        try {
            return chipsClient.get().uri(chipsApiUrl + "/getPrice")
                    .retrieve().bodyToMono(new ParameterizedTypeReference<Map<String, Double>>() {
                    })
                    .block();
        } catch (UnsupportedOperationException e) {
            throw e;
        }

    }

    public Playerdto getPlayerByToken(String token) {
        String email = newJwtToken().getEmailFromToken(token);
        return fetchPlayerByEmail(email);
    }

}