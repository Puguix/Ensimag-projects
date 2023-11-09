import java.time.LocalDate;

public class Emprunt extends CompteAbstrait {
    CompteAbstrait compte;
    Integer montant;
    double taux;
    LocalDate dateLimite;

    public Emprunt(CompteAbstrait _compte, Integer _montant, double _taux, LocalDate _dateLimite) {
        compte = _compte;
        montant = _montant;
        taux = _taux;
        dateLimite = _dateLimite;
        _compte.ajouteSolde(_montant);
        compte.getUser().comptes.remove(compte.getType().toString());
        compte.getUser().comptes.put(compte.getType().toString(), this);
    }

    public void ajouteSolde(double _montant) {
        compte.ajouteSolde(_montant);
    }

    public String getRIB() {
        return compte.getRIB();
    }

    public Utilisateur getUser() {
        return compte.getUser();
    }

    public TypeCompte getType() {
        return compte.getType();
    }

    public double getSolde() {
        return compte.getSolde();
    }

    public Compte getCompte() {
        return compte.getCompte();
    }

    @Override
    public String toString() {
        String res = compte.toString();
        res += "\t Emprunt de " + montant + "€ à " + taux * 100 + "%";
        return res;
    }
}
