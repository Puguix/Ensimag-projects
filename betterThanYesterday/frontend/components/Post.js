import { React, useState } from "react";
import { View, Text, TouchableOpacity, FlatList, Alert } from "react-native";
import styled from "styled-components/native";
import tw from "twrnc";
import Comment from "./Comment";
import Icon from "react-native-vector-icons/MaterialCommunityIcons";
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

const Author = styled(Text)`
    ${tw`text-xl font-bold mb-4 text-black w-2/3`}
    text-align: left
`;

const Description = styled(Text)`
    ${tw`text-m font-bold mb-4 text-black w-2/3`}
    text-align: center
`;

const CommentaryContainer = styled(View)`
    ${tw`bg-gray-900`}
`;

const Commentary = styled(TouchableOpacity)`
    ${tw`my-2 mr-4`}
    alignSelf: flex-end
`;

const Post = ({ item }) => {
    const post = item["item"];

    const postColors = {
        Sport: "orange",
        Culture: "red",
        Travail: "cyan",
        Mental: "purple",
        Other: "blue",
    };

    const [isFlexColored, setFlexColor] = useState(false);
    const [isBrainColored, setBrainColor] = useState(false);
    const [isMoneyColored, setMoneyColor] = useState(false);

    const { username, token } = useAuth();

    const reactionCounts = {
        Strong: 0,
        Brain: 0,
        Money: 0,
    };
    post["reactions"].forEach((reaction) => {
        reactionCounts[reaction["reaction"]]++;
    });

    const sendReaction = async (reaction) => {
        await fetch(API + "/" + username + "/" + post["id"] + "/react", {
            headers: {
                "Content-Type": "application/x-www-form-urlencoded",
                "x-access-token": token,
            },
            method: "POST",
            body: "reaction=" + reaction,
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    switch (reaction) {
                        case "Strong":
                            isFlexColored
                                ? setFlexColor(false)
                                : setFlexColor(true);
                            break;
                        case "Brain":
                            isBrainColored
                                ? setBrainColor(false)
                                : setBrainColor(true);
                            break;
                        case "Money":
                            isMoneyColored
                                ? setMoneyColor(false)
                                : setMoneyColor(true);
                            break;
                    }
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    const sendComment = async (text) => {
        await fetch(API + "/" + username + "/" + post.id + "/comment", {
            headers: {
                "x-access-token": token,
                "Content-Type": "application/x-www-form-urlencoded",
            },
            method: "POST",
            body: "text=" + text,
        })
            .then((res) => res.json())
            .then((res) => {
                if (res["status"] === true) {
                    alert("Comment posted");
                } else {
                    alert(res["message"]);
                }
            })
            .catch((e) => alert(e.toString()));
    };

    const addComment = async () => {
        Alert.prompt(
            "Add comment",
            "What do you want to say to encorage your friend?",
            [
                {
                    text: "Post comment",
                    onPress: async (text) => {
                        await sendComment(text);
                    },
                },
                {
                    text: "Cancel",
                    style: "cancel",
                },
            ],
            "plain-text"
        );
    };

    return (
        <>
            <Container color={postColors[`${post["type"]}`]}>
                <Author>{post["user"]["surname"]}</Author>
                <TextContainer>
                    <Title>{post["title"]}</Title>
                    <Description>{post["description"]}</Description>
                </TextContainer>
                <ReactionsContainer>
                    <ReactionContainer>
                        <TouchableOpacity
                            onPress={() => sendReaction("Strong")}
                        >
                            <Icon
                                name="arm-flex"
                                size={24}
                                color={isFlexColored ? "yellow" : "black"}
                            />
                        </TouchableOpacity>
                        <Text
                            color={isFlexColored ? "yellow" : "black"}
                            style={tw`pl-2`}
                        >
                            {isFlexColored + reactionCounts.Strong}
                        </Text>
                    </ReactionContainer>
                    <ReactionContainer>
                        <TouchableOpacity onPress={() => sendReaction("Brain")}>
                            <Icon
                                name="brain"
                                size={24}
                                color={isBrainColored ? "pink" : "black"}
                            />
                        </TouchableOpacity>
                        <Text
                            color={isBrainColored ? "pink" : "black"}
                            style={tw`pl-2`}
                        >
                            {isBrainColored + reactionCounts.Brain}
                        </Text>
                    </ReactionContainer>
                    <ReactionContainer>
                        <TouchableOpacity onPress={() => sendReaction("Money")}>
                            <Icon2
                                name="money"
                                size={24}
                                color={isMoneyColored ? "green" : "black"}
                            />
                        </TouchableOpacity>
                        <Text
                            color={isMoneyColored ? "green" : "black"}
                            style={tw`pl-2`}
                        >
                            {isMoneyColored + reactionCounts.Money}
                        </Text>
                    </ReactionContainer>
                </ReactionsContainer>
            </Container>
            {post["comments"].length > 0 ? (
                <FlatList
                    data={post["comments"]}
                    renderItem={(item) => <Comment item={item} />}
                />
            ) : (
                <></>
            )}
            <CommentaryContainer>
                <Commentary onPress={addComment}>
                    <Icon2 name="comment" size={24} color="white" />
                </Commentary>
            </CommentaryContainer>
        </>
    );
};

export default Post;
