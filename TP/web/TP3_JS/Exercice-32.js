function miseEnPlace() {
    function jaunir() {
        document.getElementById("contents").style.backgroundColor = "yellow";
    }
    function rougir() {
        let titre = document.getElementsByTagName("h1")[0];
        if (titre.style.color === "red") {
            titre.style.color = "";
        } else {
            titre.style.color = "red";
        }
    }
    function italic() {
        let textes = document.getElementsByTagName("p");
        let i = 0;
        while (
            textes[i].style.fontStyle === "italic" &&
            i < textes.length - 1
        ) {
            i++;
        }
        textes[i].style.fontStyle = "italic";
    }

    let b1 = document.getElementById("b1");
    let b2 = document.getElementById("b2");
    let b3 = document.getElementById("b3");

    b1.addEventListener("click", jaunir, false);
    b2.addEventListener("click", rougir, false);
    b3.addEventListener("click", italic, false);
}

window.addEventListener("load", miseEnPlace, false);
