const status = require("http-status");
const userModel = require("../models/users.js");
const postModel = require("../models/posts.js");
const commentModel = require("../models/comments.js");
const reactionModel = require("../models/reactions.js");
const has = require("has-keys");
const CodeError = require("../util/CodeError.js");
const bcrypt = require("bcrypt");
const jws = require("jws");
require("mandatoryenv").load(["TOKENSECRET"]);
const { TOKENSECRET, SALT } = process.env;

async function verifyUser(req) {
    if (!req.headers || !req.headers.hasOwnProperty("x-access-token"))
        throw { code: 403, message: "Token missing" };
    // Code vérifiant la validité du token
    if (!jws.verify(req.headers["x-access-token"], "HS256", TOKENSECRET))
        throw { code: 403, message: "Token invalid" };
    // Le payload du token contient le login de l'utilisateur
    // On modifie l'objet requête pour mettre le login à disposition pour les middleware suivants
    username = jws.decode(req.headers["x-access-token"]).payload;
    if (!username == req.params.username)
        throw new CodeError("Invalid credentials", status.UNAUTHORIZED);
    const data = await userModel.findOne({
        where: { username },
        attributes: ["id"],
    });
    if (!data) throw new CodeError("User not found", status.UNAUTHORIZED);
    return data;
}

module.exports = {
    async create(req, res) {
        // #swagger.tags = ['Posts']
        // #swagger.summary = 'Create a post'
        // #swagger.parameters['obj'] = { in: 'body', schema: { $title: 'Rando', $type: 'Sport', $description: "Randonnée bastille"}}
        const user = await verifyUser(req);
        await user.createPost({
            title: req.body.title,
            type: req.body.type,
            description: req.body.description,
        });
        res.json({
            status: false,
            message: "Post created",
        });
    },
    async getPosts(req, res) {
        // #swagger.tags = ['Posts']
        // #swagger.summary = 'Get all the posts of followed users'
        const user = await verifyUser(req);
        const followed = await user.getFollowing({ attributes: ["id"] });
        const followedUserIds = followed.map((user) => user.id);
        const data = await postModel.findAll({
            where: {
                userId: followedUserIds,
            },
            include: [
                { model: userModel, attributes: ["surname"] },
                {
                    model: commentModel,
                    attributes: ["text"], // Specify the attributes you want to retrieve for comments
                    include: [
                        {
                            model: userModel,
                            attributes: ["surname"],
                        },
                    ],
                },
                {
                    model: reactionModel,
                    attributes: ["reaction"], // Specify the attributes you want to retrieve for reactions
                },
            ],
        });
        console.log(data);
        res.json({ status: true, message: "Returning followed posts", data });
    },
    async comment(req, res) {
        // #swagger.tags = ['Posts', 'Comments']
        // #swagger.summary = 'Comment on a post'
        // #swagger.parameters['obj'] = { in: 'body', schema: { $text: 'wow'}}
        const user = await verifyUser(req);
        const post = await postModel.findByPk(req.params.post);
        await commentModel.create({
            userId: user.id,
            postId: post.id,
            text: req.body.text,
        });
        res.json({ status: true, message: "Comment added" });
    },
    async react(req, res) {
        // #swagger.tags = ['Posts', 'Reactions']
        // #swagger.summary = 'React or unreact on a post'
        // #swagger.parameters['obj'] = { in: 'body', schema: { $reaction: "Strong"}}
        const user = await verifyUser(req);
        const post = await postModel.findByPk(req.params.post);
        const reaction = await reactionModel.findOne({
            where: {
                userId: user.id,
                postId: post.id,
                reaction: req.body.reaction,
            },
        });
        if (!reaction) {
            await reactionModel.create({
                userId: user.id,
                postId: post.id,
                reaction: req.body.reaction,
            });
            res.json({ status: true, message: "Reaction added" });
        } else {
            reaction.destroy();
            res.json({ status: true, message: "Reaction deleted" });
        }
    },
    async delete(req, res) {
        // #swagger.tags = ['Posts']
        // #swagger.summary = 'Delete a post'
        const user = await verifyUser(req);
        const post = await postModel.findOne({
            where: { id: req.params.post, userId: user.id },
        });

        if (!post) {
            // Post not found or does not belong to the user
            throw new Error("Post not found or unauthorized");
        }

        // If the post belongs to the user, delete it
        await post.destroy();
        res.json({ status: true, message: "Post deleted" });
    },
};
