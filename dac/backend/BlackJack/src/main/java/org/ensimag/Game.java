package org.ensimag;

import lombok.Data;

import java.util.ArrayList;
import java.util.List;

@Data
public class Game {

    public List<Card> cards;
    public List<Integer> scores;

    public Game(){
        this.cards = new ArrayList<>();
        this.scores = new ArrayList<>();
    }

}
