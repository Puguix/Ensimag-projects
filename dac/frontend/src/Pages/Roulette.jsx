import React, { useEffect, useState } from 'react';
import "./CSS/Roulette.css";
import RouletteTable from '../Components/RouletteTable/RouletteTable';
import HowToPlayRoulette from '../Components/HowToPlayRoulette/HowToPlayRoulette'
import RouletteWheel from '../Components/RouletteWheel/RouletteWheel';
import PopupWin from "../Components/PopupWin/PopupWin";
import PopupLoose from "../Components/PopupLoose/PopupLoose"
import { useAuth } from '../Context/AuthContext';
import { useNavigate } from 'react-router-dom';


const Roulette = () => {
  const auth = useAuth();
  // État pour gérer l'affichage de la popup HowToPlayRoulette
  const [showHowToPlay, setShowHowToPlay] = useState(false);
  const [rouletteResults, setRouletteResults] = useState({
    "rouletteRes" : null,
    "roulettePayoff": null
  });
  const [spinAllowed, setSpinAllowed] = useState(false);
  const [showWinLose, setShowWinLose] = useState(false);
  const [totalBet, setTotalBet] = useState(0);
  const [popupEnd, setPopupEnd] = useState(null);

  function handleConfirm (allBets){
    window.scrollTo({top: 0, left: 0, behavior: 'smooth'});
    let rouletteBets = [];
    let totalBetAmount = 0;
    Object.keys(allBets).forEach((betKey) => {
      totalBetAmount = totalBetAmount + allBets[betKey].betValue;
      if(allBets[betKey].isBet){
          let betValues = [];
          for (const item in String(betKey).split("-").slice(1)){
              betValues.push(Number(String(betKey).split("-").slice(1)[item]))
          }
          const betItem = {
              amount : allBets[betKey].betValue,
              type : String(betKey).split("-")[0],
              value : betValues
          };
          rouletteBets.push(betItem);
      }
    });
    setTotalBet(totalBetAmount);
    const precChip = localStorage.getItem("chips");
    console.log(rouletteBets);
    if (rouletteBets.length!==0){
      fetch(`http://localhost:8085/roulette/bet`, {
        method: 'POST',
        headers: { 'Content-Type': 'application/json',  'token': localStorage.getItem("token")},
        body: JSON.stringify(rouletteBets),
      })
      .then((res) => res.json())
      .then((json) => {
        if (json.length===2)
        {
          const newChipAmount = localStorage.getItem("chips") - totalBetAmount;
          localStorage.setItem("chips", newChipAmount);
          setRouletteResults(rouletteResults => ({...rouletteResults,
            "rouletteRes":json[0],
            "roulettePayoff": json[1]}))
            localStorage.setItem("chips", precChip - totalBetAmount);
          }
        else{
          alert("problems occurred with the roulette, we have reimbursed your chips.");
          window.location.reload(false);
        }
        // if (){
        //   console.log("problem");
        //   alert("Problems occurred with the roulette, we have reimbursed your chips.");
        // }
        // else{
        //   console.log(json)
        //   console.log(localStorage.getItem("token"))
        //   setRouletteResults(rouletteResults => ({
        //     ...rouletteResults,
        //     "rouletteRes" : json[0],
        //     "roulettePayoff" : json[1]
        //   }));
        //   console.log(rouletteResults);
        //   setSpinAllowed(!spinAllowed);
        // }
      });


      //do fetch 
      //if fetch ok, remove money from auth
      //else oops problem give back money
    //   setRouletteResults(rouletteResults => ({
    //     ...rouletteResults,
    //     "rouletteRes" : "25",
    //     "roulettePayoff" : 53
    // }));
    }
    else{
      alert("You haven't bet anything")
      return
  }
}

useEffect(() => {
  if(rouletteResults.roulettePayoff!==null){
    setSpinAllowed(true);
  }
},[rouletteResults])

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

  const endGame = async (obj) => {
    const timer = setTimeout(() => {setShowWinLose(obj);
    const newChips = Number(localStorage.getItem("chips")) + Number(rouletteResults.roulettePayoff)
    localStorage.setItem("chips", Number(newChips));
    if(rouletteResults.roulettePayoff > 0) {
      setPopupEnd(<PopupWin winnings={rouletteResults.roulettePayoff} gamePage={"/Roulette"}/>);
    }
    else{
      setPopupEnd(<PopupLoose losses={totalBet} gamePage={"/Roulette"}/>);
    }
  }, 7000);  
    return () => clearTimeout(timer);

  }


  

  // Fonction pour ouvrir la popup
  const openHowToPlay = () => {
    setShowHowToPlay(true);
  };

  // Fonction pour fermer la popup
  const closeHowToPlay = () => {
    setShowHowToPlay(false);
  };


  return (
    <div className="roulette-content">
        <h1 className="roulette-title">
            Roulette
        </h1>
        {/* Utiliser un bouton au lieu de lien et gérer le clic */}
        <button onClick={openHowToPlay} className="how-to-play-button">How to play</button>
        <div className="roulette-game">
            <div className="roulette-wheel">
              <RouletteWheel canSpin={spinAllowed} rouletteRes={rouletteResults.rouletteRes} endGame={endGame}/>
            </div>
            <div className="roulette-table">
                <RouletteTable handleConfirm={handleConfirm}/>
            </div>
        </div>
        {/* Affichage conditionnel de la popup fin de partie */}
        {showWinLose && popupEnd}
        {/* Affichage conditionnel de la popup */}
        {showHowToPlay && <HowToPlayRoulette onClose={closeHowToPlay} />}
    </div>
  );
};

export default Roulette;
