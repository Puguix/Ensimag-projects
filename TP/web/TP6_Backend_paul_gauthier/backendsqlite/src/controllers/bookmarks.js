const status = require("http-status");
const tagModel = require("../models/tags.js");
const bookmarkModel = require("../models/bookmarks.js");
const userModel = require("../models/users.js");
const has = require("has-keys");
const CodeError = require("../util/CodeError.js");
const bcrypt = require("bcrypt");
const jws = require("jws");
const user = require("./user.js");
const tags = require("./tags.js");
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
    async getBookmarks(req, res) {
        // #swagger.tags = ['Bookmarks']
        // #swagger.summary = 'Get All bookmarks'
        const user = await verifyUser(req);
        const bookmarks = await user.getBookmarks();
        res.json({ status: true, message: "Returning bookmarks", bookmarks });
    },
    async createBookmark(req, res) {
        // #swagger.tags = ['Bookmarks']
        // #swagger.summary = 'New Bookmark'
        // #swagger.parameters['obj'] = { in: 'body', description:'Bookmark', schema: { $title: 'Node', $link: 'www.node.html', $description: 'Node doc', $tags: [tid1, tid2, ...]}}
        const user = await verifyUser(req);
        const { title, link, description, tags } = req.body;
        let bookmark = await user.createBookmark({ title, link, description });
        let tagIds = [];
        if (tags) {
            tagIds = await tagModel.findAll({ where: { id: tags } });
        }
        await bookmark.addTags(tagIds);
        res.status(201).json({ status: true, message: "Bookmark added" });
    },
    async getBookmark(req, res) {
        // #swagger.tags = ['Bookmarks']
        // #swagger.summary = 'Get One bookmark'
        const user = await verifyUser(req);
        const id = req.params.bid;
        const bookmark = (await user.getBookmarks({ where: { id } }))[0];
        if (!bookmark)
            throw new CodeError("Bookmark not found", status.NOT_FOUND);
        res.json({
            status: true,
            message: "Returning bookmark: " + id,
            bookmark,
        });
    },
    async updateBookmark(req, res) {
        // #swagger.tags = ['Bookmarks']
        // #swagger.summary = 'Modify Bookmark'
        // #swagger.parameters['obj'] = { in: 'body', description:'Bookmark', schema: { $title: 'Node', $link: 'www.node.html', $description: 'Node doc', $tags: [tid1, tid2, ...]}}
        const user = await verifyUser(req);
        const id = req.params.bid;
        const { title, link, description, tags } = req.body;
        const bookmark = (await user.getBookmarks({ where: { id } }))[0];
        console.log(title, link, description);
        await bookmark.update({ title, link, description });
        let tagIds = [];
        if (tags) {
            tagIds = await tagModel.findAll({ where: { id: tags } });
        }
        await bookmark.setTags(tagIds);
        res.json({ status: true, message: "Bookmark modified" });
    },
    async deleteBookmark(req, res) {
        // #swagger.tags = ['Bookmarks']
        // #swagger.summary = 'Delete Bookmark'
        const user = await verifyUser(req);
        const id = req.params.bid;
        const bookmark = (await user.getBookmarks({ where: { id } }))[0];
        await bookmark.destroy();
        res.json({ status: true, message: "Bookmark deleted" });
    },
    async getTagBookmarks(req, res) {
        // #swagger.tags = ['Bookmarks', 'Tags]
        // #swagger.summary = 'Get tag associated bookmarks'
        const user = await verifyUser(req);
        const id = req.params.tid;
        const tag = (await user.getTags({ where: { id } }))[0];
        const bookmarks = await tag.getBookmarks({});
        res.json({
            status: true,
            message: "Returning tag bookmarks",
            bookmarks,
        });
    },
};
