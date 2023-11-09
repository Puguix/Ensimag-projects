import java.time.LocalDate;

public class Demo {
    public static void main(String[] args) {
        Utilisateur emma = new Utilisateur("Carenna", "Emma", LocalDate.of(2001, 01, 02), "emma.carenna@gmail.com",
                "V1veL3nsimag!");
        Transaction virement = new Transaction(emma.comptes.get("COURANT"), Credit.getInstance(), 1000);
        Transaction course = new Transaction(emma.comptes.get("COURANT"), Debit.getInstance(), 8);
        new Compte(emma, TypeCompte.LIVRETA, 20);
        CategorieTransaction Alimentaire = new CategorieTransaction("Alimentaire", emma);
        CategorieTransaction Salaire = new CategorieTransaction("Salaire", emma);
        Salaire.ajouterTransaction(virement);
        Alimentaire.ajouterTransaction(course);
        Emprunt emprunt = new Emprunt(emma.comptes.get("COURANT"), 200, 0.0, LocalDate.of(2024, 04, 18));
        System.out.println(emma);
    }
}
