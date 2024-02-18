package org.ensimag;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Playerdto {

    public Long id;
    public String email;
    public String password;
    public String firstName;
    public String surname;
    public String dateOfBirth;
    public Long nbChip;

}