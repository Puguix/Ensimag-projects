const express = require("express");
const router = express.Router();
const bookmarks = require("../controllers/bookmarks.js");

router.get("/bmt/:user/bookmarks", bookmarks.getBookmarks);
router.post("/bmt/:user/bookmarks", bookmarks.createBookmark);
router.get("/bmt/:user/bookmarks/:bid", bookmarks.getBookmark);
router.put("/bmt/:user/bookmarks/:bid", bookmarks.updateBookmark);
router.delete("/bmt/:user/bookmarks/:bid", bookmarks.deleteBookmark);
router.get("/bmt/:user/tags/:tid/bookmarks", bookmarks.getTagBookmarks);

module.exports = router;
