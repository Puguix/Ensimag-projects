const express = require("express");
const router = express.Router();
const user = require("../controllers/user.js");

router.post("/login", user.login);
router.post("/signup", user.signUp);
router.put("/:username", user.updateUser);
router.get("/:username/followers", user.getFollowers);
router.get("/:username/following", user.getFollowing);
router.delete("/:username", user.deleteUser);
router.get("/:username/:id", user.getUser);
router.put("/:username/:visibility", user.updateVisibility);
router.post("/:username/:surname", user.follow);
router.get("/:username", user.getUserInfo);

module.exports = router;
