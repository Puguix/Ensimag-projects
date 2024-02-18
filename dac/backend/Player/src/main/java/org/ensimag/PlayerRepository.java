package org.ensimag;

import org.springframework.data.repository.CrudRepository;

import java.util.Optional;

public interface PlayerRepository extends CrudRepository<Player, Long> {

    Optional<Player> findById(Long id);

    Optional<Player> findByEmail(String email);

}
