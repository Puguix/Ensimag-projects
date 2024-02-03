const status = require("http-status");
const userModel = require("../models/users.js");
const commentModel = require("../models/comments.js");
const reactionModel = require("../models/reactions.js");
const has = require("has-keys");
const CodeError = require("../util/CodeError.js");
const bcrypt = require("bcrypt");
const jws = require("jws");
require("mandatoryenv").load(["TOKENSECRET"]);
const { TOKENSECRET } = process.env;
const SALT = 2;

function validPassword(password) {
    return /^(?=.*[\d])(?=.*[A-Z])(?=.*[a-z])(?=.*[!@#$%^&*])[\w!@#$%^&*]{8,}$/.test(
        password
    );
}

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
    async login(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Verify credentials of user using username and password and return token'
        // #swagger.parameters['obj'] = { in: 'body', schema: { $username: 'Ensimag', $password: '12345'}}
        if (!has(req.body, ["username", "password"]))
            throw new CodeError(
                "You must specify the username and password",
                status.BAD_REQUEST
            );
        const { username, password } = req.body;
        const user = await userModel.findOne({ where: { username } });
        if (user) {
            if (await bcrypt.compare(password, user.passhash)) {
                const token = jws.sign({
                    header: { alg: "HS256" },
                    payload: user.username,
                    secret: TOKENSECRET,
                });
                res.json({ status: true, message: "Login/Password ok", token });
                return;
            }
        }
        res.status(status.FORBIDDEN).json({
            status: false,
            message: "Wrong username/password",
        });
    },
    async signUp(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'New User'
        // #swagger.parameters['obj'] = { in: 'body', description:'Username and email', schema: { $username: 'Ensimag', $email: 'ensimag@imag.com', $password: '1m02P@SsF0rt!', $surname: 'Ensimag <3'}}
        if (!has(req.body, ["username", "email", "password"]))
            throw new CodeError(
                "You must specify the username, email and password",
                status.BAD_REQUEST
            );
        const { username, email, password, surname } = req.body;
        if (!validPassword(password))
            throw new CodeError("Weak password!", status.BAD_REQUEST);
        await userModel.create({
            username,
            email,
            passhash: await bcrypt.hash(password, SALT),
            surname,
        });
        const token = jws.sign({
            header: { alg: "HS256" },
            payload: username,
            secret: TOKENSECRET,
        });
        res.json({ status: true, message: "Account created", token });
    },
    async updateUser(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Update User'
        // #swagger.parameters['obj'] = { in: 'body', schema: {$password: '1m02P@SsF0rt!', $surname: 'Ensimag <3'}}
        const user = await verifyUser(req);
        if (!has(req.body, ["surname", "password"]))
            throw new CodeError(
                "You must specify the surname and password",
                status.BAD_REQUEST
            );
        const { password, surname } = req.body;
        await userModel.update(
            { passhash: await bcrypt.hash(password, SALT), surname },
            { where: { id: user.id } }
        );
        res.status(201).json({ status: true, message: "User updated" });
    },
    async getFollowers(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Get All followers'
        const user = await verifyUser(req);
        const data = await user.getFollowers({ attributes: ["id"] });
        res.json({ status: true, message: "Returning followers", data });
    },
    async getFollowing(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Get all user follows'
        const user = await verifyUser(req);
        const data = await user.getFollowing({ attributes: ["id"] });
        res.json({ status: true, message: "Returning follows", data });
    },
    async deleteUser(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Delete User'
        const user = await verifyUser(req);
        await userModel.destroy({ where: { id: user.id } });
        res.json({ status: true, message: "User deleted" });
    },
    async getUser(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'get a specific User'
        const user = await verifyUser(req);
        const follow = await user.getFollowing({
            where: { id: req.params.id },
        });
        if (!follow)
            throw new CodeError(
                "The user does not exist or you can't see the account",
                status.BAD_REQUEST
            );
        res.json({ status: true, message: "Returning user", follow });
    },
    async updateVisibility(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Update user account visibility'
        // #swagger.parameters['obj'] = { in: 'body', schema: { $isPublic: 'true'}}
        const user = await verifyUser(req);
        if (!has(req.body, ["isPublic"]))
            throw new CodeError(
                "You must specify the visibility",
                status.BAD_REQUEST
            );
        const { isPublic } = req.body;
        await userModel.update({ isPublic }, { where: { id: user.id } });
        res.status(201).json({
            status: true,
            message: "Account visibility updated",
        });
    },
    async follow(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'The user follows someone'
        const user = await verifyUser(req);
        const follow = await userModel.findOne({
            where: { surname: req.params.surname },
        });

        if (!follow) {
            throw new Error("The surname does not exist");
        }
        await user.addFollowing(follow);
        res.status(201).json({
            status: true,
            message: "Account followed",
        });
    },
    async getUserInfo(req, res) {
        // #swagger.tags = ['Users', 'Posts']
        // #swagger.summary = 'Get the user info and posts'
        const userId = await verifyUser(req);
        const user = await userModel.findOne({ where: { id: userId.id } });
        const posts = await userId.getPosts({
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
        res.json({
            status: true,
            message: "User info: ",
            user,
            posts,
        });
    },
};
