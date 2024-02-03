import React from "react";
import styled from "styled-components/native";
import { View, TouchableOpacity } from "react-native";
import tw from "twrnc";
import Icon from "react-native-vector-icons/Ionicons";

const Container = styled(View)`
    ${tw`flex-row justify-between items-center p-4 bg-gray-800`}
    border-top-width: 1px;
    border-top-color: white;
`;

const Footer = ({ navigation }) => {
    const navigateToHome = () => {
        navigation.navigate("Home");
    };
    const navigateToCreate = () => {
        navigation.navigate("Create");
    };
    const navigateToProfile = () => {
        navigation.navigate("Profile");
    };

    return (
        <Container>
            <TouchableOpacity
                style={tw`flex-1 items-center`}
                onPress={() => navigateToHome()}
            >
                <Icon name="home" size={30} color="white" />
            </TouchableOpacity>

            <TouchableOpacity
                style={tw`flex-1 items-center`}
                onPress={() => navigateToCreate()}
            >
                <Icon name="add" size={30} color="white" />
            </TouchableOpacity>

            <TouchableOpacity
                style={tw`flex-1 items-center`}
                onPress={() => navigateToProfile()}
            >
                <Icon name="person" size={30} color="white" />
            </TouchableOpacity>
        </Container>
    );
};

export default Footer;
