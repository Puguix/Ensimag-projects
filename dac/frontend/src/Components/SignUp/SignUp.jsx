import React, { useState } from 'react';
import "./SignUp.css";
import { useAuth } from '../../Context/AuthContext';

const SignUp = () => {
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [firstName, setFirstName] = useState("");
    const [surname, setSurname] = useState("");
    const [birthdate, setBirthdate] = useState("");
    const [termsAccepted, setTermsAccepted] = useState(false);
    const [errors, setErrors] = useState({});
    const [signupSuccess, setSignupSuccess] = useState(false);
    const auth = useAuth();

    const validateField = (name, value) => {
        let errorMsg = '';
        switch (name) {
            case 'email':
                if (!/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value)) errorMsg = 'Invalid email format.';
                break;
            case 'password':
                if (value.length < 8) errorMsg = 'Password must be at least 8 characters.';
                break;
            case 'birthdate':
                const dateRegex = /^(0[1-9]|[12][0-9]|3[01])\/(0[1-9]|1[012])\/(19|20)\d\d$/;
                if (!dateRegex.test(value)) {
                    errorMsg = 'Date must be in DD/MM/YYYY format.';
                } else {
                    const birthday = new Date(value.split('/').reverse().join('-'));
                    console.log(value);
                    const ageDifMs = Date.now() - birthday.getTime();
                    const ageDate = new Date(ageDifMs);
                    const age = Math.abs(ageDate.getUTCFullYear() - 1970);
                    if (age < 18) {
                        errorMsg = 'You must be over 18 years old.';
                    }
                }
                break;
            default:
                errorMsg = '';
        }
        setErrors(prevErrors => ({ ...prevErrors, [name]: errorMsg }));
    };

    const handleInputChange = (e) => {
        const { name, value } = e.target;
        validateField(name, value);
        switch (name) {
            case 'email':
                setEmail(value);
                break;
            case 'password':
                setPassword(value);
                break;
            case 'firstName':
                setFirstName(value);
                break;
            case 'surname':
                setSurname(value);
                break;
            case 'birthdate':
                setBirthdate(value);
                break;
            case 'terms':
                setTermsAccepted(e.target.checked);
                if (e.target.checked) {
                    setErrors({ ...errors, terms: '' });
                } else {
                    setErrors({ ...errors, terms: 'You must accept the Terms and Conditions to register.' });
                }
                break;
            default:
                break;
        }
    };

    const handleSignUp = async (e) => {
        e.preventDefault();
        if (Object.values(errors).every(error => !error) && termsAccepted) {
            try {
                let dateOfBirth = birthdate.split('/').reverse().join('-')
                console.log(dateOfBirth)
                const response = await fetch('http://localhost:8085/players', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify({
                        email,
                        password,
                        firstName,
                        surname,
                        dateOfBirth
                    }),
                });
    
                if (response.ok) {
                    setSignupSuccess(true);
                    auth.loginAfterSignup({email:email, password:password})
                    // Clear form fields
                    setEmail("");
                    setPassword("");
                    setFirstName("");
                    setSurname("");
                    setBirthdate("");
                    setTermsAccepted(false);
                    setErrors({});
                } else {
                    const responseData = await response.json();
                    if (responseData.error) {
                        setErrors({ ...errors, signup: responseData.error });
                    } else {
                        setErrors({ ...errors, signup: 'An error occurred during signup.' });
                    }
                }
            } catch (error) {
                console.error('Error during signup:', error);
                setErrors({ ...errors, signup: 'An error occurred during signup.' });
            }
        } else {
            setErrors({ ...errors, terms: 'You must accept the Terms and Conditions to register.' });
        }
    };

    const isFormValid = () => {
        return (
            email && password && firstName && surname && birthdate &&
            termsAccepted && Object.values(errors).every(error => !error)
        );
    };

    return (
        <div className="signup">
            <p className="signup-heading">Sign Up</p>
            {signupSuccess && (
                <div className="signup-success-message">
                    Signup successful! You can now log in to access the app.
                </div>
            )}
            <form onSubmit={handleSignUp} className="signup-form">
                <input
                    type="email"
                    name="email"
                    className="input-field"
                    placeholder="Email address"
                    value={email}
                    onChange={handleInputChange}
                />
                {errors.email && <div className="error-msg">{errors.email}</div>}

                <input
                    type="password"
                    name="password"
                    className="input-field"
                    placeholder="Password"
                    value={password}
                    onChange={handleInputChange}
                />
                {errors.password && <div className="error-msg">{errors.password}</div>}

                <input
                    type="text"
                    name="firstName"
                    className="input-field"
                    placeholder="First name"
                    value={firstName}
                    onChange={handleInputChange}
                />
                {errors.firstName && <div className="error-msg">{errors.firstName}</div>}

                <input
                    type="text"
                    name="surname"
                    className="input-field"
                    placeholder="Surname"
                    value={surname}
                    onChange={handleInputChange}
                />
                {errors.surname && <div className="error-msg">{errors.surname}</div>}

                <input
                    type="text"
                    name="birthdate"
                    className="input-field"
                    placeholder="Birthdate DD/MM/YYYY"
                    value={birthdate}
                    onChange={handleInputChange}
                />
                {errors.birthdate && <div className="error-msg">{errors.birthdate}</div>}

                <label className="terms-container">
                    <input
                        type="checkbox"
                        name="terms"
                        className="terms-checkbox"
                        checked={termsAccepted}
                        onChange={handleInputChange}
                    />
                    I have read and agree with the Terms and Conditions.
                </label>
                {errors.terms && <div className="error-msg">{errors.terms}</div>}

                <button
                    type="submit"
                    className="signup-button"
                    disabled={!isFormValid()}
                >
                    Register now
                </button>
            </form>
        </div>
    );
}

export default SignUp;
