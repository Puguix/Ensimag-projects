import React, { useEffect } from 'react'
import "./RouletteWheel.css"
import gsap from "gsap";
import rouletteWheel from "../../Assets/rouletteWheel.png"
import rouletteMarble from "../../Assets/rouletteMarble.png"

const RouletteWheel = (props) => {
    const numberPositions = {
        "0" : 0,
        "32" : 9.72973,
        "15" : 19.45946,
        "19" : 29.18919,
        "4" : 38.91892,
        "21" : 48.648647,
        "2" : 58.378376,
        "25" : 68.10811,
        "17" : 77.83784,
        "34" : 87.567566,
        "6" : 97.297295,
        "27" : 107.02702,
        "13" : 116.75675,
        "36" : 126.48648,
        "11" : 136.21622,
        "30" : 145.94595,
        "8" : 155.67569,
        "23" : 165.40543,
        "10" : 175.13516,
        "5" : 184.8649,
        "24" : 194.59464,
        "16" : 204.32437,
        "33" : 214.05411,
        "1" : 223.78384,
        "20" : 233.51358,
        "14" : 243.24332,
        "31" : 252.97305,
        "9" : 262.7028,
        "22" : 272.43253,
        "18" : 282.16226,
        "29" : 291.892,
        "7" : 301.62173,
        "28" : 311.35147,
        "12" : 321.0812,
        "35" : 330.81094,
        "3" : 340.54068,
        "26": 350.27042
    }
    const stopAt = numberPositions[props.rouletteRes]
    const circleRef = React.useRef(null);
    const [spinning, setSpinning] = React.useState(false);
    
    const loopIteration = React.useRef(0);
    const stopRotation = React.useMemo(() => 360 + stopAt, [stopAt]);
      
        // const handleStartSpinning = () => {
        //   setSpinning(true);
        // };
      
    const stopAnim = gsap.to(circleRef.current, {
        rotation: `+=${stopRotation}`,
          // Calculate the new duration ...
          // ... to make the transition between spinning and ...
          // ... stopping as smooth as possible.
        duration: stopRotation / 360,
        paused: true,
        overwrite: true
    });
      
    const loopAnim = gsap.to(circleRef.current, {
        rotation: "+=360",
        ease: "none",
        duration: 0.5,
        onComplete: () => {
        // The props won't update in here...
        if (loopIteration.current >= 5 && typeof stopAt === "number") {
            stopAnim.play();
        } else {
            loopIteration.current++;
            loopAnim.play(0);
        }
        },
        paused: true
    });
      
    const startAnim = gsap.to(circleRef.current, {
        rotation: "+=360",
        ease: "power1.in",
        duration: 1,
        onComplete: () => loopAnim.play(),
        paused: true
    });
    
    React.useEffect(() => {
        if (spinning) {
        startAnim.play();
        } else {
        stopAnim.play();
        }
    }, [spinning]);
      
    // React.useEffect(() => {
    //     console.log("prop", { stopAt });
    // }, [stopAt]);  

    function handleSpin(e){
        console.log("spinnin?")
        setSpinning(!spinning)
        props.endGame(true);
   
    }



  return (
    <div className="roulette-wheel-content">
        <div className="roulette-wheel-images">
            <img src={rouletteWheel} alt="" className='roulette-wheel-image'/>
            <img src={rouletteMarble} alt="" ref={circleRef} className='roulette-ball'/>
        </div>
        {props.canSpin && <button className="spin-roulette" onClick={handleSpin}>SPIN</button>}
    </div>
  )
}

export default RouletteWheel