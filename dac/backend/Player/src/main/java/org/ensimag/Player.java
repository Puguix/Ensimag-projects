package org.ensimag;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Data
@NoArgsConstructor
@AllArgsConstructor
public class Player {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    @Column(unique = true)
    private String email;
    private String password;
    private String firstName;
    private String surname;
    private String dateOfBirth;
    private Long nbChip;

    public Player(String email, String password, String firstName, String surname, String dateOfBirth, Long nbChip) {
        this.email = email;
        this.password = password;
        this.firstName = firstName;
        this.surname = surname;
        this.dateOfBirth = dateOfBirth;
        this.nbChip = nbChip;
    }

    public Player(String email, String password, String firstName, String surname, String dateOfBirth) {
        this.email = email;
        this.password = password;
        this.firstName = firstName;
        this.surname = surname;
        this.dateOfBirth = dateOfBirth;
        this.nbChip = 0L;
    }
}