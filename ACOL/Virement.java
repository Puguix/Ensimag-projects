public class Virement extends TypeTransaction {
    Compte destinataire;

    public Virement(Compte _destinataire) {
        super();
        destinataire = _destinataire;
    }

    @Override
    void faireTransaction(Transaction t) {
        t.compte.ajouteSolde(-t.montant);
        destinataire.ajouteSolde(t.montant);
    }

    @Override
    public String toString() {
        return "virement à " + destinataire.getRIB();
    }

    @Override
    public void verifierTransaction(Transaction t) {
        if (t.montant > t.compte.getSolde()) {
            throw new IllegalArgumentException("Le montant dépasse votre solde.");
        }
        if (t.compte.getSolde() - t.montant < t.compte.getType().soldeMin) {
            throw new IllegalArgumentException("Solde minimal atteint");
        }
        if (destinataire.getType().soldeMax < destinataire.solde + t.montant) {
            throw new IllegalArgumentException("Solde maximal atteint");
        }
    }

}
