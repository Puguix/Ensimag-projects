const express = require("express");
const router = express.Router();
const posts = require("../controllers/posts.js");

router.post("/:username/posts", posts.create);
router.get("/:username/posts", posts.getPosts);
router.post("/:username/:post/comment", posts.comment);
router.post("/:username/:post/react", posts.react);
router.delete("/:username/:post", posts.delete);

module.exports = router;
