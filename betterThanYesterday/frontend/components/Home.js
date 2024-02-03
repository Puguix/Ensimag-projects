import React, { useEffect, useState } from "react";
import { View, FlatList, TouchableOpacity, Text, Alert } from "react-native";
import styled from "styled-components/native";
import tw from "twrnc";
import Header from "./Header";
import Post from "./Post";
import Footer from "./Footer";
import { API } from "../utils/ApiLink";
import { useAuth } from "../utils/AuthContext";

const Container = styled(View)`
    ${tw`flex-1 justify-center items-center bg-gray-900`}
`;
const Button = styled(TouchableOpacity)`
    ${tw`bg-gray-200 px-4 py-2 rounded`}
    margin-bottom: 6px;
`;

const ButtonText = styled(Text)`
    ${tw`text-pink-600 text-center`}
`;

const Error = styled(Text)`
    ${tw`font-bold mb-4 text-pink-300 w-2/3`}
    text-align: center
`;

const Home = ({ navigation }) => {
    const [posts, setPosts] = useState([]);
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

    useEffect(() => {
        const fetchPosts = async () => {
            console.log(
                "In Home\n fecth posts:" + username + " token:" + token
            );
            fetch(API + "/" + username + "/posts", {
                headers: { "x-access-token": token },
                method: "GET",
            })
                .then((res) => res.json())
                .then((res) => {
                    if (res["status"] === true) {
                        setPosts(res["data"]);
                    } else {
                        alert(res["message"]);
                    }
                })
                .catch((e) => alert(e.toString()));
        };

        fetchPosts();
    }, []);

    return (
        <View style={tw`flex-1`}>
            <Header navigation={navigation} />
            {posts.length > 0 ? (
                <FlatList
                    style={tw`bg-gray-900`}
                    data={posts}
                    keyExtractor={(item) => item.id.toString()}
                    renderItem={(item) => <Post item={item} />}
                />
            ) : (
                <></>
            )}
            <Container>
                <Error>
                    You've seen all your friends posts! Consider adding more
                    friends:
                </Error>
                <Button onPress={addFriend}>
                    <ButtonText>Add friends</ButtonText>
                </Button>
            </Container>

            <Footer navigation={navigation} />
        </View>
    );
};

export default Home;
