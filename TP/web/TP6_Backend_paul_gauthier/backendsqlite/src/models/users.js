const Sequelize = require("sequelize");
const db = require("./database.js");
const users = db.define(
    "users",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        username: {
            type: Sequelize.STRING(16),
            unique: true,
            validate: {
                is: /^[a-z\-'\s]{1,128}$/i,
            },
        },
    },
    { timestamps: false }
);
module.exports = users;
