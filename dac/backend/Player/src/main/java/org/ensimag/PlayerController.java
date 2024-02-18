package org.ensimag;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.bind.annotation.CrossOrigin;

import java.util.Optional;

@CrossOrigin(origins = "http://localhost:3000")
@RestController
public class PlayerController {

    @Autowired
    private PlayerService playerService;

    @GetMapping("/players")
    public Iterable<Player> getPlayers() {
        try {
            System.out.println("on est là");
            return playerService.getPlayers();
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @GetMapping("/players/{playerId}")
    public Optional<Player> getPlayerById(@PathVariable Long playerId) {
        try {
            return playerService.getPlayerById(playerId);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @GetMapping("/player/{email}")
    public Optional<Player> getPlayerByEmail(@PathVariable String email) {
        try {
            return playerService.getPlayerByEmail(email);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @PostMapping("/players")
    public Player newPlayer(@RequestBody Player newPlayer) {
        try {
            System.out.println(newPlayer.getDateOfBirth());
            return playerService.createPlayer(newPlayer);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @PutMapping("/players/{playerId}")
    public Player updatePlayer(@RequestBody Player newPlayer, @PathVariable Long playerId) {
        try {
            return playerService.updatePlayer(newPlayer, playerId);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @DeleteMapping("/players/{playerId}")
    void deletePlayer(@PathVariable Long playerId) {
        try {
            playerService.deletePlayerById(playerId);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @GetMapping("/players/{playerId}/chips")
    public Long getPlayerChips(@PathVariable Long playerId) {
        try {
            return playerService.getPlayerChips(playerId);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @PutMapping("/players/{playerId}/chips")
    public Player updatePlayerChips(@PathVariable Long playerId, @RequestBody Long newChips) {
        try {
            return playerService.updatePlayerChips(playerId, newChips);
        } catch (RuntimeException e) {
            throw e;
        }
    }

    @PutMapping("/players/{playerId}/addchips")
    public Player addPlayerChips(@PathVariable Long playerId, @RequestBody Long nbChips,
            @RequestHeader("token") String token) {
        try {
            return playerService.updatePlayerChips(playerId, nbChips);
        } catch (RuntimeException e) {
            throw e;
        }
    }

}