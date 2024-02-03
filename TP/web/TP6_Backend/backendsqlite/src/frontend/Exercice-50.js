/* Base URL of the web-service for the current user and access token */
const backend = "http://localhost:3000"; // replace by the backend to use
const token =
    "eyJhbGciOiJIUzI1NiJ9.Z2F1dGhwYXU.iexSQOJzSBQbe4ip_ARtgm9U1qmWptI2nocs2qdyNk8"; //replace by your token : go to BACKEND/getjwsDeleg/caw to obtain it
const wsBase = `${backend}/bmt/gauthpau/`; // replace USER by your login used to obtain TOKEN

/* Shows the identity of the current user */
function setIdentity() {
    // get the span to modify
    let span = document.getElementsByClassName("identity")[0];
    // get the result and add it to the span
    fetch(backend + "/whoami", {
        headers: { "x-access-token": token },
        method: "GET",
    })
        .then((res) => res.json())
        .then((res) => (span.textContent = res["data"]))
        .catch((e) => console.log(e.toString()));
}

/* Sets the height of <div id="#contents"> to benefit from all the remaining place on the page */
function setContentHeight() {
    let availableHeight = window.innerHeight;
    availableHeight -= document.getElementById("contents").offsetTop;
    availableHeight -= 2 * document.querySelector("h1").offsetTop;
    availableHeight -= 4 * 1;
    document.getElementById("contents").style.height = availableHeight + "px";
}

/* Selects a new object type : either "bookmarks" or "tags" */
function selectObjectType(type) {
    // get the type clicked on
    const li = document.querySelector("." + type);
    if (!li.classList.contains("selected")) {
        // logic if the tag wasn't selected to modify the selected component
        if (type === "bookmarks") {
            document.querySelector(".bookmarks").classList.add("selected");
            document.querySelector(".tags").classList.remove("selected");
            listBookmarks();
            checkTags();
            document.querySelector("#add .tag").classList.remove("selected");
            document.querySelector("#add .bookmark").classList.add("selected");
        } else {
            document.querySelector(".bookmarks").classList.remove("selected");
            document.querySelector(".tags").classList.add("selected");
            listTags();
            document
                .querySelector("#add .bookmark")
                .classList.remove("selected");
            document.querySelector("#add .tag").classList.add("selected");
        }
    }
}

/* Loads the list of all bookmarks and displays them */
function listBookmarks() {
    // get and empty the items div
    let div = document.querySelector("#items");
    div.innerHTML = "";
    // fetch the items
    fetch(wsBase + "bookmarks", {
        headers: { "x-access-token": token },
        method: "GET",
    })
        .then((res) => res.json())
        .then((res) =>
            // for each bookmark, create the appropriate content and append it to the items div
            res["data"].forEach((bookmark) => {
                let d = document.createElement("div");
                d.classList.add("item");
                d.classList.add("bookmark");
                d.setAttribute("num", bookmark["id"]);

                let h2 = document.createElement("h2");
                h2.textContent = bookmark["title"];
                d.appendChild(h2);

                let a = document.createElement("a");
                a.setAttribute("href", bookmark["link"]);
                a.textContent = bookmark["link"];
                d.appendChild(a);

                let desc = document.createElement("div");
                desc.classList.add("description");
                desc.textContent = bookmark["description"];
                d.appendChild(desc);

                let ul = document.createElement("ul");
                ul.classList.add("tags");
                bookmark["tags"].forEach((tag) => {
                    let li = document.createElement("li");
                    li.textContent = tag["name"];
                    ul.appendChild(li);
                });
                d.appendChild(ul);

                div.appendChild(d);
            })
        )
        .catch((e) => console.log(e.toString()));
}

// generate the checkboxes for the tags
function checkTags() {
    // fetch the tags items to add bookmarks
    let ul = document.querySelector("#tagList");
    ul.innerHTML = "";
    fetch(wsBase + "tags", {
        headers: { "x-access-token": token },
        method: "GET",
    })
        .then((res) => res.json())
        .then((res) => {
            // for each tag, create the appropriate data and append it to the items div
            res["data"].forEach((tag) => {
                let li = document.createElement("li");
                let input = document.createElement("input");
                input.type = "checkbox";
                input.name = "tag";
                input.value = tag["name"];
                input.setAttribute("num", tag["id"]);

                let label = document.createElement("label");
                label.for = tag["name"];
                label.textContent = tag["name"];

                li.appendChild(input);
                li.appendChild(label);
                ul.appendChild(li);
            });
        })
        .catch((e) => console.log(e.toString()));
}

/* Adds a new Bookmark */
function addBookmark() {
    // get the bookmark information from the form
    let title = document.querySelector("#add input[name='title']").value;
    let link = document.querySelector("#add input[name='url']").value;
    let description = document.querySelector(
        "#add input[name='description']"
    ).value;
    let tags = [];
    document
        .querySelectorAll("#add input[name='tag']:checked")
        .forEach((checkbox) => {
            tags.push(checkbox.value);
        });
    console.log(tags);

    // fetch to create a bookmark
    fetch(wsBase + "bookmarks", {
        headers: {
            "x-access-token": token,
            "Content-Type": "application/x-www-form-urlencoded",
        },
        method: "POST",
        body:
            "data=" +
            JSON.stringify({
                title: title,
                link: link,
                description: description,
                tags: tags,
            }),
    })
        .then((res) => listBookmarks())
        .catch((e) => listBookmarks());
}

/* Handles the click on a Bookmark */
function clickBookmark(bookmark) {
    // escape if already selected
    if (bookmark.classList.contains("selected")) {
        return;
    }

    // get the selected item, check if not null
    let selected = document.querySelector("#items .selected");
    if (selected !== null) {
        // reverse modifications
        selected.classList.remove("selected");
        Array.from(selected.children).forEach(
            (child) => (child.style.display = "block")
        );
        for (let i = 0; i < 6; i++) selected.removeChild(selected.lastChild);
    }

    // add selected class and make things disappear
    bookmark.classList.add("selected");
    Array.from(bookmark.children).forEach(
        (child) => (child.style.display = "none")
    );

    // create input for title
    let inputTitle = document.createElement("input");
    inputTitle.type = "text";
    inputTitle.name = "title";
    inputTitle.value = bookmark.querySelector("h2").textContent;
    bookmark.appendChild(inputTitle);

    // create input for URL
    let inputURL = document.createElement("input");
    inputURL.type = "text";
    inputURL.name = "url";
    inputURL.value = bookmark.querySelector("a").getAttribute("href");
    bookmark.appendChild(inputURL);

    // create input for description
    let inputDescription = document.createElement("input");
    inputDescription.type = "text";
    inputDescription.name = "description";
    inputDescription.value = bookmark.querySelector(".description").textContent;
    bookmark.appendChild(inputDescription);

    // create checkboxes for tags
    let tagList = document.querySelector("#tagList").cloneNode(true);
    bookmark.appendChild(tagList);

    // create modify button
    let modifyBtn = document.createElement("button");
    modifyBtn.type = "button";
    modifyBtn.textContent = "Modify Bookmark";
    modifyBtn.addEventListener("click", function () {
        modifyBookmark(bookmark);
    });
    bookmark.appendChild(modifyBtn);

    // create remove button
    let removeBtn = document.createElement("button");
    removeBtn.type = "button";
    removeBtn.textContent = "Remove Bookmark";
    removeBtn.addEventListener("click", function () {
        removeBookmark(bookmark);
    });
    bookmark.appendChild(removeBtn);
}

/* Performs the modification of a Bookmark */
function modifyBookmark() {
    // get the selected bookmark information from the form
    let bookmark = document.querySelector("#items .selected");
    let title = bookmark.children[4].value;
    let link = bookmark.children[5].value;
    let description = bookmark.children[6].value;
    let tags = [];
    document
        .querySelectorAll(`#items .selected input[name='tag']:checked`)
        .forEach((checkbox) => {
            tags.push(checkbox.value);
        });

    console.log(title);
    console.log(link);
    console.log(description);
    console.log(tags);

    // fetch to update the bookmark
    fetch(wsBase + "bookmarks/" + bookmark.getAttribute("num"), {
        headers: {
            "x-access-token": token,
            "Content-Type": "application/x-www-form-urlencoded",
        },
        method: "PUT",
        body:
            "data=" +
            JSON.stringify({
                title: title,
                link: link,
                description: description,
                tags: tags,
            }),
    })
        .then((res) => listBookmarks())
        .catch((e) => listBookmarks());
}

/* Removes a Bookmark */
function removeBookmark() {
    // get the selected bookmark
    let bookmark = document.querySelector("#items .selected");
    // fetch to delete the bookmark
    fetch(wsBase + "bookmarks/" + bookmark.getAttribute("num"), {
        headers: {
            "x-access-token": token,
            "Content-Type": "application/x-www-form-urlencoded",
        },
        method: "DELETE",
    })
        .then((res) => listBookmarks())
        .catch((e) => listBookmarks());
}

/* Loads the list of all tags and displays them */
function listTags() {
    // get and empty the items div
    let div = document.querySelector("#items");
    div.innerHTML = "";
    // fetch the tags items
    fetch(wsBase + "tags", {
        headers: { "x-access-token": token },
        method: "GET",
    })
        .then((res) => res.json())
        .then((res) => {
            // for each tag, create the appropriate data and append it to the items div
            res["data"].forEach((tag) => {
                let d = document.createElement("div");
                d.classList.add("item");
                d.classList.add("tag");

                let h2 = document.createElement("h2");
                h2.textContent = tag["name"];
                d.setAttribute("num", tag["id"]);
                d.appendChild(h2);

                div.appendChild(d);
            });
        })
        .catch((e) => console.log(e.toString()));
}

/* Adds a new tag */
function addTag() {
    // get the name tag
    let nom = document.querySelector("div.selected > input:nth-child(1)").value;
    // return and alert if tag name is empty
    if (nom === "") {
        alert("Le nom du tag est vide");
        return;
    }
    // fetch to create a tag
    fetch(wsBase + "tags", {
        headers: {
            "x-access-token": token,
            "Content-Type": "application/x-www-form-urlencoded",
        },
        method: "POST",
        body: "data=" + JSON.stringify({ name: nom }),
    })
        .then((res) => listTags())
        .catch((e) => listTags());
}

/* Handles the click on a tag */
function clickTag(tag) {
    // escape if already selected
    if (tag.classList.contains("selected")) {
        return;
    }
    // get selected item, check if not null
    let selected = document.querySelector("#items .selected");
    if (selected != null) {
        // reverse modifications
        selected.classList.remove("selected");
        selected.firstChild.style.display = "block";
        for (let i = 0; i < 3; i++) selected.removeChild(selected.lastChild);
    }
    // add selected class, display H2
    tag.classList.add("selected");
    tag.firstChild.style.display = "none";
    // create input
    let input = document.createElement("input");
    input.type = "text";
    input.name = "newName";
    input.value = tag.firstChild.textContent;
    tag.appendChild(input);
    // create modify button
    let modifyBtn = document.createElement("button");
    modifyBtn.type = "button";
    modifyBtn.textContent = "Modify name";
    modifyBtn.addEventListener("click", modifyTag, false);
    tag.appendChild(modifyBtn);
    // create remove button
    let removeBtn = document.createElement("button");
    removeBtn.type = "button";
    removeBtn.textContent = "Remove tag";
    removeBtn.addEventListener("click", removeTag, false);
    tag.appendChild(removeBtn);
}

/* Performs the modification of a tag */
function modifyTag() {
    // get the selected tag and its name
    let tag = document.querySelector("#items .selected");
    let nom = tag.children[1].value;
    // fetch to update the tag
    fetch(wsBase + "tags/" + tag.getAttribute("num"), {
        headers: {
            "x-access-token": token,
            "Content-Type": "application/x-www-form-urlencoded",
        },
        method: "PUT",
        body: "data=" + JSON.stringify({ name: nom }),
    })
        .then((res) => listTags())
        .catch((e) => listTags());
}

/* Removes a tag */
function removeTag() {
    // get the selected tag
    let tag = document.querySelector("#items .selected");
    // fetch to delete the tag
    fetch(wsBase + "tags/" + tag.getAttribute("num"), {
        headers: {
            "x-access-token": token,
            "Content-Type": "application/x-www-form-urlencoded",
        },
        method: "DELETE",
    })
        .then((res) => listTags())
        .catch((e) => listTags());
}

/* On document loading */
function miseEnPlace() {
    /* Give access token for future ajax requests */
    // Put the name of the current user into <h1>
    setIdentity();
    // Adapt the height of <div id="contents"> to the navigator window
    setContentHeight();
    window.addEventListener("resize", setContentHeight);
    // Listen to the clicks on menu items
    for (let element of document.querySelectorAll("#menu li")) {
        element.addEventListener(
            "click",
            function () {
                const isTags = this.classList.contains("tags");
                selectObjectType(isTags ? "tags" : "bookmarks");
            },
            false
        );
    }
    // Initialize the object type to "tags"
    selectObjectType("tags");
    // Listen to clicks on the "add tag" button

    document.getElementById("addTag").addEventListener("click", addTag, false);
    document
        .getElementById("addBookmark")
        .addEventListener("click", addBookmark, false);
    document.getElementById("items").addEventListener(
        "click",
        (e) => {
            // Listen to clicks on the tag items
            const tag = e.target.closest(".tag.item");
            if (tag !== null) {
                clickTag(tag);
                return;
            }
            // Questions 10 & 12 - Listen to clicks on bookmark items
            const bookmark = e.target.closest(".bookmark.item");
            if (bookmark !== null) {
                clickBookmark(bookmark);
            }
        },
        false
    );
}
window.addEventListener("load", miseEnPlace, false);
