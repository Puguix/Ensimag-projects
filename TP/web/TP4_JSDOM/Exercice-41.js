// Fonction pour effectuer la mise en place des boutons et des événements associés
function miseEnPlace() {
    // Sélectionner les boutons push, pop et peek dans le formulaire
    const pushButton = document.querySelector("input[name='push']");
    const popButton = document.querySelector("input[name='pop']");
    const peekButton = document.querySelector("input[name='peek']");

    // Ajouter des écouteurs d'événements pour les boutons
    pushButton.addEventListener("click", lifo_push, false);
    popButton.addEventListener("click", lifo_pop, false);
    peekButton.addEventListener("click", lifo_peek, false);

    // Ajouter un écouteur d'événements pour le formulaire (empêche le rechargement de la page lors de la soumission)
    document.querySelector("form").addEventListener(
        "submit",
        function (e) {
            e.preventDefault();
            lifo_push();
        },
        false
    );
}

// Fonction pour ajouter un élément à la pile (lifo)
function lifo_push() {
    // Sélectionner l'élément d'entrée
    const item = document.getElementById("newItem");

    // Créer un nouvel élément de liste avec le texte de l'élément d'entrée
    let li = document.createElement("li");
    li.innerText = item.value;

    // Sélectionner la pile (ul) et y ajouter le nouvel élément
    let ul = document.getElementById("lifo");
    ul.appendChild(li);
}

// Fonction pour retirer un élément de la pile (lifo)
function lifo_pop() {
    // Sélectionner la pile (ul)
    let ul = document.getElementById("lifo");

    // Vérifier s'il y a des éléments dans la pile
    if (ul.childElementCount > 0) {
        // Retirer le premier élément de la pile
        ul.removeChild(ul.children[0]);
    } else {
        // Afficher une alerte s'il n'y a rien à retirer
        alert("Il n'y rien à enlever");
    }
}

// Fonction pour afficher le premier élément de la pile (lifo) sans le retirer
function lifo_peek() {
    // Sélectionner la pile (ul)
    const ul = document.getElementById("lifo");

    // Vérifier s'il y a des éléments dans la pile
    if (ul.childElementCount > 0) {
        // Sélectionner la zone de texte (peek-area) et créer un paragraphe avec le texte du premier élément
        let texteArea = document.getElementById("peek-area");
        let p = document.createElement("p");
        let text = document.createTextNode(ul.children[0].firstChild.data);
        p.appendChild(text);

        // Remplacer le contenu de la zone de texte par le nouveau paragraphe
        texteArea.replaceChildren(p);
    } else {
        // Afficher une alerte s'il n'y a rien à afficher
        alert("Il n'y a rien à afficher");
    }
}

// Ajouter un écouteur d'événements pour déclencher la fonction miseEnPlace lorsque la page est entièrement chargée
window.addEventListener("load", miseEnPlace, false);
