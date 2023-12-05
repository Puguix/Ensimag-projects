const status = require("http-status");
const tagModel = require("../models/tags.js");
const userModel = require("../models/users.js");
const has = require("has-keys");
const CodeError = require("../util/CodeError.js");
const bcrypt = require("bcrypt");
const jws = require("jws");
const user = require("./user.js");
require("mandatoryenv").load(["TOKENSECRET"]);
const { TOKENSECRET } = process.env;

async function verifyUser(req) {
    if (!req.headers || !req.headers.hasOwnProperty("x-access-token"))
        throw { code: 403, message: "Token missing" };
    // Code vérifiant la validité du token
    if (!jws.verify(req.headers["x-access-token"], "HS256", TOKENSECRET))
        throw { code: 403, message: "Token invalid" };
    // Le payload du token contient le login de l'utilisateur
    // On modifie l'objet requête pour mettre le login à disposition pour les middleware suivants
    username = jws.decode(req.headers["x-access-token"]).payload;
    if (!username == req.params.user)
        throw new CodeError("Invalid credentials", status.UNAUTHORIZED);
    const data = await userModel.findOne({
        where: { username },
        attributes: ["id"],
    });
    if (!data) throw new CodeError("User not found", status.UNAUTHORIZED);
    return data;
}

module.exports = {
    async getTags(req, res) {
        // #swagger.tags = ['Tags']
        // #swagger.summary = 'Get All tags'
        const user = await verifyUser(req);
        const data = await user.getTags();
        res.json({ status: true, message: "Returning tags", data });
    },
    async createTag(req, res) {
        // #swagger.tags = ['Tags']
        // #swagger.summary = 'New Tag'
        // #swagger.parameters['obj'] = { in: 'body', description:'Tag', schema: { $name: 'Backend'}}
        const user = await verifyUser(req);
        const { name } = req.body;
        await user.createTag({ name });
        res.status(201).json({ status: true, message: "Tag added" });
    },
    async getTag(req, res) {
        // #swagger.tags = ['Tags']
        // #swagger.summary = 'Get One tag'
        const user = await verifyUser(req);
        const id = req.params.tid;
        const tag = (await user.getTags({ where: { id } }))[0];
        if (!tag) throw new CodeError("Tag not found", status.NOT_FOUND);
        res.json({ status: true, message: "Returning tag: " + id, tag });
    },
    async updateTag(req, res) {
        // #swagger.tags = ['Tags']
        // #swagger.summary = 'Modify Tag'
        // #swagger.parameters['obj'] = { in: 'body', description:'Tag', schema: { $name: 'Backend'}}
        const user = await verifyUser(req);
        const id = req.params.tid;
        const { name } = req.body;
        const tag = (await user.getTags({ where: { id } }))[0];
        await tag.update({ name });
        res.json({ status: true, message: "Tag modified" });
    },
    async deleteTag(req, res) {
        // #swagger.tags = ['Tags']
        // #swagger.summary = 'Delete Tag'
        const user = await verifyUser(req);
        const id = req.params.tid;
        const tag = (await user.getTags({ where: { id } }))[0];
        await tag.destroy();
        res.json({ status: true, message: "Tag deleted" });
    },
};
