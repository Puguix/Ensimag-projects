import React, { useEffect, useState } from 'react';
import './WalletRates.css';
import coinImage from '../../Assets/coin.png';

const WalletRates = () => {
    const [rates, setRates] = useState([]);

    useEffect(() => {
        const currencies = ['EUR', 'USD', 'GBP', 'JPY', 'CAD', 'AUD', 'CHF'];

        const fetchRates = async () => {
            try {
                const ratesPromises = currencies.map(currency =>
                    fetch('http://localhost:8085/getPrice', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json'
                        },
                        body: JSON.stringify({
                            type: currency,
                            nbChip: 1
                        })
                    }).then(response => {
                        if (!response.ok) {
                            throw new Error(`Network response was not ok for ${currency}`);
                        }
                        return response.json().then(rate => ({ currency, rate }));
                    })
                );

                let ratesResults = await Promise.all(ratesPromises);

                // Validate the EUR rate; if it's not 1.00, we consider it incorrect and filter it out
                ratesResults = ratesResults.filter(({ currency, rate }) => {
                    if (currency === 'EUR' && rate !== 1.00) {
                        console.error('Incorrect EUR rate detected.');
                        return false;
                    }
                    return true;
                });

                // Update state only if the EUR rate is correct
                if (ratesResults.some(rateInfo => rateInfo.currency === 'EUR')) {
                    setRates(ratesResults.map(({ currency, rate }) => ({
                        currency,
                        rate: `${rate.toFixed(2)} ${currency}` // Formatage du taux avec deux décimales
                    })));
                }
            } catch (error) {
                console.error('Failed to fetch rates:', error);
            }
        };

        fetchRates();
    }, []);

    return (
        <div className="wallet-rates-container">
            <h3>Taux de change actuels :</h3>
            <div className="rates-grid">
                {rates.map(({ currency, rate }, index) => (
                    <div className="rate-item" key={index}>
                        1 <img className="coin" src={coinImage} alt="Coin" /> ↔ {rate}
                    </div>
                ))}
            </div>
        </div>
    );
};

export default WalletRates;
