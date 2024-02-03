const status = require("http-status");
const userModel = require("../models/users.js");
const has = require("has-keys");
const CodeError = require("../util/CodeError.js");
const bcrypt = require("bcrypt");
const jws = require("jws");
require("mandatoryenv").load(["TOKENSECRET"]);
const { TOKENSECRET } = process.env;

module.exports = {
    async getUsers(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Get All users'
        const data = await userModel.findAll({
            attributes: ["id", "username"],
        });
        res.json({ status: true, message: "Returning users", data });
    },
    async newUser(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'New User'
        // #swagger.parameters['obj'] = { in: 'body', description:'Username', schema: { $username: 'John Doe'}}
        if (!has(req.body, ["username"]))
            throw new CodeError(
                "You must specify the username",
                status.BAD_REQUEST
            );
        const { username } = req.body;
        console.log(req.body);
        await userModel.create({
            username,
        });
        res.status(201).json({ status: true, message: "User added" });
    },
    async deleteUsers(req, res) {
        // #swagger.tags = ['Users']
        // #swagger.summary = 'Delete Users'
        await userModel.destroy({ where: {} });
        res.json({ status: true, message: "Users deleted" });
    },
    async createToken(req, res) {
        // #swagger.tags = ['Token']
        // #swagger.summary = 'Create Token'
        const username = req.params.user;
        const data = await userModel.findOne({ where: { username } });
        if (!data) throw new CodeError("User not found", status.NOT_FOUND);
        const signature = jws.sign({
            header: { alg: "HS256" },
            payload: username,
            secret: TOKENSECRET,
        });
        res.json({ status: true, message: "Token created: ", signature });
    },
    async getToken(req, res) {
        // #swagger.tags = ['Token']
        // #swagger.summary = 'Get Token'
        if (!req.headers || !req.headers.hasOwnProperty("x-access-token"))
            throw { code: 403, message: "Token missing" };
        // Code vérifiant la validité du token
        if (!jws.verify(req.headers["x-access-token"], "HS256", TOKENSECRET))
            throw { code: 403, message: "Token invalid" };
        // Le payload du token contient le login de l'utilisateur
        // On modifie l'objet requête pour mettre le login à disposition pour les middleware suivants
        const user = jws.decode(req.headers["x-access-token"]).payload;
        res.json({ status: true, message: "Login: ", user });
    },
};
