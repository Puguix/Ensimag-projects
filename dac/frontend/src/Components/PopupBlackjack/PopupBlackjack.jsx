import React, { useState } from 'react';
import './PopupBlackjack.css';
import { useAuth } from '../../Context/AuthContext';


const PopupBlackjack = ({ onClose, onBetConfirmed }) => {
  const [betAmount, setBetAmount] = useState('');
  const [errorMessage, setErrorMessage] = useState('');
  const auth = useAuth();

  const handleBetChange = (event) => {
    const value = event.target.value;
    setBetAmount(value);
    // Réinitialiser le message d'erreur si l'utilisateur change la valeur
    if (value > 0 && value <= 10000) {
      setErrorMessage('');
    }
  };

  const confirmBet = () => {
    // Vérifier que la valeur est un nombre positif et ne dépasse pas la limite de mise
    if (betAmount <= 0) {
      setErrorMessage('Please enter a valid amount greater than 0.');
      return;
    } else if (betAmount > 10000 || betAmount > localStorage.getItem("chips")) {
      setErrorMessage('Betting limit reached. Please enter a lower amount.');
      return;
    }
    // Si la mise est valide, ajoutez ici la logique pour traiter la mise
    onBetConfirmed(betAmount);
  };

  return (
    <div className="popup-blackjack-container">
      <div className="popup-blackjack-content">
        <button className="popup-blackjack-close-button" onClick={onClose}>×</button>
        <h2 className="popup-blackjack-title">How many chips do you want to bet:</h2>
        <input
          type="number"
          className="popup-blackjack-input"
          value={betAmount}
          onChange={handleBetChange}
          placeholder="XXX"
          min="1" // Définit la mise minimale à 1
          max="10000" // Définit la mise maximale à 10000
        />
        <button className="popup-blackjack-confirm-button" onClick={confirmBet}>CONFIRM BET</button>
        {errorMessage && <p className="popup-blackjack-error">{errorMessage}</p>}
        <p className="popup-blackjack-instruction">Once you confirm your bet, you cannot take back your chips.</p>
      </div>
    </div>
  );
};

export default PopupBlackjack;
