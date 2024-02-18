import React from 'react';
import './PopupWin.css';
import { useNavigate } from 'react-router';
import { useAuth } from '../../Context/AuthContext';

const PopupWin = ({ winnings, gamePage }) => {
    const auth = useAuth();
    const navigate = useNavigate();

    function gotoDashboard() {
        navigate("/Dashboard");
    }

    return (
        <div className="popup-win-container">
            <div className="popup-win-content">
                {/* Background animation circles */}
                <div className="area" style={{ position: 'absolute', top: 0, left: 0, right: 0, bottom: 0, zIndex: 0 }}>
                <ul className="circles">
                    {Array.from({ length: 200 }, (_, index) => (
                    <li key={index} style={{
                        left: `${Math.floor(Math.random() * 100)}%`,
                        top: `${Math.floor(Math.random() * 100)}%`,
                        width: `${20 + Math.random() * 40}px`,
                        height: `${20 + Math.random() * 40}px`,
                        animationDuration: `${Math.floor(Math.random() * 10) + 5}s`,
                        animationDelay: `${Math.floor(Math.random() * 10)}s`,
                        position: 'absolute',
                        top: -100, //
                    }}></li>
                    ))}
                </ul>
                </div>
                 {/* Content overlay so it appears above the circles */}
                 <div className="content-overlay" style={{ position: 'relative', zIndex: 1 }}>
                    <div className="popup-win-header">Congrats!</div>
                    <p className="popup-win-text">You won {winnings} chips!</p>
                    <p className="popup-win-text">Your new total is {parseInt(localStorage.getItem("chips"), 10)} chips.</p>
                    <div className="popup-win-buttons">
                        <button className="popup-win-button" onClick={() => window.location.reload(false)}>PLAY AGAIN</button>
                        <button className="popup-win-button" onClick={gotoDashboard}>Home</button>
                    </div>
                </div>
            </div>
        </div>
    );
};

export default PopupWin;
