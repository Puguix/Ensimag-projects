import React from 'react'
import "./CSS/LoginSignup.css"
import Login from '../Components/Login/Login'
import SignUp from '../Components/SignUp/SignUp'

const LoginSignup = () => {
  return (
    <div className="login-signup">
        <div className="titles">
            <h1>easyBet</h1>
            <h2>To PLAY is to <em>WIN</em></h2>
        </div>
        <div className="login-signup-containers">
            <Login/>
            <SignUp/>
        </div>
    </div>
  )
}

export default LoginSignup