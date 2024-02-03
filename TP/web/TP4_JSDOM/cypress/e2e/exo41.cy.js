// Décrire le test pour l'exercice 41
describe("Test de l'exercice 41", () => {
    // Itération du test
    it("test", () => {
        // Visiter la page HTML de l'exercice 41
        cy.visit("http://127.0.0.1:5500/Exercice-41.html");

        // Ajouter un nouvel élément avec le texte "test1" et appuyer sur la touche "Entrée"
        cy.get("#newItem").type("test1").type("{enter}");

        // Vérifier que la liste lifo a une longueur de 1
        cy.get("#lifo li").should("have.length", 1);

        // Modifier le texte de l'élément en remplaçant le dernier caractère par "2" et appuyer sur la touche "Entrée"
        cy.get("#newItem").type("{backspace}").type("2").type("{enter}");

        // Vérifier que la liste lifo a maintenant une longueur de 2
        cy.get("#lifo li").should("have.length", 2);

        // Cliquer sur le bouton "pop"
        cy.get("input[name='pop']").click();

        // Vérifier que la liste lifo a une longueur de 1 après la suppression d'un élément
        cy.get("#lifo li").should("have.length", 1);

        // Cliquer sur le bouton "peek"
        cy.get("input[name='peek']").click();

        // Vérifier que la liste lifo a toujours une longueur de 1
        cy.get("#lifo li").should("have.length", 1);

        // Vérifier que le paragraphe dans l'élément avec l'id "peek-area" contient le texte "test2"
        cy.get("#peek-area p").should("have.text", "test2");

        // Cliquer à nouveau sur le bouton "pop"
        cy.get("input[name='pop']").click();

        // Vérifier que la liste lifo est maintenant vide
        cy.get("#lifo li").should("have.length", 0);
    });
});
