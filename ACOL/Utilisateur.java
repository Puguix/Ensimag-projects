import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.time.LocalDate;

public class Utilisateur {
    Integer id;
    String nom;
    String prenom;
    LocalDate dateNaissance;
    String mail;
    String motDePasse;
    HashMap<String, CompteAbstrait> comptes;
    Set<CategorieTransaction> categorie;

    static private Integer userNumber = 0;

    public Utilisateur(String _nom, String _prenom, LocalDate _naissance, String _mail, String _motDePasse) {
        id = userNumber;
        userNumber++;
        nom = _nom;
        prenom = _prenom;
        dateNaissance = _naissance;
        mail = _mail;
        motDePasse = _motDePasse;
        comptes = new HashMap<String, CompteAbstrait>();
        new Compte(this, TypeCompte.COURANT, 0);
        categorie = new HashSet<CategorieTransaction>();
    }

    public void supprimerCompte(Compte c) {
        if (c.getType() == TypeCompte.COURANT) {
            throw new IllegalArgumentException("Vous ne pouvez pas fermer votre compte courant");
        }
        comptes.remove(c.getType().toString());
        comptes.get(TypeCompte.COURANT.toString()).ajouteSolde(c.getSolde());
    }

    @Override
    public String toString() {
        String res = prenom + " " + nom + " : " + mail + " | " + motDePasse + "\n";
        for (CompteAbstrait c : comptes.values()) {
            res += c + "\n";
        }
        for (CategorieTransaction ca : categorie) {
            res += ca + "\n";
        }
        return res;
    }
}