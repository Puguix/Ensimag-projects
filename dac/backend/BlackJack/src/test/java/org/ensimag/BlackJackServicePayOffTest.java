package org.ensimag;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.mock;

import static org.mockito.Mockito.when;


import java.util.List;

import org.ensimag.Card.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;

import org.mockito.junit.jupiter.MockitoExtension;

@ExtendWith(MockitoExtension.class)
public class BlackJackServicePayOffTest {

    
    @Test
	public void getValue_ACE_Number() {
        Card card = new Card(Rank.ACE, Suit.DIAMONDS);
        Card card2 = new Card(Rank.TWO, Suit.DIAMONDS);
        Card card3 = new Card(Rank.THREE, Suit.DIAMONDS);
        Card card4 = new Card(Rank.FOUR, Suit.DIAMONDS);
        Card card5 = new Card(Rank.FIVE, Suit.DIAMONDS);
        Card card6 = new Card(Rank.SIX, Suit.DIAMONDS);
        Card card7 = new Card(Rank.SEVEN, Suit.DIAMONDS);
        Card card8 = new Card(Rank.EIGHT, Suit.DIAMONDS);
        Card card9 = new Card(Rank.NINE, Suit.DIAMONDS);
        Card card10 = new Card(Rank.TEN, Suit.DIAMONDS);

        double resultat = card.getValue();
        double resultat2 = card2.getValue();
        double resultat3 = card3.getValue();
        double resultat4 = card4.getValue();
        double resultat5 = card5.getValue();
        double resultat6 = card6.getValue();
        double resultat7 = card7.getValue();
        double resultat8 = card8.getValue();
        double resultat9 = card9.getValue();
        double resultat10 = card10.getValue();

        assertEquals(1, resultat);
        assertEquals(2, resultat2);
        assertEquals(3, resultat3);
        assertEquals(4, resultat4);
        assertEquals(5, resultat5);
        assertEquals(6, resultat6);
        assertEquals(7, resultat7);
        assertEquals(8, resultat8);
        assertEquals(9, resultat9);
        assertEquals(10, resultat10);
	}


    @Test
	public void getValue_HEAD() {        Card cardJ = new Card(Rank.JACK, Suit.DIAMONDS);
        Card cardQ= new Card(Rank.QUEEN, Suit.DIAMONDS);
        Card cardK = new Card(Rank.KING, Suit.DIAMONDS);
                double resultatJ = cardJ.getValue();
        double resultatQ = cardQ.getValue();
        double resultatK = cardK.getValue();
                assertEquals(10, resultatJ);
        assertEquals(10, resultatQ);
        assertEquals(10, resultatK);
	}
    
    @Test
	public void getScore_BlackJack() {
        BlackJackService blackJackService = new BlackJackService();        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(10);
        double resultat = blackJackService.getScore(List.of(mockCard1, mockCard2));
        assertEquals(21, resultat);
	}

    @Test
	public void getScore_WithoutAce_Under21() {
        BlackJackService blackJackService = new BlackJackService();
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.THREE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.FOUR);
        when(mockCard3.getRank()).thenReturn(Card.Rank.QUEEN);

        when(mockCard1.getValue()).thenReturn(3);
        when(mockCard2.getValue()).thenReturn(4);
        when(mockCard3.getValue()).thenReturn(10);

        double resultat = blackJackService.getScore(List.of(mockCard1, mockCard2, mockCard3));

        assertEquals(17, resultat);
	}

    @Test
	public void getScore_WithoutAce_After21() {
        BlackJackService blackJackService = new BlackJackService();
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.FIVE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);
        when(mockCard3.getRank()).thenReturn(Card.Rank.QUEEN);

        when(mockCard1.getValue()).thenReturn(5);
        when(mockCard2.getValue()).thenReturn(10);
        when(mockCard3.getValue()).thenReturn(10);

        double resultat = blackJackService.getScore(List.of(mockCard1, mockCard2, mockCard3));

        assertEquals(25, resultat);
	}

    @Test
	public void getScore_With_1_ACE_Value_11() {
        BlackJackService blackJackService = new BlackJackService();
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.NINE);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(9);

        double resultat = blackJackService.getScore(List.of(mockCard1, mockCard2));

        assertEquals(20, resultat);
	}

    @Test
	public void getScore_With_1_ACE_Value_1() {
        BlackJackService blackJackService = new BlackJackService();
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);
        when(mockCard3.getRank()).thenReturn(Card.Rank.SIX);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(10);
        when(mockCard3.getValue()).thenReturn(6);
        double resultat = blackJackService.getScore(List.of(mockCard1, mockCard2, mockCard3));

        assertEquals(17, resultat);
	}

    @Test
	public void getScore_With_2_ACEs() {
        BlackJackService blackJackService = new BlackJackService();
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);
        Card mockCard4 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard3.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard4.getRank()).thenReturn(Card.Rank.ACE);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(1);
        when(mockCard3.getValue()).thenReturn(1);
        when(mockCard4.getValue()).thenReturn(1);

        double resultat = blackJackService.getScore(List.of(mockCard1, mockCard2, mockCard3, mockCard4));

        assertEquals(14, resultat);
	}

	@Test
	public void calculatePayOff_BlackJackPlayerOnly() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);

        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);
        when(mockCard3.getRank()).thenReturn(Card.Rank.NINE);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(10);
        when(mockCard3.getValue()).thenReturn(9);
        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard3));

        when(mockEndGame.getBet()).thenReturn(10.0);

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(25.0, resultat);
	}

    @Test
    public void calculatePayOff_2BlackJacks() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(10);
        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard2));

        when(mockEndGame.getBet()).thenReturn(10.0);

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(10.0, resultat);
    }

    @Test
	public void calculatePayOff_BlackJackDealerOnly() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.ACE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);
        when(mockCard3.getRank()).thenReturn(Card.Rank.FOUR);

        when(mockCard1.getValue()).thenReturn(1);
        when(mockCard2.getValue()).thenReturn(10);
        when(mockCard3.getValue()).thenReturn(4);
        
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard3));

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(0.0, resultat);
	}

    @Test
	public void calculatePayOff_Player_Over21() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.FIVE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);

        when(mockCard1.getValue()).thenReturn(5);
        when(mockCard2.getValue()).thenReturn(10);
        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard2, mockCard2));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard2));

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(0.0, resultat);
	}

    @Test
	public void calculatePayOff_Dealer_Over21() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.FIVE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);

        when(mockCard1.getValue()).thenReturn(5);
        when(mockCard2.getValue()).thenReturn(10);
        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard2, mockCard2));
        when(mockEndGame.getBet()).thenReturn(10.0);

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(20.0, resultat);
	}

    @Test
	public void calculatePayOff_Dealer_SameScore() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.FIVE);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);

        when(mockCard1.getValue()).thenReturn(5);
        when(mockCard2.getValue()).thenReturn(10);
        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getBet()).thenReturn(10.0);

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(10.0, resultat);
	}

    @Test
	public void calculatePayOff_Player_Win_Under21() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.SEVEN);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);
        when(mockCard3.getRank()).thenReturn(Card.Rank.EIGHT);

        when(mockCard1.getValue()).thenReturn(7);
        when(mockCard2.getValue()).thenReturn(10);
        when(mockCard3.getValue()).thenReturn(8);

        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard2, mockCard3));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getBet()).thenReturn(10.0);

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(20.0, resultat);
	}

    @Test
	public void calculatePayOff_Dealer_Win_Under21() {
        BlackJackService blackJackService = new BlackJackService();

        EndGame mockEndGame = mock(EndGame.class);
        
        Card mockCard1 = mock(Card.class);
        Card mockCard2 = mock(Card.class);
        Card mockCard3 = mock(Card.class);

        when(mockCard1.getRank()).thenReturn(Card.Rank.SEVEN);
        when(mockCard2.getRank()).thenReturn(Card.Rank.TEN);
        when(mockCard3.getRank()).thenReturn(Card.Rank.EIGHT);

        when(mockCard1.getValue()).thenReturn(7);
        when(mockCard2.getValue()).thenReturn(10);
        when(mockCard3.getValue()).thenReturn(8);

        
        when(mockEndGame.getPlayerHand()).thenReturn(List.of(mockCard1, mockCard2));
        when(mockEndGame.getDealerHand()).thenReturn(List.of(mockCard1, mockCard3));

        double resultat = blackJackService.getPayoff(mockEndGame);

        assertEquals(0.0, resultat);
	}
}