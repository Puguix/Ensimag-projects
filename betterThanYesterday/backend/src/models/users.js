const Sequelize = require("sequelize");
const db = require("./database.js");

const Follows = db.define("Follows", {});

const users = db.define(
    "users",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        username: {
            type: Sequelize.STRING(64),
            unique: true,
            validate: {
                is: /^[a-zA-Z0-9]{1,64}$/i,
            },
        },
        email: {
            type: Sequelize.STRING(128),
            unique: true,
            validate: {
                isEmail: true,
            },
        },
        passhash: {
            type: Sequelize.STRING(60),
            validate: {
                is: /^[0-9a-z\\/$.]{60}$/i,
            },
        },
        surname: {
            type: Sequelize.STRING(64),
            validate: {
                is: /^[a-zA-Z0-9]{1,64}$/i,
            },
        },
        isPublic: {
            type: Sequelize.BOOLEAN,
            default: false,
        },
    },
    { timestamps: false }
);

// Define the Following/Followers relationship
users.belongsToMany(users, {
    as: "followers",
    through: Follows,
    foreignKey: "userId",
});
users.belongsToMany(users, {
    as: "following",
    through: Follows,
    foreignKey: "followedId",
});

module.exports = users;
