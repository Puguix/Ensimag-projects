import React, { useState, useEffect } from 'react';
import { BrowserRouter, Route, Routes, useLocation } from 'react-router-dom';
import './App.css';
import Home from './Pages/Home';
import LoginSignup from './Pages/LoginSignup';
import Dashboard from './Pages/Dashboard';
import AuthProvider from './Context/AuthContext';
import PrivateRoute from './PrivateRoute';
import Profile from './Pages/Profile';
import Wallet from './Pages/Wallet';
import Navbar from './Components/Navbar/Navbar';
import Footer from './Components/Footer/Footer';
import Roulette from './Pages/Roulette';
import Blackjack from './Pages/Blackjack';
import LoadingPage from './Pages/LoadingPage'; // Import the LoadingPage component

function Layout() {
    const location = useLocation();
    // Check if the path is '/login' or '', in this case, do not display Navbar and Footer
    const showNavbarAndFooter = location.pathname !== "/login" && location.pathname !== "/";

    return (
        <>
            {showNavbarAndFooter && <Navbar />}
            <AuthProvider>
                <Routes>
                    <Route path="" element={<Home />} />
                    <Route path="/login" element={<LoginSignup />} />
                    <Route element={<PrivateRoute />}>
                        <Route path="/Dashboard" element={<Dashboard />}></Route>
                        <Route path="/Profile" element={<Profile />}></Route>
                        <Route path="/Wallet" element={<Wallet />}></Route>
                        <Route path="/Roulette" element={<Roulette />}></Route>
                        <Route path="/Blackjack" element={<Blackjack />}></Route>
                    </Route>
                </Routes>
            </AuthProvider>
            {showNavbarAndFooter && <Footer />}
        </>
    );
}

function App() {
    const [isLoading, setIsLoading] = useState(true);

    useEffect(() => {
        // Simulate data loading or any async operation
        setTimeout(() => {
            setIsLoading(false);
        }, 3000);
    }, []);

    return (
        <BrowserRouter>
            <AuthProvider>
                {isLoading ? <LoadingPage /> : <Layout />} {/* Render LoadingPage if loading, otherwise render Layout */}
            </AuthProvider>
        </BrowserRouter>
    );
}

export default App;
