const Sequelize = require("sequelize");
const db = require("./database.js");
const users = require("./users.js");
const tags = db.define(
    "tags",
    {
        id: {
            primaryKey: true,
            type: Sequelize.INTEGER,
            autoIncrement: true,
        },
        name: {
            type: Sequelize.STRING(256),
        },
    },
    { timestamps: false }
);
tags.belongsTo(users);
users.hasMany(tags);

module.exports = tags;
