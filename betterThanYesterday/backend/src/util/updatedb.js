const userModel = require("../models/users.js");
const postModel = require("../models/posts.js");
const reactionModel = require("../models/reactions.js");
const commentsModel = require("../models/comments.js");
const bcrypt = require("bcrypt");
require("mandatoryenv").load(["TOKENSECRET"]);
const { SALT } = process.env;

(async () => {
    // Regénère la base de données
    await require("../models/database.js").sync({ force: true });
    console.log("Base de données créée.");
    // Initialise la base avec quelques données
    const passhash = await bcrypt.hash("123456", 2);
    let paul = await userModel.create({
        username: "Paul",
        email: "paul.gauthier@outlook.fr",
        passhash,
        surname: "Polo",
    });
    let marie = await userModel.create({
        username: "Marie",
        email: "marie.wagner@outlook.fr",
        passhash,
        surname: "Marie",
    });
    let nils = await userModel.create({
        username: "Nils",
        email: "nils.depuille@outlook.fr",
        passhash,
        surname: "Nils",
    });
    let guilhem = await userModel.create({
        username: "Guilhem",
        email: "guilhem.stevant@outlook.fr",
        passhash,
        surname: "Guigui",
    });
    await paul.addFollowing(nils);
    await paul.addFollowing(guilhem);
    await paul.addFollowing(marie);
    await guilhem.addFollowing(nils);
    let post = await nils.createPost({
        title: "Montée Bastille",
        type: "Sport",
        description: "Ptite montée de la Bastille en 1h!",
    });
    await nils.createPost({
        title: "Stage",
        type: "Travail",
        description:
            "J'ai enfin obtenu un stage! Je serai à la société général en tant qu'analyste risque à partir d'avril!",
    });
    await guilhem.createPost({
        title: "Sortie VTT",
        type: "Sport",
        description: "Entrainement dans le vercors: 25km en 2h =)",
    });
    await nils.createPost({
        title: "Lecture terminée",
        type: "Culture",
        description:
            "J'ai fini de lire 'The psychology of money' de Morgan Housel. Je suis désormais prêt pour investir!",
    });
    await marie.createPost({
        title: "Mois de yoga",
        type: "Mental",
        description:
            "Depuis un mois j'ai fait une séance d'une heure de yoga tous les jours. J'en ai ressentie les bein faits dès la semaine 1! Je recommande à tout le monde d'essayer",
    });
    await nils.addFollowing(marie);
    await reactionModel.create({
        userId: guilhem.id,
        postId: post.id,
        reaction: "Strong",
    });
    await commentsModel.create({
        userId: guilhem.id,
        postId: post.id,
        text: "Machine de guerre ;p",
    });
    console.log("Base de données à jour");
})();
