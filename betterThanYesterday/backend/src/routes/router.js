const router = require("express").Router();
router.use(require("./posts"));
router.use(require("./user"));
module.exports = router;
