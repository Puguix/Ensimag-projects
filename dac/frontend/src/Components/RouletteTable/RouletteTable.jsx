import React, { useState } from 'react'
import "./RouletteTable.css"
import chipTen from "../../Assets/chip_ten.png"
import chipFive from "../../Assets/IMG_2425.PNG"
import chipFifty from "../../Assets/IMG_2424.PNG"
import { useAuth } from '../../Context/AuthContext'

const RouletteTable = ({handleConfirm}) => {
    const auth = useAuth();
    const initalImgSources = {"inside-0-1-2-3" : {isBet : false, betValue : null},
    "inside-1-2-3" : {isBet : false, betValue : null},
    "inside-1-2-3-4-5-6" : {isBet : false, betValue : null},
    "inside-4-5-6" : {isBet : false, betValue : null},
    "inside-4-5-6-7-8-9" : {isBet : false, betValue : null},
    "inside-7-8-9" : {isBet : false, betValue : null},
    "inside-7-8-9-10-11-12" : {isBet : false, betValue : null},
    "inside-10-11-12" : {isBet : false, betValue : null},
    "inside-10-11-12-13-14-15" : {isBet : false, betValue : null},
    "inside-13-14-15" : {isBet : false, betValue : null},
    "inside-13-14-15-16-17-18" : {isBet : false, betValue : null},
    "inside-16-17-18" : {isBet : false, betValue : null},
    "inside-16-17-18-19-20-21" : {isBet : false, betValue : null},
    "inside-19-20-21" : {isBet : false, betValue : null},
    "inside-19-20-21-22-23-24" : {isBet : false, betValue : null},
    "inside-22-23-24" : {isBet : false, betValue : null},
    "inside-22-23-24-25-26-27" : {isBet : false, betValue : null},
    "inside-25-26-27" : {isBet : false, betValue : null},
    "inside-25-26-27-28-29-30" : {isBet : false, betValue : null},
    "inside-28-29-30" : {isBet : false, betValue : null},
    "inside-28-29-30-31-32-33" : {isBet : false, betValue : null},
    "inside-31-32-33" : {isBet : false, betValue : null},
    "inside-31-32-33-34-35-36" : {isBet : false, betValue : null},
    "inside-34-35-36" : {isBet : false, betValue : null},
    "inside-0" : {isBet : false, betValue : null},
    "inside-0-3" : {isBet : false, betValue : null},
    "inside-3" : {isBet : false, betValue : null},
    "inside-3-6" : {isBet : false, betValue : null},
    "inside-6" : {isBet : false, betValue : null},
    "inside-6-9" : {isBet : false, betValue : null},
    "inside-9" : {isBet : false, betValue : null},
    "inside-9-12" : {isBet : false, betValue : null},
    "inside-12" : {isBet : false, betValue : null},
    "inside-12-15" : {isBet : false, betValue : null},
    "inside-15" : {isBet : false, betValue : null},
    "inside-15-18" : {isBet : false, betValue : null},
    "inside-18" : {isBet : false, betValue : null},
    "inside-18-21" : {isBet : false, betValue : null},
    "inside-21" : {isBet : false, betValue : null},
    "inside-21-24" : {isBet : false, betValue : null},
    "inside-24" : {isBet : false, betValue : null},
    "inside-24-27" : {isBet : false, betValue : null},
    "inside-27" : {isBet : false, betValue : null},
    "inside-27-30" : {isBet : false, betValue : null},
    "inside-30" : {isBet : false, betValue : null},
    "inside-30-33" : {isBet : false, betValue : null},
    "inside-33" : {isBet : false, betValue : null},
    "inside-33-36" : {isBet : false, betValue : null},
    "inside-36" : {isBet : false, betValue : null},
    "column-0" : {isBet : false, betValue : null},
    "inside-0-2-3" : {isBet : false, betValue : null},
    "inside-2-3" : {isBet : false, betValue : null},
    "inside-2-3-5-6" : {isBet : false, betValue : null},
    "inside-5-6" : {isBet : false, betValue : null},
    "inside-5-6-8-9" : {isBet : false, betValue : null},
    "inside-8-9" : {isBet : false, betValue : null},
    "inside-8-9-11-12" : {isBet : false, betValue : null},
    "inside-11-12" : {isBet : false, betValue : null},
    "inside-11-12-14-15" : {isBet : false, betValue : null},
    "inside-14-15" : {isBet : false, betValue : null},
    "inside-14-15-17-18" : {isBet : false, betValue : null},
    "inside-17-18" : {isBet : false, betValue : null},
    "inside-17-18-20-21" : {isBet : false, betValue : null},
    "inside-20-21" : {isBet : false, betValue : null},
    "inside-20-21-23-24" : {isBet : false, betValue : null},
    "inside-23-24" : {isBet : false, betValue : null},
    "inside-23-24-26-27" : {isBet : false, betValue : null},
    "inside-26-27" : {isBet : false, betValue : null},
    "inside-26-27-29-30" : {isBet : false, betValue : null},
    "inside-29-30" : {isBet : false, betValue : null},
    "inside-29-30-32-33" : {isBet : false, betValue : null},
    "inside-32-33" : {isBet : false, betValue : null},
    "inside-32-33-35-36" : {isBet : false, betValue : null},
    "inside-35-36" : {isBet : false, betValue : null},
    "inside-0-2" : {isBet : false, betValue : null},
    "inside-2" : {isBet : false, betValue : null},
    "inside-2-5" : {isBet : false, betValue : null},
    "inside-5" : {isBet : false, betValue : null},
    "inside-5-8" : {isBet : false, betValue : null},
    "inside-8" : {isBet : false, betValue : null},
    "inside-8-11" : {isBet : false, betValue : null},
    "inside-11" : {isBet : false, betValue : null},
    "inside-11-14" : {isBet : false, betValue : null},
    "inside-14" : {isBet : false, betValue : null},
    "inside-14-17" : {isBet : false, betValue : null},
    "inside-17" : {isBet : false, betValue : null},
    "inside-17-20" : {isBet : false, betValue : null},
    "inside-20" : {isBet : false, betValue : null},
    "inside-20-23" : {isBet : false, betValue : null},
    "inside-23" : {isBet : false, betValue : null},
    "inside-23-26" : {isBet : false, betValue : null},
    "inside-26" : {isBet : false, betValue : null},
    "inside-26-29" : {isBet : false, betValue : null},
    "inside-29" : {isBet : false, betValue : null},
    "inside-29-32" : {isBet : false, betValue : null},
    "inside-32" : {isBet : false, betValue : null},
    "inside-32-35" : {isBet : false, betValue : null},
    "inside-35" : {isBet : false, betValue : null},
    "column-2" : {isBet : false, betValue : null},
    "inside-0-1-2" : {isBet : false, betValue : null},
    "inside-1-2" : {isBet : false, betValue : null},
    "inside-1-2-4-5" : {isBet : false, betValue : null},
    "inside-4-5" : {isBet : false, betValue : null},
    "inside-4-5-7-8" : {isBet : false, betValue : null},
    "inside-7-8" : {isBet : false, betValue : null},
    "inside-7-8-10-11" : {isBet : false, betValue : null},
    "inside-10-11" : {isBet : false, betValue : null},
    "inside-10-11-13-14" : {isBet : false, betValue : null},
    "inside-13-14" : {isBet : false, betValue : null},
    "inside-13-14-16-17" : {isBet : false, betValue : null},
    "inside-16-17" : {isBet : false, betValue : null},
    "inside-16-17-19-20" : {isBet : false, betValue : null},
    "inside-19-20" : {isBet : false, betValue : null},
    "inside-19-20-22-23" : {isBet : false, betValue : null},
    "inside-22-23" : {isBet : false, betValue : null},
    "inside-22-23-25-26" : {isBet : false, betValue : null},
    "inside-25-26" : {isBet : false, betValue : null},
    "inside-25-26-28-29" : {isBet : false, betValue : null},
    "inside-28-29" : {isBet : false, betValue : null},
    "inside-28-29-31-32" : {isBet : false, betValue : null},
    "inside-31-32" : {isBet : false, betValue : null},
    "inside-31-32-34-35" : {isBet : false, betValue : null},
    "inside-34-35" : {isBet : false, betValue : null},
    "inside-0-1" : {isBet : false, betValue : null},
    "inside-1" : {isBet : false, betValue : null},
    "inside-1-4" : {isBet : false, betValue : null},
    "inside-4" : {isBet : false, betValue : null},
    "inside-4-7" : {isBet : false, betValue : null},
    "inside-7" : {isBet : false, betValue : null},
    "inside-7-10" : {isBet : false, betValue : null},
    "inside-10" : {isBet : false, betValue : null},
    "inside-10-13" : {isBet : false, betValue : null},
    "inside-13" : {isBet : false, betValue : null},
    "inside-13-16" : {isBet : false, betValue : null},
    "inside-16" : {isBet : false, betValue : null},
    "inside-16-19" : {isBet : false, betValue : null},
    "inside-19" : {isBet : false, betValue : null},
    "inside-19-22" : {isBet : false, betValue : null},
    "inside-22" : {isBet : false, betValue : null},
    "inside-22-25" : {isBet : false, betValue : null},
    "inside-25" : {isBet : false, betValue : null},
    "inside-25-28" : {isBet : false, betValue : null},
    "inside-28" : {isBet : false, betValue : null},
    "inside-28-31" : {isBet : false, betValue : null},
    "inside-31" : {isBet : false, betValue : null},
    "inside-31-34" : {isBet : false, betValue : null},
    "inside-34" : {isBet : false, betValue : null},
    "column-1" : {isBet : false, betValue : null},
    "dozen-0" : {isBet : false, betValue : null},
    "dozen-1" : {isBet : false, betValue : null},
    "dozen-2" : {isBet : false, betValue : null},
    "lowHigh-0" : {isBet : false, betValue : null},
    "oddEven-0" : {isBet : false, betValue : null},
    "blackRed-1" : {isBet : false, betValue : null},
    "blackRed-0" : {isBet : false, betValue : null},
    "oddEven-1" : {isBet : false, betValue : null},
    "lowHigh-1" : {isBet : false, betValue : null},
};
    const [selectedChipValue, setSelectedChipValue] = useState(5);
    const [imgSources, setImgSources] = useState(initalImgSources);
    const availableChipsInitial = localStorage.getItem("chips");
    const [availableChips, setAvailableChips] = useState(availableChipsInitial);
    // const [availableChips, setAvailableChips] = useState(auth.chips);

    function handleBetClick (e) {
        e.preventDefault();
        const betClass = e.currentTarget.classList[1];
        if (imgSources[betClass].isBet){
            const prevBetValue = imgSources[betClass].betValue;
            const newBet = {isBet : !imgSources[betClass].isBet, betValue: null};
            setAvailableChips(availableChips + prevBetValue);
            setImgSources(imgSources => ({
                ...imgSources,
                [betClass] : newBet
            }));
        }
        else{
            if (selectedChipValue > availableChips){
                alert("You do not have enough chips for this bet.")
            }
            else{
                setAvailableChips(availableChips - selectedChipValue)
                const newBet = {isBet : !imgSources[betClass].isBet, betValue: selectedChipValue};
                setImgSources(imgSources => ({
                    ...imgSources,
                    [betClass] : newBet
                }));
            }
        }
      };

    function handleSelectChip (e){
        const chipClasses = e.target.classList;
        switch(chipClasses[0]){
            case "chip-five":
                setSelectedChipValue(5);
                break;
            case "chip-ten":
                setSelectedChipValue(10);
                break;
            case "chip-fifty":
                setSelectedChipValue(50);
                break
            default:
                setSelectedChipValue(5);
        }
    }

    // function handleConfirm(e){
    //     e.preventDefault();
    //     let rouletteBets = [];
    //     Object.keys(imgSources).forEach((betKey) => {
    //         if(imgSources[betKey].isBet){
    //             let betValues = [];
    //             for (const item in String(betKey).split("-").slice(1)){
    //                 betValues.push(Number(String(betKey).split("-").slice(1)[item]))
    //             }
    //             const betItem = {
    //                 amount : imgSources[betKey].betValue,
    //                 type : String(betKey).split("-")[0],
    //                 values : betValues
    //             };
    //             rouletteBets.push(betItem);
    //             //post to back
    //         }
    //     })
    // }

    function handleClearBets(e){
        e.preventDefault();
        setImgSources(initalImgSources);
        setAvailableChips(availableChipsInitial);
    }

  return (
    <div className="roulette-table-content">
        <div className="roulette-table-bets">
            <div className="empty side">
                {/* {imageTen ? (<img src={chipTen} alt="" className="test-coin" />) : ""}
                {imageFive ? (<img src={chipFive} alt="" className="test-coin" />) : ""}
                {imageFifty ? (<img src={chipFifty} alt="" className="test-coin" />) : ""} */}
            </div>
            <div className="empty side"></div>
            <div className="first-four inside-0-1-2-3" onClick={handleBetClick}>
            { imgSources['inside-0-1-2-3'].isBet && <img src={imgSources["inside-0-1-2-3"].betValue===10 ? chipTen : (imgSources["inside-0-1-2-3"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div> 
            <div className="street inside-1-2-3" onClick={handleBetClick}>{ imgSources['inside-1-2-3'].isBet && <img src={imgSources["inside-1-2-3"].betValue===10 ? chipTen : (imgSources["inside-1-2-3"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-1-2-3-4-5-6" onClick={handleBetClick}>{ imgSources['inside-1-2-3-4-5-6'].isBet && <img src={imgSources["inside-1-2-3-4-5-6"].betValue===10 ? chipTen : (imgSources["inside-1-2-3-4-5-6"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-4-5-6" onClick={handleBetClick}>{ imgSources['inside-4-5-6'].isBet && <img src={imgSources["inside-4-5-6"].betValue===10 ? chipTen : (imgSources["inside-4-5-6"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-4-5-6-7-8-9" onClick={handleBetClick}>{ imgSources['inside-4-5-6-7-8-9'].isBet && <img src={imgSources["inside-4-5-6-7-8-9"].betValue===10 ? chipTen : (imgSources["inside-4-5-6-7-8-9"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-7-8-9" onClick={handleBetClick}>{ imgSources['inside-7-8-9'].isBet && <img src={imgSources["inside-7-8-9"].betValue===10 ? chipTen : (imgSources["inside-7-8-9"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-7-8-9-10-11-12" onClick={handleBetClick}>{ imgSources['inside-7-8-9-10-11-12'].isBet && <img src={imgSources["inside-7-8-9-10-11-12"].betValue===10 ? chipTen : (imgSources["inside-7-8-9-10-11-12"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-10-11-12" onClick={handleBetClick}>{ imgSources['inside-10-11-12'].isBet && <img src={imgSources["inside-10-11-12"].betValue===10 ? chipTen : (imgSources["inside-10-11-12"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-10-11-12-13-14-15" onClick={handleBetClick}>{ imgSources['inside-10-11-12-13-14-15'].isBet && <img src={imgSources["inside-10-11-12-13-14-15"].betValue===10 ? chipTen : (imgSources["inside-10-11-12-13-14-15"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-13-14-15" onClick={handleBetClick}>{ imgSources['inside-13-14-15'].isBet && <img src={imgSources["inside-13-14-15"].betValue===10 ? chipTen : (imgSources["inside-13-14-15"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-13-14-15-16-17-18" onClick={handleBetClick}>{ imgSources['inside-13-14-15-16-17-18'].isBet && <img src={imgSources["inside-13-14-15-16-17-18"].betValue===10 ? chipTen : (imgSources["inside-13-14-15-16-17-18"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-16-17-18" onClick={handleBetClick}>{ imgSources['inside-16-17-18'].isBet && <img src={imgSources["inside-16-17-18"].betValue===10 ? chipTen : (imgSources["inside-16-17-18"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-16-17-18-19-20-21" onClick={handleBetClick}>{ imgSources['inside-16-17-18-19-20-21'].isBet && <img src={imgSources["inside-16-17-18-19-20-21"].betValue===10 ? chipTen : (imgSources["inside-16-17-18-19-20-21"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-19-20-21" onClick={handleBetClick}>{ imgSources['inside-19-20-21'].isBet && <img src={imgSources["inside-19-20-21"].betValue===10 ? chipTen : (imgSources["inside-19-20-21"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-19-20-21-22-23-24" onClick={handleBetClick}>{ imgSources['inside-19-20-21-22-23-24'].isBet && <img src={imgSources["inside-19-20-21-22-23-24"].betValue===10 ? chipTen : (imgSources["inside-19-20-21-22-23-24"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-22-23-24" onClick={handleBetClick}>{ imgSources['inside-22-23-24'].isBet && <img src={imgSources["inside-22-23-24"].betValue===10 ? chipTen : (imgSources["inside-22-23-24"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-22-23-24-25-26-27" onClick={handleBetClick}>{ imgSources['inside-22-23-24-25-26-27'].isBet && <img src={imgSources["inside-22-23-24-25-26-27"].betValue===10 ? chipTen : (imgSources["inside-22-23-24-25-26-27"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-25-26-27" onClick={handleBetClick}>{ imgSources['inside-25-26-27'].isBet && <img src={imgSources["inside-25-26-27"].betValue===10 ? chipTen : (imgSources["inside-25-26-27"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-25-26-27-28-29-30" onClick={handleBetClick}>{ imgSources['inside-25-26-27-28-29-30'].isBet && <img src={imgSources["inside-25-26-27-28-29-30"].betValue===10 ? chipTen : (imgSources["inside-25-26-27-28-29-30"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-28-29-30" onClick={handleBetClick}>{ imgSources['inside-28-29-30'].isBet && <img src={imgSources["inside-28-29-30"].betValue===10 ? chipTen : (imgSources["inside-28-29-30"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-28-29-30-31-32-33" onClick={handleBetClick}>{ imgSources['inside-28-29-30-31-32-33'].isBet && <img src={imgSources["inside-28-29-30-31-32-33"].betValue===10 ? chipTen : (imgSources["inside-28-29-30-31-32-33"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-31-32-33" onClick={handleBetClick}>{ imgSources['inside-31-32-33'].isBet && <img src={imgSources["inside-31-32-33"].betValue===10 ? chipTen : (imgSources["inside-31-32-33"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="sixline inside-31-32-33-34-35-36" onClick={handleBetClick}>{ imgSources['inside-31-32-33-34-35-36'].isBet && <img src={imgSources["inside-31-32-33-34-35-36"].betValue===10 ? chipTen : (imgSources["inside-31-32-33-34-35-36"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="street inside-34-35-36" onClick={handleBetClick}>{ imgSources['inside-34-35-36'].isBet && <img src={imgSources["inside-34-35-36"].betValue===10 ? chipTen : (imgSources["inside-34-35-36"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="single inside-0" onClick={handleBetClick}>0{ imgSources['inside-0'].isBet && <img src={imgSources["inside-0"].betValue===10 ? chipTen : (imgSources["inside-0"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-0-3" onClick={handleBetClick}>{ imgSources['inside-0-3'].isBet && <img src={imgSources["inside-0-3"].betValue===10 ? chipTen : (imgSources["inside-0-3"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-3 red" onClick={handleBetClick}>
                3 
                { imgSources['inside-3'].isBet && <img src={imgSources["inside-3"].betValue===10 ? chipTen : (imgSources["inside-3"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }
            </div>
            <div className="split inside-3-6" onClick={handleBetClick}>{ imgSources['inside-3-6'].isBet && <img src={imgSources["inside-3-6"].betValue===10 ? chipTen : (imgSources["inside-3-6"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-6 black" onClick={handleBetClick}>6{ imgSources['inside-6'].isBet && <img src={imgSources["inside-6"].betValue===10 ? chipTen : (imgSources["inside-6"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-6-9" onClick={handleBetClick}>{ imgSources['inside-6-9'].isBet && <img src={imgSources["inside-6-9"].betValue===10 ? chipTen : (imgSources["inside-6-9"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-9 red" onClick={handleBetClick}>9{ imgSources['inside-9'].isBet && <img src={imgSources["inside-9"].betValue===10 ? chipTen : (imgSources["inside-9"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-9-12" onClick={handleBetClick}>{ imgSources['inside-9-12'].isBet && <img src={imgSources["inside-9-12"].betValue===10 ? chipTen : (imgSources["inside-9-12"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-12 red" onClick={handleBetClick}>12{ imgSources['inside-12'].isBet && <img src={imgSources["inside-12"].betValue===10 ? chipTen : (imgSources["inside-12"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-12-15" onClick={handleBetClick}>{ imgSources['inside-12-15'].isBet && <img src={imgSources["inside-12-15"].betValue===10 ? chipTen : (imgSources["inside-12-15"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-15 black" onClick={handleBetClick}>15{ imgSources['inside-15'].isBet && <img src={imgSources["inside-15"].betValue===10 ? chipTen : (imgSources["inside-15"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-15-18" onClick={handleBetClick}>{ imgSources['inside-15-18'].isBet && <img src={imgSources["inside-15-18"].betValue===10 ? chipTen : (imgSources["inside-15-18"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-18 red" onClick={handleBetClick}>18{ imgSources['inside-18'].isBet && <img src={imgSources["inside-18"].betValue===10 ? chipTen : (imgSources["inside-18"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-18-21" onClick={handleBetClick}>{ imgSources['inside-18-21'].isBet && <img src={imgSources["inside-18-21"].betValue===10 ? chipTen : (imgSources["inside-18-21"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-21 red" onClick={handleBetClick}>21{ imgSources['inside-21'].isBet && <img src={imgSources["inside-21"].betValue===10 ? chipTen : (imgSources["inside-21"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-21-24" onClick={handleBetClick}>{ imgSources['inside-21-24'].isBet && <img src={imgSources["inside-21-24"].betValue===10 ? chipTen : (imgSources["inside-21-24"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-24 black" onClick={handleBetClick}>24{ imgSources['inside-24'].isBet && <img src={imgSources["inside-24"].betValue===10 ? chipTen : (imgSources["inside-24"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-24-27" onClick={handleBetClick}>{ imgSources['inside-24-27'].isBet && <img src={imgSources["inside-24-27"].betValue===10 ? chipTen : (imgSources["inside-24-27"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-27 red" onClick={handleBetClick}>27{ imgSources['inside-27'].isBet && <img src={imgSources["inside-27"].betValue===10 ? chipTen : (imgSources["inside-27"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-27-30" onClick={handleBetClick}>{ imgSources['inside-27-30'].isBet && <img src={imgSources["inside-27-30"].betValue===10 ? chipTen : (imgSources["inside-27-30"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-30 red" onClick={handleBetClick}>30{ imgSources['inside-30'].isBet && <img src={imgSources["inside-30"].betValue===10 ? chipTen : (imgSources["inside-30"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-30-33" onClick={handleBetClick}>{ imgSources['inside-30-33'].isBet && <img src={imgSources["inside-30-33"].betValue===10 ? chipTen : (imgSources["inside-30-33"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-33 black" onClick={handleBetClick}>33{ imgSources['inside-33'].isBet && <img src={imgSources["inside-33"].betValue===10 ? chipTen : (imgSources["inside-33"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-33-36" onClick={handleBetClick}>{ imgSources['inside-33-36'].isBet && <img src={imgSources["inside-33-36"].betValue===10 ? chipTen : (imgSources["inside-33-36"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-36 red" onClick={handleBetClick}>36{ imgSources['inside-36'].isBet && <img src={imgSources["inside-36"].betValue===10 ? chipTen : (imgSources["inside-36"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="column column-0" onClick={handleBetClick}>2 to 1{ imgSources['column-0'].isBet && <img src={imgSources["column-0"].betValue===10 ? chipTen : (imgSources["column-0"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="street inside-0-2-3" onClick={handleBetClick}>{ imgSources['inside-0-2-3'].isBet && <img src={imgSources["inside-0-2-3"].betValue===10 ? chipTen : (imgSources["inside-0-2-3"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-2-3" onClick={handleBetClick}>{ imgSources['inside-2-3'].isBet && <img src={imgSources["inside-2-3"].betValue===10 ? chipTen : (imgSources["inside-2-3"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-2-3-5-6" onClick={handleBetClick}>{ imgSources['inside-2-3-5-6'].isBet && <img src={imgSources["inside-2-3-5-6"].betValue===10 ? chipTen : (imgSources["inside-2-3-5-6"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-5-6" onClick={handleBetClick}>{ imgSources['inside-5-6'].isBet && <img src={imgSources["inside-5-6"].betValue===10 ? chipTen : (imgSources["inside-5-6"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-5-6-8-9" onClick={handleBetClick}>{ imgSources['inside-5-6-8-9'].isBet && <img src={imgSources["inside-5-6-8-9"].betValue===10 ? chipTen : (imgSources["inside-5-6-8-9"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-8-9" onClick={handleBetClick}>{ imgSources['inside-8-9'].isBet && <img src={imgSources["inside-8-9"].betValue===10 ? chipTen : (imgSources["inside-8-9"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-8-9-11-12" onClick={handleBetClick}>{ imgSources['inside-8-9-11-12'].isBet && <img src={imgSources["inside-8-9-11-12"].betValue===10 ? chipTen : (imgSources["inside-8-9-11-12"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-11-12" onClick={handleBetClick}>{ imgSources['inside-11-12'].isBet && <img src={imgSources["inside-11-12"].betValue===10 ? chipTen : (imgSources["inside-11-12"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-11-12-14-15" onClick={handleBetClick}>{ imgSources['inside-11-12-14-15'].isBet && <img src={imgSources["inside-11-12-14-15"].betValue===10 ? chipTen : (imgSources["inside-11-12-14-15"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-14-15" onClick={handleBetClick}>{ imgSources['inside-14-15'].isBet && <img src={imgSources["inside-14-15"].betValue===10 ? chipTen : (imgSources["inside-14-15"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-14-15-17-18" onClick={handleBetClick}>{ imgSources['inside-14-15-17-18'].isBet && <img src={imgSources["inside-14-15-17-18"].betValue===10 ? chipTen : (imgSources["inside-14-15-17-18"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-17-18" onClick={handleBetClick}>{ imgSources['inside-17-18'].isBet && <img src={imgSources["inside-17-18"].betValue===10 ? chipTen : (imgSources["inside-17-18"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-17-18-20-21" onClick={handleBetClick}>{ imgSources['inside-17-18-20-21'].isBet && <img src={imgSources["inside-17-18-20-21"].betValue===10 ? chipTen : (imgSources["inside-17-18-20-21"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-20-21" onClick={handleBetClick}>{ imgSources['inside-20-21'].isBet && <img src={imgSources["inside-20-21"].betValue===10 ? chipTen : (imgSources["inside-20-21"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-20-21-23-24" onClick={handleBetClick}>{ imgSources['inside-20-21-23-24'].isBet && <img src={imgSources["inside-20-21-23-24"].betValue===10 ? chipTen : (imgSources["inside-20-21-23-24"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-23-24" onClick={handleBetClick}>{ imgSources['inside-23-24'].isBet && <img src={imgSources["inside-23-24"].betValue===10 ? chipTen : (imgSources["inside-23-24"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-23-24-26-27" onClick={handleBetClick}>{ imgSources['inside-23-24-26-27'].isBet && <img src={imgSources["inside-23-24-26-27"].betValue===10 ? chipTen : (imgSources["inside-23-24-26-27"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-26-27" onClick={handleBetClick}>{ imgSources['inside-26-27'].isBet && <img src={imgSources["inside-26-27"].betValue===10 ? chipTen : (imgSources["inside-26-27"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-26-27-29-30" onClick={handleBetClick}>{ imgSources['inside-26-27-29-30'].isBet && <img src={imgSources["inside-26-27-29-30"].betValue===10 ? chipTen : (imgSources["inside-26-27-29-30"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-29-30" onClick={handleBetClick}>{ imgSources['inside-29-30'].isBet && <img src={imgSources["inside-29-30"].betValue===10 ? chipTen : (imgSources["inside-29-30"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-29-30-32-33" onClick={handleBetClick}>{ imgSources['inside-29-30-32-33'].isBet && <img src={imgSources["inside-29-30-32-33"].betValue===10 ? chipTen : (imgSources["inside-29-30-32-33"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-32-33" onClick={handleBetClick}>{ imgSources['inside-32-33'].isBet && <img src={imgSources["inside-32-33"].betValue===10 ? chipTen : (imgSources["inside-32-33"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-32-33-35-36" onClick={handleBetClick}>{ imgSources['inside-32-33-35-36'].isBet && <img src={imgSources["inside-32-33-35-36"].betValue===10 ? chipTen : (imgSources["inside-32-33-35-36"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-35-36" onClick={handleBetClick}>{ imgSources['inside-35-36'].isBet && <img src={imgSources["inside-35-36"].betValue===10 ? chipTen : (imgSources["inside-35-36"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="split inside-0-2" onClick={handleBetClick}>{ imgSources['inside-0-2'].isBet && <img src={imgSources["inside-0-2"].betValue===10 ? chipTen : (imgSources["inside-0-2"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-2 black" onClick={handleBetClick}>2{ imgSources['inside-2'].isBet && <img src={imgSources["inside-2"].betValue===10 ? chipTen : (imgSources["inside-2"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-2-5" onClick={handleBetClick}>{ imgSources['inside-2-5'].isBet && <img src={imgSources["inside-2-5"].betValue===10 ? chipTen : (imgSources["inside-2-5"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-5 red" onClick={handleBetClick}>5{ imgSources['inside-5'].isBet && <img src={imgSources["inside-5"].betValue===10 ? chipTen : (imgSources["inside-5"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-5-8" onClick={handleBetClick}>{ imgSources['inside-5-8'].isBet && <img src={imgSources["inside-5-8"].betValue===10 ? chipTen : (imgSources["inside-5-8"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-8 black" onClick={handleBetClick}>8{ imgSources['inside-8'].isBet && <img src={imgSources["inside-8"].betValue===10 ? chipTen : (imgSources["inside-8"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-8-11" onClick={handleBetClick}>{ imgSources['inside-8-11'].isBet && <img src={imgSources["inside-8-11"].betValue===10 ? chipTen : (imgSources["inside-8-11"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-11 black" onClick={handleBetClick}>11{ imgSources['inside-11'].isBet && <img src={imgSources["inside-11"].betValue===10 ? chipTen : (imgSources["inside-11"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-11-14" onClick={handleBetClick}>{ imgSources['inside-11-14'].isBet && <img src={imgSources["inside-11-14"].betValue===10 ? chipTen : (imgSources["inside-11-14"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-14 red" onClick={handleBetClick}>14{ imgSources['inside-14'].isBet && <img src={imgSources["inside-14"].betValue===10 ? chipTen : (imgSources["inside-14"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-14-17" onClick={handleBetClick}>{ imgSources['inside-14-17'].isBet && <img src={imgSources["inside-14-17"].betValue===10 ? chipTen : (imgSources["inside-14-17"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-17 black" onClick={handleBetClick}>17{ imgSources['inside-17'].isBet && <img src={imgSources["inside-17"].betValue===10 ? chipTen : (imgSources["inside-17"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-17-20" onClick={handleBetClick}>{ imgSources['inside-17-20'].isBet && <img src={imgSources["inside-17-20"].betValue===10 ? chipTen : (imgSources["inside-17-20"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-20 black" onClick={handleBetClick}>20{ imgSources['inside-20'].isBet && <img src={imgSources["inside-20"].betValue===10 ? chipTen : (imgSources["inside-20"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-20-23" onClick={handleBetClick}>{ imgSources['inside-20-23'].isBet && <img src={imgSources["inside-20-23"].betValue===10 ? chipTen : (imgSources["inside-20-23"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-23 red" onClick={handleBetClick}>23{ imgSources['inside-23'].isBet && <img src={imgSources["inside-23"].betValue===10 ? chipTen : (imgSources["inside-23"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-23-26" onClick={handleBetClick}>{ imgSources['inside-23-26'].isBet && <img src={imgSources["inside-23-26"].betValue===10 ? chipTen : (imgSources["inside-23-26"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-26 black" onClick={handleBetClick}>26{ imgSources['inside-26'].isBet && <img src={imgSources["inside-26"].betValue===10 ? chipTen : (imgSources["inside-26"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-26-29" onClick={handleBetClick}>{ imgSources['inside-26-29'].isBet && <img src={imgSources["inside-26-29"].betValue===10 ? chipTen : (imgSources["inside-26-29"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-29 black" onClick={handleBetClick}>29{ imgSources['inside-29'].isBet && <img src={imgSources["inside-29"].betValue===10 ? chipTen : (imgSources["inside-29"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-29-32" onClick={handleBetClick}>{ imgSources['inside-29-32'].isBet && <img src={imgSources["inside-29-32"].betValue===10 ? chipTen : (imgSources["inside-29-32"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-32 red" onClick={handleBetClick}>32{ imgSources['inside-32'].isBet && <img src={imgSources["inside-32"].betValue===10 ? chipTen : (imgSources["inside-32"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-32-35" onClick={handleBetClick}>{ imgSources['inside-32-35'].isBet && <img src={imgSources["inside-32-35"].betValue===10 ? chipTen : (imgSources["inside-32-35"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-35 black" onClick={handleBetClick}>35{ imgSources['inside-35'].isBet && <img src={imgSources["inside-35"].betValue===10 ? chipTen : (imgSources["inside-35"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="column column-2" onClick={handleBetClick}>2 to 1{ imgSources['column-2'].isBet && <img src={imgSources["column-2"].betValue===10 ? chipTen : (imgSources["column-2"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div> 
            <div className="empty"></div>
            <div className="street inside-0-1-2" onClick={handleBetClick}>{ imgSources['inside-0-1-2'].isBet && <img src={imgSources["inside-0-1-2"].betValue===10 ? chipTen : (imgSources["inside-0-1-2"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-1-2" onClick={handleBetClick}>{ imgSources['inside-1-2'].isBet && <img src={imgSources["inside-1-2"].betValue===10 ? chipTen : (imgSources["inside-1-2"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-1-2-4-5" onClick={handleBetClick}>{ imgSources['inside-1-2-4-5'].isBet && <img src={imgSources["inside-1-2-4-5"].betValue===10 ? chipTen : (imgSources["inside-1-2-4-5"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-4-5" onClick={handleBetClick}>{ imgSources['inside-4-5'].isBet && <img src={imgSources["inside-4-5"].betValue===10 ? chipTen : (imgSources["inside-4-5"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-4-5-7-8" onClick={handleBetClick}>{ imgSources['inside-4-5-7-8'].isBet && <img src={imgSources["inside-4-5-7-8"].betValue===10 ? chipTen : (imgSources["inside-4-5-7-8"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-7-8" onClick={handleBetClick}>{ imgSources['inside-7-8'].isBet && <img src={imgSources["inside-7-8"].betValue===10 ? chipTen : (imgSources["inside-7-8"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-7-8-10-11" onClick={handleBetClick}>{ imgSources['inside-7-8-10-11'].isBet && <img src={imgSources["inside-7-8-10-11"].betValue===10 ? chipTen : (imgSources["inside-7-8-10-11"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-10-11" onClick={handleBetClick}>{ imgSources['inside-10-11'].isBet && <img src={imgSources["inside-10-11"].betValue===10 ? chipTen : (imgSources["inside-10-11"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-10-11-13-14" onClick={handleBetClick}>{ imgSources['inside-10-11-13-14'].isBet && <img src={imgSources["inside-10-11-13-14"].betValue===10 ? chipTen : (imgSources["inside-10-11-13-14"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-13-14" onClick={handleBetClick}>{ imgSources['inside-13-14'].isBet && <img src={imgSources["inside-13-14"].betValue===10 ? chipTen : (imgSources["inside-13-14"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-13-14-16-17" onClick={handleBetClick}>{ imgSources['inside-13-14-16-17'].isBet && <img src={imgSources["inside-13-14-16-17"].betValue===10 ? chipTen : (imgSources["inside-13-14-16-17"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-16-17" onClick={handleBetClick}>{ imgSources['inside-16-17'].isBet && <img src={imgSources["inside-16-17"].betValue===10 ? chipTen : (imgSources["inside-16-17"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-16-17-19-20" onClick={handleBetClick}>{ imgSources['inside-16-17-19-20'].isBet && <img src={imgSources["inside-16-17-19-20"].betValue===10 ? chipTen : (imgSources["inside-16-17-19-20"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-19-20" onClick={handleBetClick}>{ imgSources['inside-19-20'].isBet && <img src={imgSources["inside-19-20"].betValue===10 ? chipTen : (imgSources["inside-19-20"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-19-20-22-23" onClick={handleBetClick}>{ imgSources['inside-19-20-22-23'].isBet && <img src={imgSources["inside-19-20-22-23"].betValue===10 ? chipTen : (imgSources["inside-19-20-22-23"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-22-23" onClick={handleBetClick}>{ imgSources['inside-22-23'].isBet && <img src={imgSources["inside-22-23"].betValue===10 ? chipTen : (imgSources["inside-22-23"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-22-23-25-26" onClick={handleBetClick}>{ imgSources['inside-22-23-25-26'].isBet && <img src={imgSources["inside-22-23-25-26"].betValue===10 ? chipTen : (imgSources["inside-22-23-25-26"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-25-26" onClick={handleBetClick}>{ imgSources['inside-25-26'].isBet && <img src={imgSources["inside-25-26"].betValue===10 ? chipTen : (imgSources["inside-25-26"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-25-26-28-29" onClick={handleBetClick}>{ imgSources['inside-25-26-28-29'].isBet && <img src={imgSources["inside-25-26-28-29"].betValue===10 ? chipTen : (imgSources["inside-25-26-28-29"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-28-29" onClick={handleBetClick}>{ imgSources['inside-28-29'].isBet && <img src={imgSources["inside-28-29"].betValue===10 ? chipTen : (imgSources["inside-28-29"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-28-29-31-32" onClick={handleBetClick}>{ imgSources['inside-28-29-31-32'].isBet && <img src={imgSources["inside-28-29-31-32"].betValue===10 ? chipTen : (imgSources["inside-28-29-31-32"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-31-32" onClick={handleBetClick}>{ imgSources['inside-31-32'].isBet && <img src={imgSources["inside-31-32"].betValue===10 ? chipTen : (imgSources["inside-31-32"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="corner inside-31-32-34-35" onClick={handleBetClick}>{ imgSources['inside-31-32-34-35'].isBet && <img src={imgSources["inside-31-32-34-35"].betValue===10 ? chipTen : (imgSources["inside-31-32-34-35"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-34-35" onClick={handleBetClick}>{ imgSources['inside-34-35'].isBet && <img src={imgSources["inside-34-35"].betValue===10 ? chipTen : (imgSources["inside-34-35"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="split inside-0-1" onClick={handleBetClick}>{ imgSources['inside-0-1'].isBet && <img src={imgSources["inside-0-1"].betValue===10 ? chipTen : (imgSources["inside-0-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-1 red" onClick={handleBetClick}>1{ imgSources['inside-1'].isBet && <img src={imgSources["inside-1"].betValue===10 ? chipTen : (imgSources["inside-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-1-4" onClick={handleBetClick}>{ imgSources['inside-1-4'].isBet && <img src={imgSources["inside-1-4"].betValue===10 ? chipTen : (imgSources["inside-1-4"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-4 black" onClick={handleBetClick}>4{ imgSources['inside-4'].isBet && <img src={imgSources["inside-4"].betValue===10 ? chipTen : (imgSources["inside-4"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-4-7" onClick={handleBetClick}>{ imgSources['inside-4-7'].isBet && <img src={imgSources["inside-4-7"].betValue===10 ? chipTen : (imgSources["inside-4-7"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-7 red" onClick={handleBetClick}>7{ imgSources['inside-7'].isBet && <img src={imgSources["inside-7"].betValue===10 ? chipTen : (imgSources["inside-7"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-7-10" onClick={handleBetClick}>{ imgSources['inside-7-10'].isBet && <img src={imgSources["inside-7-10"].betValue===10 ? chipTen : (imgSources["inside-7-10"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-10 red" onClick={handleBetClick}>10{ imgSources['inside-10'].isBet && <img src={imgSources["inside-10"].betValue===10 ? chipTen : (imgSources["inside-10"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-10-13" onClick={handleBetClick}>{ imgSources['inside-10-13'].isBet && <img src={imgSources["inside-10-13"].betValue===10 ? chipTen : (imgSources["inside-10-13"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-13 black" onClick={handleBetClick}>13{ imgSources['inside-13'].isBet && <img src={imgSources["inside-13"].betValue===10 ? chipTen : (imgSources["inside-13"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-13-16" onClick={handleBetClick}>{ imgSources['inside-13-16'].isBet && <img src={imgSources["inside-13-16"].betValue===10 ? chipTen : (imgSources["inside-13-16"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-16 red" onClick={handleBetClick}>16{ imgSources['inside-16'].isBet && <img src={imgSources["inside-16"].betValue===10 ? chipTen : (imgSources["inside-16"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-16-19" onClick={handleBetClick}>{ imgSources['inside-16-19'].isBet && <img src={imgSources["inside-16-19"].betValue===10 ? chipTen : (imgSources["inside-16-19"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-19 red" onClick={handleBetClick}>19{ imgSources['inside-19'].isBet && <img src={imgSources["inside-19"].betValue===10 ? chipTen : (imgSources["inside-19"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-19-22" onClick={handleBetClick}>{ imgSources['inside-19-22'].isBet && <img src={imgSources["inside-19-22"].betValue===10 ? chipTen : (imgSources["inside-19-22"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-22 black" onClick={handleBetClick}>22{ imgSources['inside-22'].isBet && <img src={imgSources["inside-22"].betValue===10 ? chipTen : (imgSources["inside-22"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-22-25" onClick={handleBetClick}>{ imgSources['inside-22-25'].isBet && <img src={imgSources["inside-22-25"].betValue===10 ? chipTen : (imgSources["inside-22-25"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-25 red" onClick={handleBetClick}>25{ imgSources['inside-25'].isBet && <img src={imgSources["inside-25"].betValue===10 ? chipTen : (imgSources["inside-25"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-25-28" onClick={handleBetClick}>{ imgSources['inside-25-28'].isBet && <img src={imgSources["inside-25-28"].betValue===10 ? chipTen : (imgSources["inside-25-28"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-28 red" onClick={handleBetClick}>28{ imgSources['inside-28'].isBet && <img src={imgSources["inside-28"].betValue===10 ? chipTen : (imgSources["inside-28"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-28-31" onClick={handleBetClick}>{ imgSources['inside-28-31'].isBet && <img src={imgSources["inside-28-31"].betValue===10 ? chipTen : (imgSources["inside-28-31"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-31 black" onClick={handleBetClick}>31{ imgSources['inside-31'].isBet && <img src={imgSources["inside-31"].betValue===10 ? chipTen : (imgSources["inside-31"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="split inside-31-34" onClick={handleBetClick}>{ imgSources['inside-31-34'].isBet && <img src={imgSources["inside-31-34"].betValue===10 ? chipTen : (imgSources["inside-31-34"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="single inside-34 red" onClick={handleBetClick}>34{ imgSources['inside-34'].isBet && <img src={imgSources["inside-34"].betValue===10 ? chipTen : (imgSources["inside-34"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="column column-1" onClick={handleBetClick}>2 to 1{ imgSources['column-1'].isBet && <img src={imgSources["column-1"].betValue===10 ? chipTen : (imgSources["column-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            {/* line for outside bets */}
            <div></div>
            <div></div>
            <div className="empty"></div>
            <div className="first-dozen dozen-0" onClick={handleBetClick}>1rst Dozen { imgSources['dozen-0'].isBet && <img src={imgSources["dozen-0"].betValue===10 ? chipTen : (imgSources["dozen-0"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="second-dozen dozen-1" onClick={handleBetClick}>2nd Dozen { imgSources['dozen-1'].isBet && <img src={imgSources["dozen-1"].betValue===10 ? chipTen : (imgSources["dozen-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="third-dozen dozen-2" onClick={handleBetClick}>3rd Dozen { imgSources['dozen-2'].isBet && <img src={imgSources["dozen-2"].betValue===10 ? chipTen : (imgSources["dozen-2"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div></div>
            <div></div>

            <div></div>
            <div></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div></div>
            <div></div>

            <div></div>
            <div></div>
            <div className="empty"></div>
            <div className="low lowHigh-0" onClick={handleBetClick}>1-18 { imgSources['lowHigh-0'].isBet && <img src={imgSources["lowHigh-0"].betValue===10 ? chipTen : (imgSources["lowHigh-0"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="even oddEven-0" onClick={handleBetClick}>EVEN { imgSources['oddEven-0'].isBet && <img src={imgSources["oddEven-0"].betValue===10 ? chipTen : (imgSources["oddEven-0"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="red-outside blackRed-1" onClick={handleBetClick}>RED { imgSources['blackRed-1'].isBet && <img src={imgSources["blackRed-1"].betValue===10 ? chipTen : (imgSources["blackRed-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="black-outside blackRed-0" onClick={handleBetClick}>BLACK { imgSources['blackRed-0'].isBet && <img src={imgSources["blackRed-0"].betValue===10 ? chipTen : (imgSources["blackRed-0"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="odd oddEven-1" onClick={handleBetClick}>ODD { imgSources['oddEven-1'].isBet && <img src={imgSources["oddEven-1"].betValue===10 ? chipTen : (imgSources["oddEven-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div className="high lowHigh-1" onClick={handleBetClick}>19-36 { imgSources['lowHigh-1'].isBet && <img src={imgSources["lowHigh-1"].betValue===10 ? chipTen : (imgSources["lowHigh-1"].betValue===5 ? chipFive : chipFifty)} alt="" class="test-coin"/> }</div>
            <div className="empty"></div>
            <div></div>
            <div></div>

            <div></div>
            <div></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div className="empty"></div>
            <div></div>
            <div></div>
        </div>

        <div className="roulette-bet">
            <div className="roulette-bet-chip">
                <img src={chipFive} alt="" className={selectedChipValue===5 ? "chip-five active" : "chip-five"} onClick={handleSelectChip}/>
                <img src={chipTen} alt="" className={selectedChipValue===10 ? "chip-ten active" : "chip-ten"} onClick={handleSelectChip}/>
                <img src={chipFifty} alt="" className={selectedChipValue===50 ? "chip-fifty active" : "chip-fifty"} onClick={handleSelectChip} />
            </div>
            <div className="bet-buttons">
                <button type="button" className="clear-bet" onClick={handleClearBets}>CLEAR ALL BETS</button>
                <button type="button" className="confirm-bet" onClick={event => handleConfirm(imgSources)}>CONFIRM BETS</button>
            </div>
            <div className="available-chips"> Available chips : {availableChips}</div>
        </div>
    </div>
  )
}

export default RouletteTable