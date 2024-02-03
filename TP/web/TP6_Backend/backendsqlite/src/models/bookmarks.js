const Sequelize = require("sequelize");
const db = require("./database.js");
const users = require("./users.js");
const tags = require("./tags.js");
const bookmarks = db.define(
    "bookmarks",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        title: {
            type: Sequelize.STRING(256),
        },
        link: {
            type: Sequelize.STRING(256),
        },
        description: {
            type: Sequelize.STRING(256),
        },
    },
    { timestamps: false }
);
bookmarks.belongsTo(users);
users.hasMany(bookmarks);

bookmarks.belongsToMany(tags, { through: "isTagged" });
tags.belongsToMany(bookmarks, { through: "isTagged" });

module.exports = bookmarks;
