import React from "react";
import { View, Text, TouchableOpacity, FlatList, Alert } from "react-native";
import styled from "styled-components/native";
import tw from "twrnc";
import Comment from "./Comment";
import Icon from "react-native-vector-icons/Entypo";
import Icon3 from "react-native-vector-icons/MaterialCommunityIcons";
import Icon2 from "react-native-vector-icons/FontAwesome";
import { API } from "../utils/ApiLink";
import { useAuth } from "../utils/AuthContext";

const Container = styled(View)`
    ${tw`flex-1 justify-center p-4`}
    background-color: ${(props) => props.color};
`;

const ReactionsContainer = styled(View)`
    ${tw`flex-row justify-between pb-2`}
`;

const ReactionContainer = styled(View)`
    ${tw`flex-row items-center`}
`;

const TextContainer = styled(View)`
    ${tw`items-center`}
`;

const Title = styled(Text)`
    ${tw`text-4xl font-bold mb-4 text-black w-2/3`}
    text-align: center
`;

const Description = styled(Text)`
    ${tw`text-m font-bold mb-4 text-black w-2/3`}
    text-align: center
`;

const OwnPost = ({ item }) => {
    const postColors = {
        Sport: "orange",
        Culture: "red",
        Travail: "cyan",
        Mental: "purple",
        Other: "blue",
    };

    const reactionCounts = {
        Strong: 0,
        Brain: 0,
        Money: 0,
    };
    item["reactions"].forEach((reaction) => {
        reactionCounts[reaction["reaction"]]++;
    });

    const { username, token } = useAuth();

    const handleDelete = async () => {
        await fetch(API + "/" + username + "/" + item["id"], {
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
                "x-access-token": token,
            },
            method: "DELETE",
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    alert("Post deleted");
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    const confirmDelete = () => {
        Alert.alert(
            "Delete Post?",
            "Do you really want to delete your post? This is permanent.",
            [
                {
                    text: "Yes, delete my post",
                    onPress: () => handleDelete(),
                    style: "destructive",
                },
                {
                    text: "No, go back",
                    style: "cancel",
                },
            ]
        );
    };

    return (
        <>
            <Container color={postColors[`${item["type"]}`]}>
                <TextContainer>
                    <TouchableOpacity
                        onPress={() => confirmDelete()}
                        style={{ alignSelf: "flex-end" }}
                    >
                        <Icon name="cross" size={24} color="black" />
                    </TouchableOpacity>
                    <Title>{item["title"]}</Title>
                    <Description>{item["description"]}</Description>
                </TextContainer>
                <ReactionsContainer>
                    <ReactionContainer>
                        <Icon3 name="arm-flex" size={24} color="yellow" />
                        <Text color="yellow" style={tw`pl-2`}>
                            {reactionCounts.Strong}
                        </Text>
                    </ReactionContainer>
                    <ReactionContainer>
                        <Icon3 name="brain" size={24} color="pink" />
                        <Text color="pink" style={tw`pl-2`}>
                            {reactionCounts.Brain}
                        </Text>
                    </ReactionContainer>
                    <ReactionContainer>
                        <Icon2 name="money" size={24} color="green" />
                        <Text color="green" style={tw`pl-2`}>
                            {reactionCounts.Money}
                        </Text>
                    </ReactionContainer>
                </ReactionsContainer>
            </Container>
            {item["comments"].length > 0 ? (
                <FlatList
                    data={item["comments"]}
                    renderItem={(item) => <Comment item={item} />}
                />
            ) : (
                <></>
            )}
        </>
    );
};

export default OwnPost;
