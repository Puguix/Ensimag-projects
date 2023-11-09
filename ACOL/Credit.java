public class Credit extends TypeTransaction {

    private Credit() {
        super();
    }

    final private static Credit credit = new Credit();

    static Credit getInstance() {
        return credit;
    }

    @Override
    void faireTransaction(Transaction t) {
        t.compte.ajouteSolde(t.montant);
    }

    @Override
    public String toString() {
        return "crédit";
    }

    public void verifierTransaction(Transaction t){
        if (t.compte.getSolde() - t.montant > t.compte.getType().soldeMax) {
            throw new IllegalArgumentException("Solde maximal atteint");
        }
    }
}
