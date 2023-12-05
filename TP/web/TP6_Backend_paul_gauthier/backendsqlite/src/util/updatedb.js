const userModel = require("../models/users.js");
const tagModel = require("../models/tags.js");
const bookmarkModel = require("../models/bookmarks.js");
const bcrypt = require("bcrypt");
// Ajouter ici les nouveaux require des nouveaux modèles

// eslint-disable-next-line no-unexpected-multiline
(async () => {
    // Regénère la base de données
    await require("../models/database.js").sync({ force: true });
    console.log("Base de données créée.");
    // Initialise la base avec quelques données
    let user = await userModel.create({
        username: "gauthpau",
    });
    let tag = await user.createTag({ name: "Backend" });
    let bookmark = await user.createBookmark({
        title: "Node",
        link: "www.node.html",
        description: "Node documentation",
    });
    await bookmark.addTag(tag);
})();
