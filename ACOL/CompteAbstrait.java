import java.util.HashSet;
import java.util.Set;

public abstract class CompteAbstrait {

    Set<Transaction> transactions;

    public CompteAbstrait() {
        transactions = new HashSet<Transaction>();
    }

    abstract void ajouteSolde(double _montant);

    abstract String getRIB();

    abstract Utilisateur getUser();

    abstract TypeCompte getType();

    abstract double getSolde();

    abstract Compte getCompte();

    public void annulerTransaction(Transaction t) {
        transactions.remove(t);
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof CompteAbstrait)) {
            return false;
        }
        CompteAbstrait c = (CompteAbstrait) o;
        return c.getUser() == this.getUser() && c.getType() == this.getType();
    }
}
