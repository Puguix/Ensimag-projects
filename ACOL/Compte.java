
import java.security.SecureRandom;

public class Compte extends CompteAbstrait {
    Utilisateur user;
    TypeCompte type;
    String RIB;
    double solde;

    static SecureRandom random = new SecureRandom();
    static Integer nombreDeCompte = random.nextInt();

    public Compte(Utilisateur _user, TypeCompte _type, double argent) {
        user = _user;
        type = _type;
        nombreDeCompte++;
        RIB = createRIB(nombreDeCompte);
        solde = argent;
        if (solde < _type.soldeMin) {
            throw new IllegalArgumentException(
                    "Solde minimal atteint, vous devez mettre au moins " + _type.soldeMin + "€\n");
        }
        if (solde > _type.soldeMax) {
            throw new IllegalArgumentException("Solde maximal atteint, le maximum est  " + _type.soldeMax + "€\n");
        }
        if (_type != TypeCompte.COURANT) {
            user.comptes.get("COURANT").ajouteSolde(-argent);
        }
        user.comptes.put(type.toString(), this);
    }

    private String createRIB(Integer n) {
        String RIB = "FR76";
        for (int j = 0; j < 18; j++) {
            RIB += Integer.toString(random.nextInt(10));
        }
        RIB += String.format("%05d", n);
        return RIB;
    }

    public void ajouteSolde(double _montant) {
        if (solde + _montant > this.type.soldeMax) {
            throw new IllegalArgumentException("Le solde Maximum est dépassé");
        }
        if (solde + _montant < this.type.soldeMin) {
            throw new IllegalArgumentException("Le solde Minimum n'est pas atteint");
        }
        solde += _montant;
    }

    public String getRIB() {
        return RIB;
    }

    public Utilisateur getUser() {
        return user;
    }

    public TypeCompte getType() {
        return type;
    }

    public double getSolde() {
        return solde;
    }

    @Override
    Compte getCompte() {
        return this;
    }

    @Override
    public String toString() {
        String res = "RIB: " + RIB + " | " + type + " avec " + solde + "€\n";
        if (transactions.size() == 0) {
            res += "Pas de transaction";
        } else {
            res += "Liste des transactions: \n";
            for (Transaction t : transactions) {
                res += "\t " + t + "€\n";
            }
        }
        return res;
    }
}