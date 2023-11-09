public class Debit extends TypeTransaction {

    private Debit() {
        super();
    }

    final private static Debit debit = new Debit();

    static Debit getInstance() {
        return debit;
    }

    @Override
    void faireTransaction(Transaction t) {
        t.compte.ajouteSolde(-t.montant);
    }

    @Override
    public String toString() {
        return "débit";
    }

    public void verifierTransaction(Transaction t){
        if (t.montant > t.compte.getSolde()) {
            throw new IllegalArgumentException("Le montant dépasse votre solde.");
        }
        if (t.compte.getSolde() - t.montant < t.compte.getType().soldeMin) {
            throw new IllegalArgumentException("Solde minimal atteint");
        }
    }
}
