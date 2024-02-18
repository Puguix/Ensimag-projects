package org.ensimag;

import lombok.Data;

import java.util.List;

@Data
public class Gamedto {

    public List<Carddto> cards;
    public List<Integer> scores;

}
