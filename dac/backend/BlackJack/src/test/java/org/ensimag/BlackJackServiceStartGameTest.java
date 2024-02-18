package org.ensimag;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;

@ExtendWith(MockitoExtension.class)
public class BlackJackServiceStartGameTest {

    @Test
    public void testInitPlayerGame_Ace_Value11() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.TWO, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.FIVE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.TWO, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.FIVE, Card.Suit.CLUBS));

        Game game = blackJackService.initPlayerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(13, 16, 21), game.getScores());
    }

    @Test
    public void testInitPlayerGame_Ace_Value1() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));

        Game game = blackJackService.initPlayerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(14, 14, 21), game.getScores());
    }

    @Test
    public void testInitPlayerGame_With_Diminuting_Score() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.SEVEN, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));

        Game game = blackJackService.initPlayerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(18, 15, 22), game.getScores());
    }

    @Test
    public void testInitPlayerGame_With_Maximum_Number_Of_Cards() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.TWO, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));
        finalCards.add(new Card(Card.Rank.THREE, Card.Suit.CLUBS));

        Game game = blackJackService.initPlayerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(12, 13, 14, 16, 18, 20, 12, 15, 18, 21), game.getScores());
    }

    @Test
    public void testInitDealerGame_BlackJack() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.KING, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.ACE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.FOUR, Card.Suit.SPADES));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.KING, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.ACE, Card.Suit.DIAMONDS));

        Game game = blackJackService.initDealerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(10, 21), game.getScores());
    }

    @Test
    public void testInitDealerGame_Continue_At_16() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.FIVE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.FIVE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.SIX, Card.Suit.SPADES));
        cards.add(new Card(Card.Rank.FOUR, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.FIVE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.FIVE, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.SIX, Card.Suit.SPADES));
        finalCards.add(new Card(Card.Rank.FOUR, Card.Suit.DIAMONDS));

        Game game = blackJackService.initDealerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(5, 20), game.getScores());
    }

    @Test
    public void testInitDealerGame_Stop_At_17() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.FIVE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.FIVE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.SPADES));
        cards.add(new Card(Card.Rank.FOUR, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.FIVE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.FIVE, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.SEVEN, Card.Suit.SPADES));

        Game game = blackJackService.initDealerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(5, 17), game.getScores());
    }

    @Test
    public void testInitDealerGame_Over_21() {
        BlackJackService blackJackService = new BlackJackService();

        List<Card> cards = new ArrayList<>();
        cards.add(new Card(Card.Rank.FIVE, Card.Suit.HEARTS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.SPADES));
        cards.add(new Card(Card.Rank.FOUR, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.THREE, Card.Suit.DIAMONDS));
        cards.add(new Card(Card.Rank.JACK, Card.Suit.CLUBS));
        cards.add(new Card(Card.Rank.SEVEN, Card.Suit.CLUBS));

        List<Card> finalCards = new ArrayList<>();
        finalCards.add(new Card(Card.Rank.FIVE, Card.Suit.HEARTS));
        finalCards.add(new Card(Card.Rank.SEVEN, Card.Suit.DIAMONDS));
        finalCards.add(new Card(Card.Rank.JACK, Card.Suit.SPADES));

        Game game = blackJackService.initDealerGame(cards);

        assertEquals(finalCards, game.getCards());
        assertEquals(Arrays.asList(5, 22), game.getScores());
    }

    @Test
    public void testGetCardDeal() {
        BlackJackService blackJackService = new BlackJackService();

        List<List<Card>> cardDeal = blackJackService.getCardDeal();

        assertEquals(2, cardDeal.size());

        for (List<Card> cards : cardDeal) {
            assertEquals(11, cards.size());
        }
    }

    @Test
	public void testDeck() {
        Deck deck = new Deck();

        int resultat = deck.getCards().size();
        assertEquals(52, resultat);

        Card card = deck.getCards().get(0);
        assertEquals(card, deck.dealCard());

        assertEquals(51, deck.getCards().size());
	}

}
        