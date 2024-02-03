import { React, useState } from "react";
import { TextInput, TouchableOpacity, View, Text, Alert } from "react-native";
import styled from "styled-components/native";
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
    ${tw`rounded-lg px-4 py-2 mb-2 w-40 items-center`}
`;

const SaveButton = styled(Button)`
    ${tw`bg-green-500`}
`;

const LogOutButton = styled(Button)`
    ${tw`bg-red-500`}
`;

const CancelButton = styled(Button)`
    ${tw`bg-orange-500`}
`;

const DeleteButton = styled(Button)`
    ${tw`bg-black`}
`;

const ButtonText = styled(Text)`
    ${tw`text-white font-bold`}
`;

const DeleteText = styled(Text)`
    ${tw`text-red-500 font-bold`}
`;

const ChangeProfile = ({ navigation }) => {
    const [password, setPassword] = useState("");
    const [confirmedPassword, setConfirmedPassword] = useState("");
    const [surname, setSurname] = useState("");
    const { username, token, logout } = useAuth();

    const navigateToProfile = () => {
        navigation.navigate("Profile");
    };

    const handleLogOut = async () => {
        await logout().then(navigation.navigate("Login"));
    };

    const handleChange = async () => {
        if (!password === confirmedPassword) {
            alert("Password must match");
            return;
        }
        await fetch(API + "/" + username, {
            headers: {
                "x-access-token": token,
                "Content-Type": "application/x-www-form-urlencoded",
            },
            method: "PUT",
            body: "password=" + password + "&surname=" + surname,
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    alert("Account modified");
                    navigateToProfile();
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    const handleDelete = async () => {
        await fetch(API + "/" + username, {
            headers: {
                "x-access-token": token,
                "Content-Type": "application/x-www-form-urlencoded",
            },
            method: "DELETE",
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    alert("Account deleted");
                    navigation.navigate("Login");
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    const confirmDelete = () => {
        Alert.alert(
            "Delete Account?",
            "Do you really want to delete your account? This is permanent.",
            [
                {
                    text: "Yes, delete my account",
                    onPress: () => handleDelete(),
                    style: "destructive",
                },
                {
                    text: "No, go back",
                    onPress: () => navigateToProfile(),
                    style: "cancel",
                },
            ]
        );
    };

    return (
        <Container>
            <Title>Modify your profile {username}</Title>
            <Input
                placeholder="New Password"
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
                placeholder="New Surname"
                placeholderTextColor="white"
                value={surname}
                onChangeText={(text) => setSurname(text)}
            />
            <SaveButton onPress={handleChange}>
                <ButtonText>Save</ButtonText>
            </SaveButton>
            <CancelButton onPress={navigateToProfile}>
                <ButtonText>Cancel</ButtonText>
            </CancelButton>
            <LogOutButton onPress={handleLogOut}>
                <ButtonText>Log out</ButtonText>
            </LogOutButton>
            <DeleteButton onPress={confirmDelete}>
                <DeleteText>Delete account</DeleteText>
            </DeleteButton>
        </Container>
    );
};

export default ChangeProfile;
