import React, { useState } from 'react';
import "./CSS/Blackjack.css";
import HowToPlayBlackJack from '../Components/HowToPlayBlackjack/HowToPlayBlackjack';
import PopupBlackjack from '../Components/PopupBlackjack/PopupBlackjack'; 
import BlackjackTable from '../Components/BlackjackTable/BlackjackTable'; 
import PopupWin from "../Components/PopupWin/PopupWin";
import PopupLoose from "../Components/PopupLoose/PopupLoose"
import { useAuth } from '../Context/AuthContext';


const Blackjack = () => {
  const [showHowToPlay, setShowHowToPlay] = useState(false);
  const [showBlackjackTable, setShowBlackjackTable] = useState(false);
  const [showBlackjackGame, setShowBlackjackGame] = useState(true);

  const [showBetPopup, setShowBetPopup] = useState(false); // État pour gérer l'affichage du popup de mise
  const [betAmount, setBetAmount] = useState(0);
  const [showWinLose, setShowWinLose] = useState(false);
  const [popupEnd, setPopupEnd] = useState(null);
  const auth = useAuth();


  // Fonction pour ouvrir la popup HowToPlayBlackJack
  const openHowToPlay = () => {
    setShowHowToPlay(true);
  };

  // Fonction pour fermer la popup HowToPlayBlackJack
  const closeHowToPlay = () => {
    setShowHowToPlay(false);
  };

  // Fonction pour ouvrir la popup de mise
  const openBetPopup = () => {
    setShowBetPopup(true);
  };

  // Fonction pour fermer la popup de mise
  const closeBetPopup = () => {
    setShowBetPopup(false);
  };

  //fonction pour lancer la table de blackjack
  const handleBetConfirmed = (amount) => {
    setBetAmount(amount);
    const prec_chips = localStorage.getItem("chips");

    localStorage.setItem("chips", prec_chips- amount);
    setShowBetPopup(false); // Close the bet popup
    setShowBlackjackGame(false)
    setShowBlackjackTable(true); // Show the Blackjack table
  };

  //fonction pour afficher les résultats
  const popupFin = async (payoffData) =>  {
    setShowBlackjackTable(false); // Close the bet popup
    const prec_chips = localStorage.getItem("chips");
    

    await getChips();

    
    if(payoffData > 0) {
      setPopupEnd(<PopupWin winnings={payoffData} gamePage={"/blackjack"}/>);
     }
    else{
      setPopupEnd(<PopupLoose losses={betAmount} gamePage={"/blackjack"}/>);
    }
    setShowWinLose(true);
  };


  const getChips = async () => {
    try {
      const response = await fetch('http://localhost:8085/players/chips', {
        method: "GET",
        headers: { 'Content-Type': 'application/json',  'token': localStorage.getItem('token')},
      });
      const res = await response.json();
      //console.log(res);
      
      localStorage.setItem("chips", parseInt(res, 10));
      console.log("changement réussi");
      
      
    } catch (err) {
      alert("Please check your login information again");
      console.error(err);
    }
  };


  return (
    <div className="blackjack-content">
        <h1 className="blackjack-title">
            Blackjack
        </h1>
        {/* Bouton pour ouvrir la popup d'instructions */}
        <button onClick={openHowToPlay} className="how-to-play-button">How to play</button>
        {/* Bouton pour ouvrir la popup de mise */}
        <button onClick={openBetPopup} className="play-button">Play</button>
        {showBlackjackGame && (
        <div className="blackjack-game">
        </div>
      )}
        {/* Popups conditionnelles */}
   
        {showHowToPlay && <HowToPlayBlackJack onClose={closeHowToPlay} />}
      {showBetPopup && <PopupBlackjack onClose={closeBetPopup} onBetConfirmed={handleBetConfirmed} />}
      {showBlackjackTable && <BlackjackTable betAmount={betAmount} payoff={popupFin}  />}
      {showWinLose && popupEnd}

    </div>
  );
};

export default Blackjack;
