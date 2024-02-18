package org.ensimag;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.reactive.function.client.WebClient;

import java.util.List;
import java.util.Map;

@CrossOrigin(origins = "http://localhost:3000")
@RestController
public class SecurityController {

    @Autowired
    WebClient.Builder webClientBuilder = WebClient.builder();

    @Autowired
    API api = new API(webClientBuilder);

    @Autowired
    UserService userService;

    @GetMapping("/allplayers")
    public List<Playerdto> getPlayers() {
        return api.fetchAllPlayers();
    }

    @GetMapping("/players")
    public Playerdto getPlayerById(@RequestHeader String token) {
        return api.getPlayerByToken(token);
    }

    @GetMapping("/player/{email}")
    public Playerdto getPlayerByEmail(@PathVariable String email) {
        return api.fetchPlayerByEmail(email);
    }

    @PostMapping("/players")
    public Playerdto newPlayer(@RequestBody Playerdto newPlayer) {
        System.out.println(newPlayer.dateOfBirth);
        return api.createPlayer(newPlayer);
    }

    @PutMapping("/players")
    public Playerdto updatePlayer(@RequestBody Playerdto newPlayer, @RequestHeader String token) {
        return api.updatePlayer(newPlayer, token);
    }

    @DeleteMapping("/players")
    public void deletePlayer(@RequestHeader String token) {
        api.deletePlayer(token);
    }

    @GetMapping("/players/chips")
    public Long getPlayerChips(@RequestHeader String token) {
        Playerdto currentPlayer = api.getPlayerChips(token);
        return currentPlayer.getNbChip();
    }

    @PutMapping("/players/chips")
    public Playerdto updatePlayerChips(@RequestHeader String token, @RequestBody Long newChips) {
        return api.addPlayerChips(token, newChips);
    }

    @PostMapping("/players/login")
    public String login(@RequestBody LoginRequest loginRequest) {
        return userService.login(loginRequest.getEmail(), loginRequest.getPassword());
    }

    @GetMapping("/players/token")
    public Playerdto getPlayerByToken(@RequestHeader String token) {
        return api.getPlayerByToken(token);
    }

    @PostMapping(path = "/roulette/bet", consumes = MediaType.APPLICATION_JSON_VALUE, produces = MediaType.APPLICATION_JSON_VALUE)
    public List<Integer> rouletteResult(@RequestBody List<RouletteBetdto> rouletteBetList,
            @RequestHeader String token) {
        List<Integer> result = api.getRouletteResults(rouletteBetList);
        long nbChip = api.getNewChips(result.get(0), rouletteBetList);
        api.addPlayerChips(token, nbChip);
        return result;
    }

    @GetMapping("/blackjack/start-game")
    public List<Gamedto> startGame() {
        return api.startBlackJack();
    }

    @PostMapping("/blackjack/getPayoff")
    public double getPayoff(@RequestBody EndGamedto endGame, @RequestHeader String token) {
        double profit = api.getBlackJackPayoff(endGame);
        api.addPlayerChips(token, (long) (profit - endGame.getBet()));
        return profit;
    }

    /**
     * Method called from frontend to know the price of the chips they want to buy
     * in the specified currency.
     *
     * @param chipsConversion parameters of conversion (currency and number of
     *                        chips), from frontend
     * @return result double: the price in the currency asked for the number of
     *         chips
     */
    @PostMapping(path = "/getPrice", consumes = MediaType.APPLICATION_JSON_VALUE, produces = MediaType.APPLICATION_JSON_VALUE)
    public double getPrice(@RequestBody ChipsConversiondto chipsConversion) {
        return api.getPrice(chipsConversion);
    }

    /**
     * Method called from frontend to know the price of one chip in all currencies
     *
     * @return result List<double>: the price off one chip in all currencies
     */
    @GetMapping(path = "/getAllPrices", consumes = MediaType.APPLICATION_JSON_VALUE, produces = MediaType.APPLICATION_JSON_VALUE)
    public Map<String, Double> getAllPrices() {
        return api.getAllPrices();
    }

}