function miseEnPlace() {
    function initialize() {
        document.getElementById("ltheme").value = "theme1";
        document.getElementById("showMenu").checked = false;
        switchMenu();
        switchTheme();
    }
    function switchMenu() {
        let menu = document.getElementById("menu");
        if (menu.style.display === "none") {
            menu.style.display = "block";
        } else {
            menu.style.display = "none";
        }
    }
    function switchTheme() {
        let body = document.querySelector("body");
        body.className = bTheme.value;
        if (bTheme.value === "theme1") {
            document.getElementById("showMenu").style.display = "none";
        } else {
            document.getElementById("showMenu").style.display = "inline";
        }
    }

    const bMenu = document.getElementById("showMenu");
    const bTheme = document.getElementById("ltheme");

    initialize();

    bMenu.addEventListener("change", switchMenu, false);
    bTheme.addEventListener("change", switchTheme, false);
}

window.addEventListener("load", miseEnPlace, false);
