import React from 'react';
import './HowToPlayBlackjack.css';
import chipsBackground from '../../Assets/chips_bckground.png';

const HowToPlayBlackjack = ({ onClose, onPlay }) => {
  return (
    <div className="how-to-play-blackjack-container">
      <div className="how-to-play-blackjack-content" style={{ backgroundImage: `url(${chipsBackground})` }}>
      <button className="popup-close-button" onClick={onClose}>Continue to Blackjack</button> {/* Bouton Close */}
        <h2 className="popup-header">How to play - BLACKJACK</h2>
        <div className="popup-text">
          <p><strong>The object of the game</strong> is to win money by creating card totals higher than those of the dealer's hand but not exceeding 21, or by stopping at a total in the hope that the dealer will bust. On their turn, players choose to <strong>"hit"</strong> (take a card) or <strong>"stand"</strong> (end their turn and stop without taking a card).</p>
          <p>Number cards count as their number, the jack, queen, and king ("<strong>face cards</strong>" or "<strong>pictures</strong>") count as 10, and aces count as either 1 or 11 according to the player's choice. If the total exceeds 21 points, it busts, and all bets on it immediately lose.</p>
          <p>After the player has finished playing, the dealer's hand is resolved by drawing cards until the hand achieves a total of 17 or higher. The dealer never doubles, splits, or surrenders. If the dealer busts, the player’s hand wins. If the dealer does not bust, the player’s bet wins if its hand is higher than the dealer's and loses if it is lower.</p>
          <p>A player total of 21 on the first two cards is a "<strong>natural</strong>" or "<strong>blackjack</strong>", and the player wins immediately unless the dealer also has one, in which case the hand ties. In the case of a tie ("<strong>push</strong>" or "<strong>standoff</strong>"), bets are returned without adjustment. A blackjack beats any hand that is not a blackjack, even one with a value of 21.</p>
          <p>Wins are paid out at even money, except for player blackjacks, which are traditionally paid out at 3 to 2 odds.</p>
        </div>
        <div className="player-decisions-section">
          <h3>Player decisions</h3>
          <ul>
            <li><strong>Hit:</strong> Take another card.</li>
            <li><strong>Stand:</strong> Take no more cards; also known as "stand pat", "sit", "stick", or "stay".</li>
          </ul>
        </div>
      </div>
    </div>
  );
};

export default HowToPlayBlackjack;
