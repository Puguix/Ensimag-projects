import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import "./Login.css";
import "../../Pages/Dashboard.jsx";
import { useAuth } from '../../Context/AuthContext.jsx';

const Login = () => {
    const [emailUser, setEmailUser] = useState('');
    const [passwordUser, setPasswordUser] = useState('');
    const [loginError, setLoginError] = useState(''); 

    const navigate = useNavigate();
    const auth = useAuth();

    function handleLogin(e) {
        e.preventDefault();
        setLoginError('');
    
        const apiEndpoint = 'http://localhost:8085/players/login';
    
        const loginData = {
            email: emailUser,
            password: passwordUser,
        };
    
        return fetch(apiEndpoint, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(loginData),
        })
        .then((response) => {
            if (response.ok) {
                return response.text();  // Récupérer la réponse comme une chaîne de caractères
            } else {
                // Handle login failure by setting the error message
                throw new Error('Login failed');
            }
        })
        .then((token) => {
            // Stocker le token JWT dans le stockage local du navigateur
            localStorage.setItem('token', token);
            console.log('Login successful', token);
            //navigate('/Dashboard'); // Redirection vers le tableau de bord
            getChips();
    
            return token; // Retourner le token pour une utilisation ultérieure
        })
        .catch((error) => {
            // Handle login failure and other errors
            setLoginError(error.message);
            console.error('Error:', error);
            throw error; // Permet de propager l'erreur pour la gérer dans le composant appelant si nécessaire
        });
    }
    



  const getChips = async () => {
    console.log("je rentre");
    try {
      const response = await fetch('http://localhost:8085/players', {
        method: "GET",
        headers: { 'Content-Type': 'application/json',  'token': localStorage.getItem('token')},
      });
      const res = await response.json();
      //console.log(res);
      localStorage.setItem("chips", parseInt(res.nbChip, 10));
      localStorage.setItem("surname",res.surname);

      
    //   if (res.ok) {
        
    //     console.log("user a x jetons");
    //     console.log(res);
    //     // setToken(res.token);
    //     localStorage.setItem("chips", res);
    //     //localStorage.setItem("chips", res.chips);
    //     //get user chips
    //     //alert("Login successful")

    //   //   const responseUser = await fetch('http://localhost:8085/players', {
    //   //   method: "GET",
    //   //   headers: {
    //   //     "Content-Type": "application/json",
    //   //     'x-access-token': token
    //   //   },
    //   //   body: JSON.stringify(data),
    //   // });
    //   // const resUser = await response.json();
    //   // if (resUser.status){
    //   //   setChips(res.data);
    //   //   localStorage.setItem("chips", res.data)
    //   // };

    //     // const userData = res.user;
    //     // setUserid(userData["id"]);
    //     // localStorage.setItem("userid", userData["id"])
    //     // setToken(userData["token"]);
    //     // localStorage.setItem("token", userData.token);
    //     // setChips(userData["chips"]);
    //     // localStorage.setItem("chips", userData.chips);
    //     }
    //     else {
    //         console.log("ça merde");
    //     }
        navigate("/Dashboard");
      
    } catch (err) {
      alert("Please check your login information again");
      console.error(err);
    }
  };
    

    return (
        <div className="login-container">
            <div className="login-header">Sign In</div>
            <form onSubmit={handleLogin} className="login-form">
                <input 
                    type="email" 
                    className="email-input" 
                    placeholder="Email address"
                    value={emailUser}
                    onChange={e => setEmailUser(e.target.value)}
                />
                <input 
                    type="password" 
                    className="password-input" 
                    placeholder="Password"
                    value={passwordUser}
                    onChange={e => setPasswordUser(e.target.value)}
                />
                {loginError && <div className="login-error">{loginError}</div>}
                <a href="#forgot" className="forgot-password">Forgot your password?</a>
                <button type="submit" className="login-button">Login</button>
            </form>
        </div>
    );
}

export default Login;
