import React from "react";
import { View, Text, TouchableOpacity, Alert } from "react-native";
import tw from "twrnc";
import styled from "styled-components/native";
import Icon from "react-native-vector-icons/FontAwesome";
import { useAuth } from "../utils/AuthContext";
import { API } from "../utils/ApiLink";

const Container = styled(View)`
    ${tw`flex-row justify-between items-center p-4 bg-gray-900 pt-10`} border-bottom-width: 1px;
    border-bottom-color: white;
`;

const Header = () => {
    const { username, token } = useAuth();

    const handleFollow = async (surname) => {
        await fetch(API + "/" + username + "/" + surname, {
            headers: {
                "x-access-token": token,
                "Content-Type": "application/x-www-form-urlencoded",
            },
            method: "POST",
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    alert("Account followed");
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    const addFriend = async () => {
        Alert.prompt(
            "Add friend",
            "Type the surname of the user you want to follow",
            [
                {
                    text: "Add this friend",
                    onPress: async (surname) => {
                        await handleFollow(surname);
                    },
                },
                {
                    text: "Go back",
                    style: "cancel",
                },
            ],
            "plain-text"
        );
    };

    return (
        <Container>
            <Text style={tw`text-pink-500 text-lg`}>BTY</Text>
            <TouchableOpacity onPress={addFriend}>
                <Icon name="user-plus" size={24} color="white" />
            </TouchableOpacity>
        </Container>
    );
};

export default Header;
