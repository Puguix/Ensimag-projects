const Sequelize = require("sequelize");
const db = require("./database.js");
const users = require("./users.js");
const posts = require("./posts.js");

const reactions = db.define(
    "reactions",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        reaction: {
            type: Sequelize.ENUM(["Strong", "Brain", "Money"]),
            allowNull: false,
        },
    },
    { timestamps: false }
);

reactions.belongsTo(posts);
reactions.belongsTo(users);
users.hasMany(reactions);
posts.hasMany(reactions);

module.exports = reactions;
