import java.time.LocalDate;

public class RembourserEmprunt extends TypeTransaction {

    @Override
    void faireTransaction(Transaction t) {
        t.compte.getUser().comptes.remove(t.compte.getType().toString());
        t.compte.getUser().comptes.put(t.toString(), t.compte.getCompte());
    }

    @Override
    public void verifierTransaction(Transaction t) {
        if (t.montant > t.compte.getSolde()) {
            throw new IllegalArgumentException("Le montant dépasse votre solde.");
        }
        if (t.compte.getSolde() - t.montant < t.compte.getType().soldeMin) {
            throw new IllegalArgumentException("Solde minimal atteint");
        }
        if (!(t.compte instanceof Emprunt)) {
            throw new IllegalArgumentException("Vous n'avez pas d'emprunt");
        }
        Emprunt e = (Emprunt) t.compte;
        if (e.dateLimite != LocalDate.now()) {
            throw new IllegalArgumentException("Date de remboursement non atteinte");
        }
        if (t.montant != e.taux * e.montant) {
            throw new IllegalArgumentException("Montant invalide");
        }
    }

    @Override
    public String toString() {
        return "Remboursement de l'emprunt";
    }
}
