import React, { useState } from "react";
import { View, TextInput, Text, TouchableOpacity } from "react-native";
import styled from "styled-components/native";
import tw from "twrnc";
import Header from "./Header";
import Footer from "./Footer";
import { API } from "../utils/ApiLink";
import Icon from "react-native-vector-icons/MaterialCommunityIcons";
import Icon2 from "react-native-vector-icons/FontAwesome";
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

const CreateButton = styled(TouchableOpacity)`
    ${tw`bg-green-500 px-4 py-2 rounded`}
    margin-bottom: 6px;
`;

const CancelButton = styled(TouchableOpacity)`
    ${tw`bg-red-500 px-4 py-2 rounded`}
    margin-bottom: 6px;
`;

const ButtonText = styled(Text)`
    ${tw`text-gray-200 text-center`}
`;

const Create = ({ navigation }) => {
    const [title, setTitle] = useState("");
    const [type, setType] = useState("");
    const [description, setDescription] = useState("");
    const [isFlexColored, setFlexColor] = useState("");
    const [isBrainColored, setBrainColor] = useState("");
    const [isMoneyColored, setMoneyColor] = useState("");
    const { username, token } = useAuth();

    const navigateToHome = () => {
        navigation.navigate("Home");
    };

    const handleCreation = async () => {
        if (type === undefined) setType("Other");
        await fetch(API + "/" + username + "/posts", {
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
                "x-access-token": token,
            },
            method: "POST",
            body:
                "title=" +
                title +
                "&type=" +
                type +
                "&description=" +
                description,
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    alert("Post online!");
                    navigateToHome();
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    function changeType(type) {
        setType(type);
        switch (type) {
            case "Sport":
                setFlexColor(true);
                setBrainColor(false);
                setMoneyColor(false);
                break;
            case "Culture":
                setFlexColor(false);
                setBrainColor(true);
                setMoneyColor(false);
                break;
            case "Travail":
                setFlexColor(false);
                setBrainColor(false);
                setMoneyColor(true);
                break;
        }
    }

    function handleCancel() {
        setDescription("");
        setTitle("");
    }

    return (
        <>
            <Header navigation={navigation} />
            <Container>
                <Title>What did you achieved?</Title>
                <Input
                    placeholder="Title"
                    placeholderTextColor="white"
                    value={title}
                    onChangeText={(text) => setTitle(text)}
                />
                <Input
                    placeholder="description"
                    placeholderTextColor="white"
                    value={description}
                    onChangeText={(text) => setDescription(text)}
                />
                <View style={tw`flex-row justify-between py-4`}>
                    <TouchableOpacity
                        onPress={() => changeType("Sport")}
                        style={tw`mr-4`}
                    >
                        <Icon
                            name="arm-flex"
                            size={24}
                            color={isFlexColored ? "yellow" : "white"}
                        />
                    </TouchableOpacity>
                    <TouchableOpacity
                        onPress={() => changeType("Culture")}
                        style={tw`mr-4`}
                    >
                        <Icon
                            name="brain"
                            size={24}
                            color={isBrainColored ? "pink" : "white"}
                        />
                    </TouchableOpacity>
                    <TouchableOpacity onPress={() => changeType("Travail")}>
                        <Icon2
                            name="money"
                            size={24}
                            color={isMoneyColored ? "green" : "white"}
                        />
                    </TouchableOpacity>
                </View>
                <View style={tw`flex-row justify-between py-4`}>
                    <CreateButton onPress={handleCreation} style={tw`mr-6`}>
                        <ButtonText>Post</ButtonText>
                    </CreateButton>
                    <CancelButton onPress={handleCancel}>
                        <ButtonText>Cancel</ButtonText>
                    </CancelButton>
                </View>
            </Container>
            <Footer navigation={navigation} />
        </>
    );
};

export default Create;
