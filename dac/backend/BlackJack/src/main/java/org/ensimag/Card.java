package org.ensimag;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class Card {

    public enum Rank {
        ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    }

    public enum Suit {
        HEARTS, DIAMONDS, CLUBS, SPADES
    }

    private final Rank rank;
    private final Suit suit;

    /**
     * Method used to calculate the value of a card.
     * @return int, which is the value of a current card.
     */
    public int getValue() {
        return switch (rank) {
            case ACE -> 1;
            case TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN -> rank.ordinal()+1;
            case JACK, QUEEN, KING -> 10;
        };
    }
}