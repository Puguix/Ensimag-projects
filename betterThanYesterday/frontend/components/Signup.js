import { React, useState } from "react";
import styled from "styled-components/native";
import { View, Text, TextInput, TouchableOpacity } from "react-native";
import tw from "twrnc";
import { API } from "../utils/ApiLink";
import { useAuth } from "../utils/AuthContext";

const Container = styled(View)`
    ${tw`flex-1 justify-center items-center bg-gray-900`}
`;

const Title = styled(Text)`
    ${tw`text-4xl font-bold mb-4 text-pink-300 w-2/3`}
    text-align: center
`;

const Input = styled(TextInput)`
    ${tw`w-3/4 px-4 py-2 border rounded mb-4 text-white`}
`;

const Button = styled(TouchableOpacity)`
    ${tw`bg-gray-200 px-4 py-2 rounded`}
    margin-bottom: 6px;
`;

const ButtonText = styled(Text)`
    ${tw`text-pink-600 text-center`}
`;

const SignUp = ({ navigation }) => {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const [confirmedPassword, setConfirmedPassword] = useState("");
    const [email, setEmail] = useState("");
    const [surname, setSurname] = useState("");
    const { login } = useAuth();

    const navigateToLogin = () => {
        navigation.navigate("Login");
    };
    const navigateToHome = () => {
        navigation.navigate("Home");
    };

    const handleSignUp = async () => {
        if (!password === confirmedPassword) {
            alert("Password must match");
            return;
        }
        await fetch(API + "/signUp", {
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
            method: "POST",
            body:
                "username=" +
                username +
                "&password=" +
                password +
                "&email=" +
                email +
                "&surname=" +
                surname,
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    login(username, res["token"]);
                    alert("Account created!");
                    navigateToHome();
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    return (
        <Container>
            <Title>Better Than Yesterday</Title>
            <Input
                placeholder="Mail adress"
                placeholderTextColor="white"
                value={email}
                onChangeText={(text) => setEmail(text)}
            />
            <Input
                placeholder="Username"
                placeholderTextColor="white"
                value={username}
                onChangeText={(text) => setUsername(text)}
            />
            <Input
                placeholder="Password"
                placeholderTextColor="white"
                secureTextEntry
                value={password}
                onChangeText={(text) => setPassword(text)}
            />
            <Input
                placeholder="Confirm Password"
                placeholderTextColor="white"
                secureTextEntry
                value={confirmedPassword}
                onChangeText={(text) => setConfirmedPassword(text)}
            />
            <Input
                placeholder="Surname"
                placeholderTextColor="white"
                value={surname}
                onChangeText={(text) => setSurname(text)}
            />
            <Button onPress={handleSignUp}>
                <ButtonText>Sign up</ButtonText>
            </Button>
            <Button onPress={navigateToLogin}>
                <ButtonText>Login</ButtonText>
            </Button>
        </Container>
    );
};

export default SignUp;
