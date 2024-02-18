package org.ensimag;

import lombok.Data;

import java.util.List;

@Data
public class EndGame {

    public List<Card> playerHand;
    public List<Card> dealerHand;
    public double bet;

}
