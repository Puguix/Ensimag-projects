package org.ensimag;

import lombok.Data;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import org.ensimag.Card.*;

@Data
public class Deck {

    private List<Card> cards;

    public Deck() {
        cards = new ArrayList<>();
        for (Rank rank : Rank.values()) {
            for (Suit suit : Suit.values()) {
                cards.add(new Card(rank, suit));
            }
        }
    }

    public void shuffle() {
        Collections.shuffle(cards);
    }

    public Card dealCard() {
        if (cards.isEmpty()) {
            throw new IllegalStateException("The deck is empty. No more cards to deal.");
        }
        return cards.remove(0);
    }

}