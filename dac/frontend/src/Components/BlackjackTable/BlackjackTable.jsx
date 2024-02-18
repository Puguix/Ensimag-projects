import React, { useState, useEffect } from 'react';
import './BlackjackTable.css';
import tableBackground from '../../Assets/blackjack\ table.png';   

import cardBack from '../../Assets/Card\ deck/card_back.PNG';
import coin from "../../Assets/coin.png";

import getCardImage from './getCardImage'; 
import { useAuth } from '../../Context/AuthContext';

function BlackJackTable({ betAmount, payoff }) {
  const [playerHand, setPlayerHand] = useState([]);
  const [dealerHand, setDealerHand] = useState([]);
  const [playerScore, setPlayerScore] = useState([]);
  const [dealerScore, setDealerScore] = useState([]);
  const [listCardDealer, setListCardDealer] = useState([]);
  const [listCardPlayer, setListCardPlayer] = useState([]);
  const [sumPlayer, setSumPlayer] = useState(0);
  const [sumDealer, setSumDealer] = useState(0);


  // Function to fetch cards from the server
  useEffect(() => {
    fetch('http://localhost:8085/blackjack/start-game')
      .then(response => {
        if (!response.ok) {
          throw new Error('Network response was not ok');
        }
        return response.json();
      })
      .then(data => {
        
        setPlayerHand(data[0].cards.slice(2, data[0].cards.length));
        setPlayerScore(data[0].scores.slice(1, data[0].scores.length));
        setDealerHand(data[1].cards);
        setDealerScore(data[1].scores.slice(1, data[1].scores.length));

        setListCardPlayer([data[0].cards[0], data[0].cards[1]]);
        setSumPlayer(data[0].scores[0]);

        setListCardDealer([data[1].cards[0]]);
        setSumDealer(data[1].scores[0]);

      })
      .catch(error => {
        console.error('There has been a problem with your fetch operation:', error);
      });
  }, []);



  


  function hit() {
    if (playerHand.length > 0 && sumPlayer < 21) {
      const nextCard = playerHand[0];
      const nextScore = playerScore[0];
      setSumPlayer(nextScore);
      setListCardPlayer([...listCardPlayer, nextCard]);
      setPlayerHand(playerHand.slice(1, playerHand.length));
      setPlayerScore(playerScore.slice(1, playerScore.length));

    }  
  
  }

  useEffect(() => {
    //on verifie que le joueur n'est pas déjà perdu
    if (sumPlayer >21) {
      setTimeout(() => {
        getPayoff();
      }, 2000);
    }
    
  }, [sumPlayer]);



  function stand() {    

    setListCardDealer(dealerHand);
    setSumDealer(dealerScore[0]);
    setTimeout(() => {
      getPayoff();
    }, 2000);
  }

 


  function getPayoff() {
   
    const payload = {
      playerHand: listCardPlayer,
      dealerHand: dealerHand,
      bet: betAmount
    };

    fetch('http://localhost:8085/blackjack/getPayoff', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json',  'token': localStorage.getItem('token')},
      body: JSON.stringify(payload)
    })
    .then(response => response.json())
    .then(data => {
      payoff(data);      
    })
    .catch(error => {
      console.error('Error:', error);
    });
    
  }

  return (
    <div className="blackjack-game" style={{ backgroundImage: `url(${tableBackground})` }}>
      <div className="dealer-hand">
          <div className="title">
            <h3>Dealer's Hand ({sumDealer})</h3>
          </div>
          <div className="hand-container">
          {/* Afficher les cartes du croupier */}
          {listCardDealer.map((card, index) => (
            <img
              key={index}
              src={getCardImage(card.rank, card.suit)}
              alt={`${card.rank} of ${card.suit}`}
              className="card"
            />
          ))}
        </div>
      </div>
      <div className="player-hand">
          <div className="title">
            <h3>Your Hand ({sumPlayer})</h3>
          </div>
          <div className="hand-container">
          {/* Afficher les cartes du joueur */}
          {listCardPlayer.map((card, index) => (
            <img
              key={index}
              src={getCardImage(card.rank, card.suit)}
              alt={`${card.rank} of ${card.suit}`}
              className="card"
            />
          ))}
        </div>
      </div>
      <div className="bet-amount">
        Bet Amount: {betAmount}
        <img src={coin} alt="coin" />
      </div>
      <div className="game-actions">
        <div className="game-actions">
          <button className="hit-button" onClick={hit}>
            Hit
          </button>
          <button className="stand-button" onClick={stand}>
            Stand
          </button>
        </div>
      </div>
    </div>
  );
}



export default BlackJackTable;
