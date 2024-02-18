import React from 'react';
import './DashboardGame.css';

const DashboardGame = ({ title, onPlayNowClick, image, className, gameTitle }) => {
  const gameClass = `dashboard-game ${className || ''}`;

  return (
    <div className={gameClass}>
      <h2>{gameTitle}</h2> 
      <div className="game-image-container">
        <img src={image} alt={title} className="game-image" />
      </div>
      <button onClick={onPlayNowClick} className="play-now-btn">PLAY NOW</button> 
    </div>
  );
};

export default DashboardGame;
