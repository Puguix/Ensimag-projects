import React from 'react';
import background_home from "../Assets/essai_display2.png";
import "./CSS/Home.css";
import { Link } from 'react-router-dom';

const Home = () => {
  return (
    <div className="App-home">
        {/* Corrigez classname en className */}
        <img src={background_home} alt="Home Background" className="background-home"/>
        <div className="link-to-login">
          <Link to='/login'>CLICK TO PLAY</Link>
        </div>
    </div>
  );
}

export default Home;
