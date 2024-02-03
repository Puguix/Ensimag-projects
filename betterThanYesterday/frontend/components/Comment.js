import React from "react";
import { View, Text } from "react-native";
import styled from "styled-components/native";
import tw from "twrnc";

const Container = styled(View)`
    ${tw`flex-row p-2 bg-gray-900`}
`;

const Author = styled(Text)`
    ${tw`font-bold text-gray-300`}
`;

const Description = styled(Text)`
    ${tw`text-gray-300`}
`;

const Comment = ({ item }) => {
    const comment = item.item;

    return (
        <Container>
            <Author>{comment.user.surname}: </Author>
            <Description>{comment.text}</Description>
        </Container>
    );
};

export default Comment;
