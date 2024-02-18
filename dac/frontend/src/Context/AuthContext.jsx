import { useContext, createContext, useState } from "react";
import { useNavigate } from "react-router-dom";

const AuthContext = createContext();

const AuthProvider = ({ children }) => {
  // const [ userid, setUserid ] = useState(localStorage.getItem("userid")||"");
  const [ token, setToken ] = useState(localStorage.getItem("token") || "blabla");
  const [ chips, setChips ] = useState(localStorage.getItem("chips")||0);
  const [loginError, setLoginError] = useState();
  const navigate = useNavigate();
  const loginAction = async (data) => {
    try {
      const response = await fetch('http://localhost:8085/players/login', {
        method: "POST",
        headers: {
          "Content-Type": "application/json",
        },
        body: JSON.stringify(data),
      });
      const res = await response.json();
      if (res.status) {
        console.log(res);
        setToken(res.token);
        localStorage.setItem("token", res.token);
        //localStorage.setItem("chips", res.chips);
        //get user chips
        alert("Login successful")

      //   const responseUser = await fetch('http://localhost:8085/players', {
      //   method: "GET",
      //   headers: {
      //     "Content-Type": "application/json",
      //     'x-access-token': token
      //   },
      //   body: JSON.stringify(data),
      // });
      // const resUser = await response.json();
      // if (resUser.status){
      //   setChips(res.data);
      //   localStorage.setItem("chips", res.data)
      // };

        // const userData = res.user;
        // setUserid(userData["id"]);
        // localStorage.setItem("userid", userData["id"])
        // setToken(userData["token"]);
        // localStorage.setItem("token", userData.token);
        // setChips(userData["chips"]);
        // localStorage.setItem("chips", userData.chips);
        }
        navigate("/Dashboard");
        return
      
    } catch (err) {
      alert("Please check your login information again");
      console.error(err);
    }
  };


  function loginAfterSignup( data){
    setLoginError('');

    const apiEndpoint = 'http://localhost:8085/players/login';

    return fetch(apiEndpoint, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(data),
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


  const getToken = async () => {
    try {
      const response = await fetch('http://localhost:8085/players/chips', {
        method: "GET",
        headers: { 'Content-Type': 'application/json',  'token': localStorage.getItem('token')},
      });
      const res = await response.json();
      if (res.status) {
        console.log(res);
        // setToken(res.token);
        localStorage.setItem("chips", res.chips);
        //localStorage.setItem("chips", res.chips);
        //get user chips
        //alert("Login successful")

      //   const responseUser = await fetch('http://localhost:8085/players', {
      //   method: "GET",
      //   headers: {
      //     "Content-Type": "application/json",
      //     'x-access-token': token
      //   },
      //   body: JSON.stringify(data),
      // });
      // const resUser = await response.json();
      // if (resUser.status){
      //   setChips(res.data);
      //   localStorage.setItem("chips", res.data)
      // };

        // const userData = res.user;
        // setUserid(userData["id"]);
        // localStorage.setItem("userid", userData["id"])
        // setToken(userData["token"]);
        // localStorage.setItem("token", userData.token);
        // setChips(userData["chips"]);
        // localStorage.setItem("chips", userData.chips);
        }
        navigate("/Dashboard");
        return
      
    } catch (err) {
      alert("Please check your login information again");
      console.error(err);
    }
  };

//   const signUp = async (data) => {
//     try {
//       const response = await fetch("http://localhost:3001/login", {
//         method: "POST",
//         headers: {
//           "Content-Type": "application/json",
//         },
//         body: JSON.stringify(data),
//       });
//       const res = await response.json();
//       if (res.status) {
//         const userData = res.user;
//         setToken(userData["token"]);
//         localStorage.setItem("site", userData.token);
//         setChips(user.chips);
//         // navigate("/");
//         return;
//       }
//       throw new Error(res.message);
//     } catch (err) {
//       alert("Please check your login information again");
//       console.error(err);
//     }
//   };

  const logOut = () => {
    // setUserid("");
    // localStorage.removeItem("userid");
    setToken("");
    localStorage.removeItem("token");
    setChips("");
    localStorage.removeItem("chips");
    navigate("/Dashboard");
  };

  return (
    <AuthContext.Provider value={{ token, chips, loginAction, logOut, loginAfterSignup}}>
      {children}
    </AuthContext.Provider>
  );

};

export default AuthProvider;

export const useAuth = () => {
  return useContext(AuthContext);
};
