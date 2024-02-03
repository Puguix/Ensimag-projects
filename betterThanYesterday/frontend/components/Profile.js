import { React, useState, useEffect } from "react";
import { View, Text, TouchableOpacity, FlatList } from "react-native";
import styled from "styled-components/native";
import tw from "twrnc";
import Icon from "react-native-vector-icons/FontAwesome";
import OwnPost from "./OwnPost";
import { useAuth } from "../utils/AuthContext";
import { API } from "../utils/ApiLink";
import Header from "./Header";
import Footer from "./Footer";

const Container = styled(View)`
    ${tw`items-center bg-gray-900 py-8 px-4`}
`;

const Title = styled(Text)`
    ${tw`text-4xl font-bold mb-4 text-pink-300 w-2/3`}
    text-align: center
`;

const SubTitle = styled(Text)`
    ${tw`text-xl font-bold mb-4 text-pink-300 w-2/3 pt-4`}
    text-align: center
`;

const Info = styled(Text)`
    ${tw`mb-4 text-gray-500 w-2/3`}
    text-align: center
`;

const Button = styled(TouchableOpacity)`
    ${tw`bg-pink-300 px-4 py-2 rounded`}
    margin-bottom: 6px;
`;

const ButtonText = styled(Text)`
    ${tw`text-gray-900 text-center`}
`;

const Profile = ({ navigation }) => {
    const { username, token } = useAuth();

    const [user, setUser] = useState([]);
    const [posts, setPosts] = useState([]);
    const [follows, setFollows] = useState([]);
    const [followers, setFollowers] = useState([]);

    const navigateToChangeProfile = () => {
        navigation.navigate("ChangeProfile");
    };
    const navigateToCreate = () => {
        navigation.navigate("Create");
    };

    useEffect(() => {
        const fetchUser = async () => {
            fetch(API + "/" + username, {
                headers: { "x-access-token": token },
                method: "GET",
            })
                .then((res) => res.json())
                .then((res) => {
                    setPosts(res["posts"]);
                    setUser(res["user"]);
                })
                .catch((e) => alert(e.toString()));
        };
        const fetchFollows = async () => {
            fetch(API + "/" + username + "/following", {
                headers: { "x-access-token": token },
                method: "GET",
            })
                .then((res) => res.json())
                .then((res) => {
                    setFollows(res["data"]);
                })
                .catch((e) => alert(e.toString()));
        };
        const fetchFollowers = async () => {
            fetch(API + "/" + username + "/followers", {
                headers: { "x-access-token": token },
                method: "GET",
            })
                .then((res) => res.json())
                .then((res) => {
                    setFollowers(res["data"]);
                })
                .catch((e) => alert(e.toString()));
        };

        fetchUser();
        fetchFollowers();
        fetchFollows();
    }, []);

    return (
        <>
            <Header navigation={navigation} />
            <Container>
                <TouchableOpacity
                    onPress={navigateToChangeProfile}
                    style={{ alignSelf: "flex-end" }}
                >
                    <Icon
                        name="cog"
                        size={24}
                        style={tw`ml-auto`}
                        color={"white"}
                    />
                </TouchableOpacity>
                <Title>{user["username"]}</Title>
                <Info>
                    {followers.length} Followers • {follows.length} Follows
                </Info>
                <SubTitle>Your own posts:</SubTitle>
            </Container>
            <FlatList
                style={tw`bg-gray-900`}
                data={posts}
                keyExtractor={(item) => item.id.toString()}
                renderItem={({ item }) => <OwnPost item={item} />}
            />
            {posts.length === 0 ? (
                <Container>
                    <SubTitle>
                        It seems like you have not posted yet...
                    </SubTitle>
                    <Button onPress={navigateToCreate}>
                        <ButtonText>Make my first post!</ButtonText>
                    </Button>
                </Container>
            ) : (
                <></>
            )}
            <Footer navigation={navigation} />
        </>
    );
};

export default Profile;
