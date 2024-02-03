function miseEnPlace() {
    let body = document.querySelector("body");

    var list = document.createElement("ul");

    let data = ["One", "Two", "Three"];
    for (i = 0; i < data.length; ++i) {
        let li = document.createElement("li");
        li.innerText = data[i];
        list.appendChild(li);
    }

    body.appendChild(list);
}

window.addEventListener("load", miseEnPlace, false);
