package org.ensimag;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.Optional;

@Service
public class PlayerService {

    @Autowired
    private PlayerRepository playerRepository;

    public Iterable<Player> getPlayers() {
        return playerRepository.findAll();
    }

    public Optional<Player> getPlayerById(Long id) {
        return playerRepository.findById(id);
    }

    public Optional<Player> getPlayerByEmail(String email) {
        return playerRepository.findByEmail(email);
    }

    public Player createPlayer(Player newPlayer) {
        return playerRepository.save(newPlayer);
    }

    public Player updatePlayer(Player newPlayer, Long id) {
        return playerRepository.findById(id)
                .map(player -> {
                    player.setEmail(newPlayer.getEmail());
                    player.setNbChip(newPlayer.getNbChip());
                    player.setPassword(newPlayer.getPassword());
                    return playerRepository.save(player);
                })
                .orElseGet(() -> {
                    newPlayer.setId(id);
                    return playerRepository.save(newPlayer);
                });
    }

    public void deletePlayerById(Long id) {
        playerRepository.deleteById(id);
    }

    public Long getPlayerChips(Long playerId) {
        return playerRepository.findById(playerId)
                .map(player -> {
                    return player.getNbChip();
                })
                .orElseThrow(() -> new RuntimeException("Player not found with id: " + playerId));
    }

    public Player updatePlayerChips(Long playerId, Long newChips) {
        return playerRepository.findById(playerId)
                .map(player -> {
                    player.setNbChip(newChips);
                    return playerRepository.save(player);
                })
                .orElseThrow(() -> new RuntimeException("Player not found with id: " + playerId));
    }

}
