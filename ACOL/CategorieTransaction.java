import java.util.HashSet;
import java.util.Set;

public class CategorieTransaction {
    Set<Transaction> categoTransaction;
    String nom;
    double budget;
    Utilisateur utilisateur;

    CategorieTransaction(String _nom, Utilisateur _utilisateur) {
        categoTransaction = new HashSet<Transaction>();
        nom = _nom;
        budget = 0;
        utilisateur = _utilisateur;
        utilisateur.categorie.add(this);
    }

    public void ajouterTransaction(Transaction t) {
        categoTransaction.add(t);
        if (t.type == Credit.getInstance()){
            budget += t.montant;
        }
        else {
            budget -= t.montant;
        }
    }

    public void supprimerTransaction(Transaction t) {
        categoTransaction.remove(t);
        budget -= t.montant;
    }

    @Override
    public String toString() {
        return nom + " budget : " + budget + "€";
    }
}
