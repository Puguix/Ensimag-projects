public enum TypeCompte {
    COURANT(0, 50000, 1000000000, 0),
    LIVRETA(0.02, 23000, 22950, 15),
    LIVRETJEUNE(0.03, 2000, 1600, 10),
    PEA(0.08, 150000, 150000, 15);

    double rendement;
    double plafond;
    double soldeMax;
    double soldeMin;

    private TypeCompte(double _rendement, double _plafond, double _soldeMax, double _soldeMin) {
        rendement = _rendement;
        plafond = _plafond;
        soldeMax = _soldeMax;
        soldeMin = _soldeMin;
    }
}
