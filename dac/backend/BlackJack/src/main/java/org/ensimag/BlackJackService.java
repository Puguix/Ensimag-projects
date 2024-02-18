package org.ensimag;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

import static org.ensimag.BlackJackConfig.*;

@Service
public class BlackJackService {


    /**
     * Method called to initialise the game.
     * @return a list of Game, containing all possible cards for player,
     * and corresponding scores, and dealer's game.
     */
    public List<Game> startGame(){
        List<Game> games = new ArrayList<>();
        List<List<Card>> deals = getCardDeal();
        games.add(initPlayerGame(deals.get(0))); // returns the player's game
        games.add(initDealerGame(deals.get(1))); // returns the dealer's game.
        return games;
    }


    /**
     * Method used to initialise a single Game for a player.
     * @param deal takes the cards dealt to the player (11 initial cards)
     * @return Game, contains maximum list of cards player can take, and associated scores.
     */
    public Game initPlayerGame(List<Card> deal){
        Game game = new Game();
        game.cards.add(deal.get(0));
        game.cards.add(deal.get(1));
        int score = getScore(game.cards);
        game.scores.add(score);
        int i=2;
        while (score< BLACKJACK){
            game.cards.add(deal.get(i));
            i+=1;
            score = getScore(game.cards);
            game.scores.add(score);
        }
        return game;
    }


    /**
     * Method to play as the dealer.
     * @param deal takes the 11 cards dealt
     * @return dealer's game : initial score (of first card), final cards and final score.
     */
    public Game initDealerGame(List<Card> deal){
        Game game = new Game();
        game.cards.add(deal.get(0));
        int score = getScore(game.cards);
        game.scores.add(score);
        int i=1;
        while (score<MAX_VALUE_OF_DEALER_HAND){
            game.cards.add(deal.get(i));
            i+=1;
            score = getScore(game.cards);
        }
        game.scores.add(score);
        return game;
    }


    /**
     Method called to deal blackjack cards. sends maximum amount of cards per player.
     @return result list of 2 elements: list of total cards for player and for dealer.
     */
    public List<List<Card>> getCardDeal(){
        Deck deck = new Deck();
        deck.shuffle();
        List<Card> playerDeck = new ArrayList<>();
        List<Card> dealerDeck = new ArrayList<>();
        for (int i=0; i<NUMBER_OF_CARDS_DEALT; i++){
            playerDeck.add(deck.dealCard());
            dealerDeck.add(deck.dealCard());
        }
        List<List<Card>> result = new ArrayList<>();
        result.add(playerDeck);
        result.add(dealerDeck);
        return result;
    }

    /**
     Method to calculate score of a given hand, takes into account the value of ace.
     @param hand player or dealer's hand.
     @return score.
     */
    public int getScore(List<Card> hand) {
        int score = 0;
        boolean aceFlag = false;
        for (Card card : hand) {
            score += card.getValue();
            if (card.getRank() == Card.Rank.ACE) {
                aceFlag = true;
            }
        }
        if (aceFlag && score + ADDED_ACE_VALUE <= BLACKJACK) {
            score += ADDED_ACE_VALUE;
        }
        return score;
    }

    /**
     * Method used to calculate the final payOff of the game.
     * @param endGame takes the cards played by the player, the dealer and the amount of the bet.
     * @return double, which is the payOff from the amount of the bet and the result of the game.
     */
    public double getPayoff (EndGame endGame){
        int playerScore = getScore(endGame.getPlayerHand());
        int dealerScore = getScore(endGame.getDealerHand());

        boolean playerBlackJack = (playerScore==BLACKJACK && endGame.getPlayerHand().size()==2);
        boolean dealerBlackJack = (dealerScore==BLACKJACK && endGame.getDealerHand().size()==2);

        if (playerBlackJack){ //If player has a blackJack
            if(!dealerBlackJack){ // And dealer has no blackjack
                return endGame.getBet()*BLACKJACK_PAYOFF;
            }
            return endGame.getBet(); //If they both get a blackJack, it's a draw.
        }
        else{
            if(dealerBlackJack) return 0.0; //If dealer has a blackJack, it's over.
            if (playerScore>BLACKJACK) return 0.0; //If the player has more than 21, it's over.
            if (dealerScore>BLACKJACK) return 2*endGame.getBet(); //If the dealer has more than 21, it's a win.
            if (dealerScore==playerScore) return endGame.getBet(); //If they have the same score, it's a draw.
            if (dealerScore>playerScore) return 0.0; //If the dealer beat the player,  it's over.
            return 2*endGame.getBet(); //If the palyer beat the dealer it's a win.
        }
    }

}
