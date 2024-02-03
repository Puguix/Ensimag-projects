const Sequelize = require("sequelize");
const db = require("./database.js");
const users = require("./users.js");

const posts = db.define(
    "posts",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        title: {
            type: Sequelize.STRING(255),
            allowNull: false,
        },
        type: {
            type: Sequelize.ENUM([
                "Sport",
                "Culture",
                "Travail",
                "Mental",
                "Other",
            ]),
            allowNull: false,
        },
        description: {
            type: Sequelize.STRING(2047),
        },
    },
    { timestamps: false }
);

users.hasMany(posts);
posts.belongsTo(users);

module.exports = posts;
