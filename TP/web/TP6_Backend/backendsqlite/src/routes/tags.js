const express = require("express");
const router = express.Router();
const tags = require("../controllers/tags.js");

router.get("/bmt/:user/tags", tags.getTags);
router.post("/bmt/:user/tags", tags.createTag);
router.get("/bmt/:user/tags/:tid", tags.getTag);
router.put("/bmt/:user/tags/:tid", tags.updateTag);
router.delete("/bmt/:user/tags/:tid", tags.deleteTag);

module.exports = router;
