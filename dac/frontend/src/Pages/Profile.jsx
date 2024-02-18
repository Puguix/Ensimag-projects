import React, { useState, useEffect } from "react";
import "./CSS/Profile.css";
import userModify from "../Assets/icons/edit-profile.svg";
import PopupDelete from "../Components/PopupDelete/PopupDelete";
import "./LoginSignup.jsx";
import { useNavigate } from "react-router-dom";

const Profile = () => {
    const [isEditing, setIsEditing] = useState(false);
    const [showPopup, setShowPopup] = useState(false);
    const [userInfo, setUserInfo] = useState({
        surname: "",
        firstname: "",
        dateOfBirth: "",
        email: "",
    });
    const [errors, setErrors] = useState({});
    const [showSuccessMessage, setShowSuccessMessage] = useState(false);
    const navigate = useNavigate();

    useEffect(() => {
        fetchUserProfile();
    }, []);

    async function fetchUserProfile() {
        try {
            const response = await fetch("http://localhost:8085/players", {
                headers: {
                    token: localStorage.getItem("token"),
                },
            });
            //console.log(response);
            //console.log(response.ok);
            if (response.ok) {
                const userData = await response.json();
                setUserInfo({
                    surname: userData.surname || "",
                    firstname: userData.firstName || "",
                    dateOfBirth: userData.dateOfBirth || "",
                    email: userData.email,
                });
            } else {
                console.error("Failed to fetch user profile:", response.status);
            }
        } catch (error) {
            console.error("Error fetching user profile:", error);
        }
    }

    async function handleDelete() {
        try {
            const token = localStorage.getItem("token"); // Récupérer le token depuis le stockage local
            if (!token) {
                console.error("No token found");
                return;
            }
    
            const response = await fetch("http://localhost:8085/players", {
                method: 'DELETE',
                headers: {
                    'token':token,
                },
            });
    
            if (response.ok) {
                // Si la suppression est réussie, naviguer vers la page de connexion ou la page d'accueil
                navigate('/login');
                console.log("Account deleted successfully");
            } else {
                console.error("Failed to delete account:", response.status);
            }
        } catch (error) {
            console.error("Error deleting account:", error);
        }
    }

    const validateField = (name, value) => {
        let errorMsg = "";
        switch (name) {
            case "email":
                const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
                if (!emailRegex.test(value))
                    errorMsg = "Email must be a valid email address.";
                break;
        }
        setErrors((prevErrors) => ({ ...prevErrors, [name]: errorMsg }));
        return errorMsg === "";
    };

    const handleEditClick = () => setIsEditing(true);
    const handleCancelClick = () => setIsEditing(false);

    const handleSaveClick = async () => {
        const allValid = Object.keys(userInfo).every((key) => {
            return validateField(key, userInfo[key]);
        });
        if (allValid) {
            await updateUserInfo();
            setIsEditing(false);
            setShowSuccessMessage(true);
            setTimeout(() => setShowSuccessMessage(false), 4000);
        }
    };

    async function updateUserInfo() {
        try {
            const response = await fetch(
                "http://localhost:8085/players",
                {
                    // Update this endpoint as necessary
                    method: "PUT",
                    headers: {
                        "Content-Type": "application/json",
                        token : localStorage.getItem("token"),
                        // 'Authorization': 'Bearer ' + localStorage.getItem('token'),
                    },
                    body: JSON.stringify({
                        email: userInfo.email,
                        password: "",
                        firstName: userInfo.firstname,
                        surname: userInfo.surname,
                        dateOfBirth: userInfo.dateOfBirth
                    }),
                }
            );
            if (!response.ok) throw new Error("Failed to update profile");
            console.log("Profile updated successfully");
            // Handle success scenario, e.g., showing a success message
        } catch (error) {
            console.error("Error updating user profile:", error);
            // Handle error scenario
        }
    }

    const handleChange = (e) => {
        const { name, value } = e.target;
        setUserInfo((prevState) => ({ ...prevState, [name]: value }));
        validateField(name, value);
    };

    const togglePopup = () => {
        setShowPopup(!showPopup);
    };

    // Function to confirm deletion
    const confirmDelete = async () => {
        await handleDelete();
        navigate('/login'); 
    };

    return (
        <div className="dashboard-content">
            <div className="user-profile">
                <h1>User Profile</h1>
                {showSuccessMessage && (
                    <div className="success-message">
                        Profile updated successfully!
                    </div>
                )}
                <div className="user-info">
                    {isEditing ? (
                        <>
                            {Object.entries(userInfo).map(([key, value]) => (
                                <div key={key} className="input-group">
                                    <label>{key}</label>
                                    <input
                                        type="text"
                                        name={key}
                                        value={value}
                                        onChange={handleChange}
                                        className={
                                            errors[key] ? "error-input" : ""
                                        }
                                    />
                                    {errors[key] && (
                                        <div className="error-msg">
                                            {errors[key]}
                                        </div>
                                    )}
                                </div>
                            ))}
                            <button
                                onClick={handleCancelClick}
                                className="save-button"
                                disabled={Object.values(errors).some(
                                    (error) => error
                                )}
                            >
                                Cancel
                            </button>
                            <button
                                onClick={handleSaveClick}
                                className="save-button"
                                disabled={Object.values(errors).some(
                                    (error) => error
                                )}
                            >
                                Save
                            </button>
                        </>
                    ) : (
                        <>
                            <div className="info-display">
                                <strong>Surname:</strong> {userInfo.surname}
                            </div>
                            <div className="info-display">
                                <strong>Firstname:</strong> {userInfo.firstname}
                            </div>
                            <div className="info-display">
                                <strong>Birthdate:</strong> {userInfo.dateOfBirth}
                            </div>
                            <div className="info-display">
                                <strong>Email:</strong> {userInfo.email}
                            </div>
                            <button
                                onClick={handleEditClick}
                                className="edit-button"
                            >
                                <img src={userModify} alt="Edit Profile" />
                            </button>
                        </>
                    )}
                </div>
                {!isEditing && (
                    <button type="button" onClick={handleDelete} className="delete-account">
                        Delete Account
                    </button>
                )}
            </div>
        </div>
    );
};

export default Profile;