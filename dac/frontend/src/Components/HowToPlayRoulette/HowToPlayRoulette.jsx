import React from 'react';
import './HowToPlayRoulette.css';
import rouletteImage from '../../Assets/Roulette_Board-min1-1.png';
import chipsBackground from '../../Assets/chips_bckground.png';

const HowToPlayRoulette = ({onClose}) => {
  return (
    <div className="popup-roulette-container">
      <div className="popup-roulette-content" style={{ backgroundImage: `url(${chipsBackground})` }}>
      <button className="popup-close-button" onClick={onClose}>Continue to Roulette</button> {/* Bouton Close */}
        <div className="popup-header">How to play - ROULETTE</div>
        <img src={rouletteImage} alt="Roulette Table" className="popup-image" />
        <div className="bet-payouts-section">
          <div className="bet-payouts-title">Roulette Bets & Payouts</div>
          <ul className="bet-payouts-list">
            <li className="bet-payouts-item" data-label="A">Single number bet pays 35 to 1. Also called "straight up."</li>
            <li className="bet-payouts-item" data-label="B">Double number bet pays 17 to 1. Also called a "split."</li>
            <li className="bet-payouts-item" data-label="C">Three number bet pays 11 to 1. Also called a "street."</li>
            <li className="bet-payouts-item" data-label="D">Four number bet pays 8 to 1. Also called a “corner bet."</li>
            <li className="bet-payouts-item" data-label="E">Bet on 0-1-2-3 pays 8 to 1. Also called “top line”.</li>
            <li className="bet-payouts-item" data-label="F">Six number bets pays 5 to 1. Example: 7, 8, 9, 10, 11, 12. Also called a “line.”</li>
            <li className="bet-payouts-item" data-label="G">Column bet (12 numbers in a row) pays 2 to 1.</li>
            <li className="bet-payouts-item" data-label="H">Twelve numbers or dozens (first, second, third dozen) pays 2 to 1.</li>
            <li className="bet-payouts-item" data-label="I">Red or black pays even money.</li>
            <li className="bet-payouts-item" data-label="J">Odd or even bets pay even money.</li>
            <li className="bet-payouts-item" data-label="K">18 numbers (1-18 or 19-36) pays even money.</li>
          </ul>
        </div>
      </div>
    </div>
  );
};

export default HowToPlayRoulette;
