import React, { createContext, useContext, useState, useEffect } from "react";
import AsyncStorage from "@react-native-async-storage/async-storage";

const AuthContext = createContext(null);

export const AuthProvider = ({ children }) => {
    const [token, setToken] = useState(null);
    const [username, setUsername] = useState(null);

    useEffect(() => {
        // Load the access token from AsyncStorage on app startup
        const loadCredentials = async () => {
            try {
                const storedToken = await AsyncStorage.getItem("token");
                const storedUsername = await AsyncStorage.getItem("username");
                setToken(storedToken);
                setUsername(storedUsername);
            } catch (error) {
                console.error(
                    "Error loading authentification information",
                    error
                );
            }
        };

        loadCredentials();
    }, []);

    const login = async (name, token) => {
        // Save the access token to AsyncStorage
        try {
            await AsyncStorage.setItem("token", token);
            await AsyncStorage.setItem("username", name);
            setToken(token);
            setUsername(name);
        } catch (error) {
            console.error("Error saving credentials:", error);
        }
    };

    const logout = async () => {
        // Remove the access token from AsyncStorage
        try {
            await AsyncStorage.removeItem("token");
            await AsyncStorage.removeItem("username");
            setToken(null);
            setUsername(null);
        } catch (error) {
            console.error("Error removing access token:", error);
        }
    };

    return (
        <AuthContext.Provider value={{ username, token, login, logout }}>
            {children}
        </AuthContext.Provider>
    );
};

export const useAuth = () => {
    return useContext(AuthContext);
};
