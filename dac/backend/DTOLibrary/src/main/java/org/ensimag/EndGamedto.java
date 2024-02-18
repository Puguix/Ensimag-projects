package org.ensimag;

import lombok.Data;

import java.util.List;

@Data
public class EndGamedto {

    public List<Carddto> playerHand;
    public List<Carddto> dealerHand;
    public double bet;

}
