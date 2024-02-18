import React, { useState, useEffect } from 'react';
import { Link, useNavigate } from 'react-router-dom'; // Import useHistory
import './Navbar.css';
import userIcon from "../../Assets/icons/user.svg";
import chipsIcon from "../../Assets/icons/coin.svg";
import "../../Pages/LoginSignup.jsx"
import { useAuth } from '../../Context/AuthContext.jsx';
const Navbar = () => {
  const navigate = useNavigate(); 
  const auth= useAuth();
  const [chips, setChips] = useState(localStorage.getItem("chips"));
  
  const handleLogout = () => {
    localStorage.removeItem("chips");
    localStorage.removeItem("token");
    navigate("");
  };



  useEffect(() => {
    const handleChipsUpdate = () => {
        setChips(localStorage.getItem("chips"));
    };

    window.addEventListener('chipsUpdated', handleChipsUpdate);

    // Nettoyer l'écouteur d'événements lors de la désinscription du composant
    return () => {
        window.removeEventListener('chipsUpdated', handleChipsUpdate);
    };
}, []);


  return (
    <div className="navbar">
      <div className="nav-logo">
        <Link to="/Dashboard">easyBet</Link>
      </div>
      <ul className="nav-menu">
        <li><Link to="/Blackjack">BLACKJACK</Link></li>
        <li><Link to="/Roulette">ROULETTE</Link></li>
      </ul>
      <div className="nav-logout-profile-chips">
        <button type="button" onClick={handleLogout}>LOG OUT</button>
        <Link to="/Profile"><img src={userIcon} alt="" /></Link>
        <Link to="/Wallet" style={{ textDecoration: 'none' }}><div className="wallet-link"> {chips} <img src={chipsIcon} alt="" /></div></Link>
      </div>
    </div>
  );
};

export default Navbar;
