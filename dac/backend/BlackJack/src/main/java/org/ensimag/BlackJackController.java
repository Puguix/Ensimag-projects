package org.ensimag;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
@CrossOrigin(origins = "http://localhost:3000")
@RestController
public class BlackJackController {

    @Autowired
    private BlackJackService blackJackService;

    @GetMapping(path = "/blackjack/start-game", produces = MediaType.APPLICATION_JSON_VALUE)
    public List<Game> startGame(){
        try{
            return blackJackService.startGame();
        }
        catch(RuntimeException e){
            throw e;
        }
    }
        
    @PostMapping(path = "/blackjack/getPayoff", consumes = MediaType.APPLICATION_JSON_VALUE, produces = MediaType.APPLICATION_JSON_VALUE)
    public double getPayoff(@RequestBody EndGame endGame){
        try{
            return blackJackService.getPayoff(endGame);
        }
        catch(RuntimeException e){
            throw e;
        }        
    }

}
