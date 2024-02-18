import React, { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom'; // Import useHistory from React Router
import './CSS/Dashboard.css';
import blackjackImage from '../Assets/top-view-of-blackjack-table.png';
import rouletteImage from '../Assets/roulette.jpg';
import DashboardGame from '../Components/DashboardGame/DashboardGame';
import HowToPlayRoulette from '../Components/HowToPlayRoulette/HowToPlayRoulette';
import HowToPlayBlackjack from '../Components/HowToPlayBlackjack/HowToPlayBlackjack';
import { useAuth } from '../Context/AuthContext.jsx';

const Dashboard = () => {
  const navigate = useNavigate();
  const [showHowToPlayRoulette, setShowHowToPlayRoulette] = useState(false); // State to control the popup
  const [showHowToPlayBlackjack, setShowHowToPlayBlackjack] = useState(false);
  const [userName, setUserName] = useState('');

  useEffect(() => {
    const userName = localStorage.getItem('surname');
    if (userName) {
      setUserName(userName);
    }
  }, []);


  const handlePlayNowClickRoulette = () => {
    setShowHowToPlayRoulette(true); // Show the HowToPlayRoulette popup
  };

  const handlePlayNowClickBlackjack = () => {
    setShowHowToPlayBlackjack(true);
  };

  const handleClosePopupRoulette = () => {
    setShowHowToPlayRoulette(false); // Close the popup
  };

  const handleClosePopupBlackjack = () => {
    setShowHowToPlayBlackjack(false);
  };

  const handlePlayRoulette = () => {
    navigate('/Roulette'); // Navigate to the Roulette page
  };

  const handlePlayBlackjack = () => {
    navigate('/Blackjack'); // Navigate to the Blackjack page
  };

  return (
    <div className="dashboard-content">
      <div className="dashboard-info">
        <h1 className="welcome">
          Welcome <em>{userName}</em>!
        </h1>
        <div className="dashboard-chips">
          <p>You currently have <em>{localStorage.getItem("chips")}</em> chips in your wallet.</p>
          <a href="/wallet">MANAGE CHIPS</a>
        </div>
      </div>
      <div className="dashboard-games">
        <DashboardGame
          title="Blackjack"
          onPlayNowClick={handlePlayNowClickBlackjack} // Pass the handlePlayNowClickBlackjack function
          image={blackjackImage}
          gameTitle="Blackjack"
        />
        <div className="dashboard-game">
          <h2>Roulette</h2>
          <div className="game-image-container">
            <img src={rouletteImage} alt="Roulette" className="game-image" />
          </div>
          <button onClick={handlePlayNowClickRoulette} className="play-now-btn">PLAY NOW</button>
        </div>
      </div>
      {showHowToPlayRoulette && (
        <HowToPlayRoulette onClose={handlePlayRoulette} />
      )}
      {showHowToPlayBlackjack && (
        <HowToPlayBlackjack onClose={handlePlayBlackjack} />
      )}
    </div>
  );
};

export default Dashboard;
