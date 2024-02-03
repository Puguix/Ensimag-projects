// Fonction pour effectuer la mise en place initiale
function miseEnPlace() {
    // Sélectionner le corps du tableau dans le document HTML
    const tabBody = document.querySelector("tbody");

    // Parcourir toutes les lignes du tableau
    for (let i = 0; i < tabBody.children.length; i++) {
        // Appliquer la couleur de fond à la ligne en fonction de sa position (paire ou impaire)
        colorRow(tabBody.children[i], i % 2 === 0);

        // Appliquer la couleur de la note à la colonne correspondante
        colorNote(tabBody.children[i].children[5]);
    }
}

// Fonction pour colorer la ligne en fonction de certains critères
function colorRow(row, isEven) {
    // Vérifier si la ligne a la classe "ue"
    if (row.classList.contains("ue")) {
        // Si oui, définir la couleur de fond sur "lightblue"
        row.style.backgroundColor = "lightblue";
    } else if (isEven) {
        // Si la ligne est paire, définir la couleur de fond sur "gray"
        row.style.backgroundColor = "gray";
    }
}

// Fonction pour colorer la note en fonction de sa valeur
function colorNote(n) {
    // Convertir la valeur de la note en entier
    let value = parseInt(n.innerText);

    // Appliquer la couleur en fonction de l'intervalle de valeurs
    if (value < 8) {
        n.style.color = "red";
    } else if (value < 10) {
        n.style.color = "orange";
    } else if (value < 12) {
        n.style.color = "yellow";
    } else {
        n.style.color = "green";
    }
}

// Ajouter un écouteur d'événements pour déclencher la fonction miseEnPlace lorsque la page est entièrement chargée
window.addEventListener("load", miseEnPlace, false);
