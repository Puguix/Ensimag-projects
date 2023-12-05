const express = require("express");
const router = express.Router();
const user = require("../controllers/user.js");

router.get("/users", user.getUsers);
router.post("/users", user.newUser);
router.delete("/users", user.deleteUsers);

router.get("/getjwtDeleg/:user", user.createToken);
router.get("/whoami", user.getToken);

module.exports = router;
