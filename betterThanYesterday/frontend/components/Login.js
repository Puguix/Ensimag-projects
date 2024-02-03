import { React, useState } from "react";
import styled from "styled-components/native";
import { View, Text, TextInput, TouchableOpacity } from "react-native";
import tw from "twrnc";
import { useAuth } from "../utils/AuthContext";
import { API } from "../utils/ApiLink";

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

const Login = ({ navigation }) => {
    const [username, setUsername] = useState("");
    const [password, setPassword] = useState("");
    const { login } = useAuth();

    const navigateToSignUp = () => {
        navigation.navigate("SignUp");
    };
    const navigateToHome = () => {
        navigation.navigate("Home");
    };

    const handleLogin = async () => {
        console.log("Login...", username, password);
        await fetch(API + "/login", {
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
            },
            method: "POST",
            body: "username=" + username + "&password=" + password,
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    login(username, res["token"]);
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
            <Button onPress={handleLogin}>
                <ButtonText>Login</ButtonText>
            </Button>
            <Button onPress={navigateToSignUp}>
                <ButtonText>Sign up</ButtonText>
            </Button>
        </Container>
    );
};

export default Login;
