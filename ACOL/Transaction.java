import java.time.LocalDateTime;

public class Transaction {
    CompteAbstrait compte;
    TypeTransaction type;
    double montant;
    LocalDateTime date;

    public Transaction(CompteAbstrait _compte, TypeTransaction _type, double _montant) {
        compte = _compte;
        type = _type;
        montant = _montant;
        try {
            _type.verifierTransaction(this);
        } catch (IllegalArgumentException e) {
            System.out.println("Erreur : " + e.getMessage());
            return;
        }
        date = LocalDateTime.now();
        type.faireTransaction(this);
        compte.transactions.add(this);
    }

    @Override
    public String toString() {
        return type + " : " + montant;
    }
}
