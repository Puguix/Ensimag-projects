import React, { useEffect, useState } from 'react';
import "./CSS/Wallet.css";
import coinsImage from '../Assets/coins.png';
import WalletRates from '../Components/WalletRates/WalletRates';
import WalletBuyChips from '../Components/WalletBuyChips/WalletBuyChips';
import WalletRedeemChips from '../Components/WalletRedeemChips/WalletRedeemChips';
import { useAuth } from '../Context/AuthContext.jsx';

const Wallet = () => {
    const [chips, setChips] = useState(localStorage.getItem("chips"));

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
        <div className="dashboard-content">
            <div className="wallet-container">
                <div className="wallet-header">
                    <h1>Wallet Balance</h1>
                    <span className="wallet-balance">{localStorage.getItem("chips")}
                        <img className="coins" src={coinsImage} alt="Coins"/>
                    </span> {/* Dynamic value */}
                </div>
                <div className="rates-container">
                    <WalletRates/>
                </div>
                <div className="buy-redeem-containers">
                    <WalletBuyChips/>
                    <WalletRedeemChips/>
                </div>
            </div>
        </div>
    );
};

export default Wallet;
