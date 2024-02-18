import React, { useState, useEffect } from 'react';
import './WalletRedeemChips.css';

const WalletRedeemChips = () => {
    const [amount, setAmount] = useState('');
    const [currency, setCurrency] = useState('EUR');
    const [total, setTotal] = useState('');
    const token = localStorage.getItem('token'); // Make sure the token is stored in local storage

    // Mapping of currency codes to symbols
    const currencySymbols = {
        EUR: '€',
        USD: '$',
        GBP: '£',
        JPY: '¥',
        CAD: '$',
        AUD: '$',
        CHF: 'Fr'
    };


    useEffect(() => {
        if (amount && currency) { 
            getPrice();
        }
    }, [amount, currency]);



    const getPrice = async () => {

        const numericAmount = Number(amount);
        if (numericAmount <= 0) {
            alert('Please enter an amount greater than 0 and lower than 10000');
            return;
        }

        try {
            const priceResponse = await fetch('http://localhost:8085/getPrice', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    type: currency,
                    nbChip: numericAmount
                })
            });

            if (!priceResponse.ok) {
                throw new Error('Network response was not ok');
            }

            const priceResult = await priceResponse.json();
            setTotal(priceResult);
            
        } catch (error) {
            console.error('There has been a problem with your fetch operation:', error);
        }
    };


    const getChips = async () => {
        try {
          const response = await fetch('http://localhost:8085/players/chips', {
            method: "GET",
            headers: { 'Content-Type': 'application/json',  'token': localStorage.getItem('token')},
          });
          const res = await response.json();
          //console.log(res);
          
          await updateChips(parseInt(res, 10));
          
          
        } catch (err) {
          alert("Please check your login information again");
          console.error(err);
        }
      };


    const updateChips = async (amount) => {
        
        
        localStorage.setItem("chips", amount);
      
        // Émettre un événement personnalisé
        window.dispatchEvent(new Event('chipsUpdated'));
      };

    const handleRedeemChips = async (e) => {
        e.preventDefault();

        // Convert amount to a number and check if it is greater than 0
        const numericAmount = Number(amount);
        if (numericAmount <= 0) {
            alert('Please enter an amount greater than 0 and lower than 10000');
            return ;
        }
        if (numericAmount > localStorage.getItem("chips")) {
            alert('Please enter an amount lower than your amount of chips');
            return ;
        }

        // Make the request to the backend
        try {
            const response = await fetch('http://localhost:8085/getPrice', { // Adjust the URL as per your backend route
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify({
                    type: currency,
                    nbChip: numericAmount
                })
            });

            if (!response.ok) {
                throw new Error('Network response was not ok');
            }

            const result = await response.json();
            setTotal(result);

            const updateChipsResponse = await fetch('http://localhost:8085/players/chips', {
                method: 'PUT',
                headers: {
                    'Content-Type': 'application/json',
                    'token': token // Assuming the token is a Bearer token
                },
                body: JSON.stringify(-numericAmount) // Sending the new chips count as a number
            });
            if (!updateChipsResponse.ok) {
                throw new Error('Failed to update chips');
            }

            const updateChipsResult = await updateChipsResponse.json();
            console.log('Chips updated:', updateChipsResult);
            //alert('Chips redeem successful!');
            getChips();

        } catch (error) {
            console.error('There has been a problem with your fetch operation:', error);
        }
    };

    // Function to get the currency symbol
    const getCurrencySymbol = (currencyCode) => {
        return currencySymbols[currencyCode] || currencyCode;
    };
    return (
        <div className="redeem-chips-container">
            <h3>Redeem Chips</h3>
            <form onSubmit={handleRedeemChips} className="redeem-chips-form">
                <input
                    type="number"
                    value={amount}
                    onChange={(e) => setAmount(e.target.value)}
                    placeholder="How many chips do you want to redeem?"
                    className="input-field"
                    min="1"
                    max="10000"
                />

                <label>
                    Choose currency of payment:
                    <select
                        value={currency}
                        onChange={(e) => setCurrency(e.target.value)}
                        className="currency-select"
                    >
                        <option value="EUR">EUR (€)</option>
                        <option value="USD">USD ($)</option>
                        <option value="GBP">GBP (£)</option>
                        <option value="JPY">JPY (¥)</option>
                        <option value="CAD">CAD ($)</option>
                        <option value="AUD">AUD ($)</option>
                        <option value="CHF">CHF (Fr)</option>
                    </select>
                </label>
                <div className="total-amount">
                    Total: {total ? `${total.toFixed(2)} ${getCurrencySymbol(currency)}` : 'XX.XX €'}                </div>
                <button type="submit" className="redeem-button">REDEEM</button>
            </form>
        </div>
    );
};

export default WalletRedeemChips;