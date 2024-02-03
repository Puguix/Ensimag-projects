// Fonction pour créer une liste déroulante à partir d'un objet
function liste(i) {
    // Fonction récursive interne pour traiter l'objet et créer la structure de la liste
    function liste_rec(obj) {
        // Créer les éléments de la liste (dl, dt, dd, ul)
        let dl = document.createElement("dl");
        let dt = document.createElement("dt");
        dt.innerText = obj["title"];
        let dd = document.createElement("dd");
        let ul = document.createElement("ul");

        // Parcourir les éléments de la liste
        obj["items"].forEach((ele) => {
            let li = document.createElement("li");
            // Vérifier le type de l'élément (chaîne de caractères ou objet)
            if (typeof ele === "string") {
                // Si c'est une chaîne de caractères, créer un nœud de texte
                li.appendChild(document.createTextNode(ele));
            } else {
                // Si c'est un objet, appeler récursivement la fonction pour créer un élément de liste imbriqué
                li.appendChild(liste_rec(ele));
            }
            ul.appendChild(li);
        });

        // Ajouter les éléments à la structure de la liste
        dd.appendChild(ul);
        dl.appendChild(dt);
        dl.appendChild(dd);
        return dl;
    }

    // Obtenir la définition de la liste en fonction de l'indice fourni
    const list = getDefinition(parseInt(i));

    // Afficher la liste générée dans la console à des fins de débogage
    console.log(list);

    // Sélectionner l'élément avec l'id "contents"
    let contents = document.getElementById("contents");

    // Vérifier s'il y a déjà des éléments enfants dans "contents" et les supprimer
    if (contents.children.length > 0) {
        contents.removeChild(contents.children[0]);
    }

    // Ajouter la liste générée à l'élément "contents"
    contents.appendChild(liste_rec(list));
}

// Fonction pour effectuer la mise en place des boutons radio et des événements associés
function miseEnPlace() {
    // Sélectionner tous les boutons radio avec le nom "list"
    let radioButtons = document.getElementsByName("list");

    // Parcourir les boutons radio
    for (i = 0; i < radioButtons.length; i++) {
        // Vérifier quel bouton radio est sélectionné et afficher la liste correspondante
        if (radioButtons[i].checked) {
            console.log(radioButtons[i].value);
            liste(radioButtons[i].value);
        }
    }

    // Ajouter des écouteurs d'événements pour les changements de sélection des boutons radio
    for (let i = 0; i < radioButtons.length; i++) {
        radioButtons[i].addEventListener("change", function () {
            // Vérifier si le bouton radio est sélectionné
            if (radioButtons[i].checked) {
                // Appeler la fonction liste avec la valeur du bouton radio sélectionné
                liste(radioButtons[i].value);
            }
        });
    }
}

// Ajouter un écouteur d'événements pour déclencher la fonction miseEnPlace lorsque la page est entièrement chargée
window.addEventListener("load", miseEnPlace, false);
