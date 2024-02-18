import React from 'react'
import "./Footer.css"

const Footer = () => {
  return (
    <div className="footer">
        <div className="footer-logo">
        easyBet
        </div>
        <div className="footer-info">
            <div className="contact-info">
                <h1>CONTACT</h1>
                <p>client-support@easybet.com</p>
                <p>(XX) XX XX XX XX</p>
            </div>
            <div className="aboutus-info">
                <h1>ABOUT US</h1>
                <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip</p>
            </div>
        </div>
        <p>Copyright© 2024</p>
    </div>
  )
}

export default Footer