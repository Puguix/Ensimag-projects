const Sequelize = require("sequelize");
const db = require("./database.js");
const users = require("./users.js");
const posts = require("./posts.js");

const comments = db.define(
    "comments",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        text: {
            type: Sequelize.STRING(2047),
            allowNull: false,
        },
    },
    { timestamps: false }
);

comments.belongsTo(posts);
comments.belongsTo(users);
users.hasMany(comments);
posts.hasMany(comments);

module.exports = comments;
