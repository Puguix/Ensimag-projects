package org.ensimag;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.CrossOrigin;

import java.util.List;
@CrossOrigin(origins = "http://localhost:3000")
@RestController
public class RouletteController {

    @Autowired
    private RouletteService rouletteService;

    /**
     Method called from frontend, when player has placed their bets.
     @param rouletteBetList list of bets, from frontend
     @return result list of 2 elements: the number the roulette will land on, and the player's win
     */
    @PostMapping(path = "/roulette/bet", consumes = MediaType.APPLICATION_JSON_VALUE
    , produces = MediaType.APPLICATION_JSON_VALUE)
    public List<Integer> rouletteResult(@RequestBody List<RouletteBet> rouletteBetList){
        try{
            return rouletteService.getResults(rouletteBetList);
        }
        catch(RuntimeException e){
            throw e;
        }
    }

}