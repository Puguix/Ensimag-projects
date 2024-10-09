# Projet de couverture multi-devises

L'objectif du projet est d'implémenter un outil permettant de couvrir des produits dérivés faisant intervenir plusieurs devises.

## Modélisation mathématique

Considérons un marché international composé de $`1`$ devise domestique et $`\bar n`$ devises étrangères. Chaque devise contient un actif sans risque associé au taux d'intérêt. On note $`r^0`$ le taux d'intérêt domestique, et $`r^i`$ le taux d'intérêt de la devise étrangère $`i`$. Ce marché contient

- $`n_0`$ actifs risqués : $`(S^{0,1}, \dots, S^{0,n_0})`$
- Pour chaque devise $`i`$:
  - le taux de change avec la devise domestique : $`X^i`$
  - $`n_i`$ actifs risqués : $`(S^{i,1}, \dots, S^{i,n_i})`$

Les dynamiques des actifs sous la probabilité historique s'écrivent

```math
\begin{align}
  dS^{0,\ell}_t &= S^{0,\ell}_t (\mu^{0,\ell} dt + \sigma^{0,\ell} dW^{0,\ell}_t) \;\text{ pour } \ell \in \{1,\dots,n_0\} \\
  dS^{i,\ell}_t &= S^{i,\ell}_t (\mu^{i,\ell} dt + \sigma^{i,\ell} dW^{i,\ell}_t) \;\text{ pour }i \in \{1, \dots, \bar n\} \text{ et } \ell \in \{1,\dots,n_i\} \\
  dX^i_t &= X^i_t (\mu^{i,X} dt + \sigma^{i,X} dW^{i,X}_t) \;\text{ pour }i \in \{1, \dots, \bar n\} \\
\end{align}
```

où $`W^{0,\ell}`$, $`W^{i,\ell}`$ et $`W^{i,X}`$ pour $`i \in \{1, \dots, \bar n\}`$ et $`\ell \in \{1,\dots,n_i\}`$ sont des mouvements browniens réels corrélés. **Pour la spécification de la matrice de corrélation, les _actifs_ sont rangés dans l'ordre suivant**

1. Les $`n^0`$ actifs risqués domestiques
2. Pour $`i \in \{1, \dots, \bar n\}`$, les $`n_i`$ actifs risqués dans la devise $`i`$.
3. Pour $`i \in \{1, \dots, \bar n\}`$, le taux de change entre la devise domestique et la devise $`i`$.

Posons $`\bar X = (X^1, \dots, X^{\bar n})`$ et $`\bar S = (S^{i, 1}, \dots, S^{i, n_i})_{0 \le i \le \bar n}`$. La matrice de corrélation décrite ci-dessus correspond à la corrélation du vecteur d'actifs $`(\bar S, \bar X)`$ de taille $`\sum_{i=0}^{\bar n} n_i + \bar n`$ .

Considérons des dates de constatation $`0 \le t_1 <  \dots < t_N = T`$ pour $`N \ge 1`$. Votre outil devra être capable de considérer des flux, payés en $`T`$, de la forme

```math
\psi(\bar S_{t_1}, \dots, \bar S_{t_n}, \bar X_{t_1}, \dots, \bar X_{t_n})
```

## Etapes du projet

1. Proposer une formalisation mathématique du marché virtuel équivalent purement domestique sous la probabilité risque neutre domestique.
2. Implémenter et tester votre outil pour une option d'achat sur un actif étranger.
3. Implémenter et tester votre outil pour une option d'achat sur la devise étrangère.
4. Implémenter et tester votre outil pour l'ensemble des payoffs fournis ci-dessous

## Payoffs

La liste des produits à implémenter est disponible [ici](products.md).

Les fichiers de description de ces produits sont disponibles dans le répertoire [data](data).

## Organisation, contraintes techniques

- Le projet devra être réalisé en binômes.
- L'outil sera développé en C++ et utilisera
  - `CMake`
  - Une version récente de `g++` ou `clang++`.
  - [PNL](https://pnlnum.github.io/pnl) : installer la dernière version à partir de https://github.com/pnlnum/pnl/releases. Sous Ubuntu, il faut préalablement installer `libblas-dev`, `liblapack-dev` et `gfortran`.
  - Une libraire de manipulation de fichiers `.json` en C++ : [nlohmann_json](https://github.com/nlohmann/). Cette librairie est disponible dans la plupart des gestionnaires de paquets
    - Homebrew : `brew install nlohmann-json`
    - Ubuntu : installer `nlohmann-json3-dev`.
- Votre outil prendra en entrée un fichier au format `.json` décrivant les paramètres du produit dérivé, un fichier de données de marché au format `.csv` et un fichier de sortie qui contient le portefeuille de couverture au format `.json`

```
./hedging_portfolio params.json market.csv portfolio.json
```

Le fichier `portfolio.json` sera obtenu par le code suivant

```c++
// jsonParams est l'objet nlohmann::json obtenu à partir de params.json
Portfolio hedgingPortfolio(jsonParams, monteCarlo);
// calculer le portefeuille de couverture
// ....
nlohmann::json jsonPortfolio = hedgingPortfolio.positions;
std::ofstream ifout(argv[3], std::ios_base::out);
if (!ifout.is_open()) {
    std::cout << "Unable to open file " << argv[3] << std::endl;
    std::exit(1);
}
ifout << jsonPortfolio.dump(4);
ifout.close();
```

## Format de données

### Description des produits

Les données du problème sont spécifiées par un fichier `JSON` au format

```json
{
  "Currencies": [
    {
      "id": "eur",
      "InterestRate": 0.01,
      "Volatility": 0
    },
    {
      "id": "us_dollar",
      "InterestRate": 0.015,
      "Volatility": 0.18
    }
  ],
  "DomesticCurrencyId": "eur",
  "Assets": [
    {
      "CurrencyId": "eur",
      "Volatility": 0.2
    },
    {
      "CurrencyId": "us_dollar",
      "Volatility": 0.3
    }
  ],
  "NumberOfDaysInOneYear": 252,
  "PortfolioRebalancingOracleDescription": {
    "Type": "Fixed",
    "Period": 1
  },
  "Option": {
    "Type": "quanto_exchange",
    "FixingDatesInDays": {
      "Type": "Grid",
      "DatesInDays": [ 378 ]
    },
    "Strike": 10,
    "MaturityInDays": 378
  },
  "Correlations": [
    [ 1, 0.3, 0.3],
    [ 0.3, 1, 0.3],
    [ 0.3, 0.3, 1]
  ],
  "SampleNb": 50000,
  "RelativeFiniteDifferenceStep": 0.1
}
```

- `Currencies` est un tableau décrivant les devises. Chaque devise est caractérisée par le taux sans risque associée et la volatility de son taux de change. La volatilité de la devise domestique est 0.
- `Asset` est un tableau décrivant les sous-jacents risqués. Chaque sous-jacent est caractérisé par sa devise (`CurrencyId` doit correspondre à l'`id` d'une des entrées de `Currencies`) et sa volatilité.
- Toutes les dates sont spécifiées en **jours**. La valeur de `NumberOfDaysInOneYear` permet de les convertir en années si besoin.
- `Correlations` est la matrice de corrélation de l'ensemble des actifs [`Assets`, `Currencies \ {DomesticCurrency}`]. L'ordre des entrées de cette matrice est liée à l'ordre des entrées des tableaux `Assets` et `Currencies`.
- `SampleNb` est le nombre de tirages Monte-Carlo.
- `RelativeFiniteDifferenceStep` est le pas de différences finies.
- `Option` décrit les paramètres de l'option. Les paramètres `Type`, `FixingDatesInDays` et `MaturityInDays` sont obligatoires. Les autres paramètres dépendent du type de l'option.
- `FixingDatesInDays` est un objet décrivant les dates de constatation entrant dans le calcul du payoff. Il peut être de 2 types
  - une grille spécifiée par une liste de dates

    ```json
    {
      "Type": "Grid",
      "DatesInDays": [ 252 ]
    }
    ```

  - une grille régulière spécifiée par son pas

    ```json
    {
      "Type": "Fixed",
      "Period": 3
    }
    ```

- `PortfolioRebalancingOracleDescription` décrit le rebalancement du portefeuille de couverture et suite le même format que `FixingDatesInDays`

### Données de marché

Les données de marché sont au format `.csv` et correspondent au marché historique : chaque actif est côté dans sa devise. Ce sont des données journalières. Une ligne du fichier correspond à un jour. Les colonnes correspondent aux cours des actifs risqués dans l'ordre dans lequel ils apparaissent dans le `.json`, puis les cours des taux de devises (sans la devise domestique) dans lequel elles apparaissent dans le `.json`.

Voir par exemple le fichier [data/call_quanto_market.csv](data/call_quanto_market.csv).

Pour créer une matrice `PnlMat` à partir de ce fichier, il suffit d'utiliser l'instruction

```c++
PnlMat *market = pnl_mat_create_from_file("fichier.csv");
```

## Architecture

Une suggestion d'architecture (partielle) est fournie [ici](architecture.md).

## Modalités de rendu

**Date de rendu** : 9/02/2024 à 17h sur TEIDE

Le projet est à réaliser en binôme. 

Vous devez rendre une archive `Equipe_i.zip` où `i` correspond au numéro de l'équipe sur TEIDE. Cette archive créera à l'extraction l'arborescence suivante

```
Equipe_i/
    |- src
    |- AUTHORS
    |– output/
        |- call_quanto_portfolio.json
        |- call_currency_portfolio.json
        |- foreign_asian_portfolio.json
        |- quanto_exchange_portfolio.json
        |- foreign_perf_basket_portfolio.json
```

où

- `src` contient l'ensemble du code source ainsi que le `CMakeLists.txt`.
- `AUTHORS` est un fichier texte contenant les prénoms, noms et mail `grenobl-inp.fr` de chaque membre de l'équipe.
- `output` contient les fichiers `.json` décrivant l'évolution du portefeuille de couverture pour chaque produit. Ces fichiers sont obtenus avec le code

  ```c++
  // jsonParams est l'objet nlohmann::json obtenu à partir de params.json
  Portfolio hedgingPortfolio(jsonParams, monteCarlo);
  // calculer le portefeuille de couverture
  // ....
  nlohmann::json jsonPortfolio = hedgingPortfolio.positions;
  std::ofstream ifout(argv[3], std::ios_base::out);
  if (!ifout.is_open()) {
      std::cout << "Unable to open file " << argv[3] << std::endl;
      std::exit(1);
  }
  ifout << jsonPortfolio.dump(4);
  ifout.close(); // Required to make sure flush is called
  ```

## FAQ

- **Comment inspecter le contenu d'un `PnlVect` ou `PnlMat` depuis la fenêtre espion (*Watch*) de Visual Studio** ou **Visual Studio Code**:
  - Pour lire le contenu de l'emplacement `i` d'un `PnlVect* my_vect`, utiliser `my_vect->array[i]`.
  - Pour lire l'intégralité d'un `PnlVec* my_vect` taille `n`, utiliser l'une des syntaxes `*(double(*)[n])my_vect->array`, `*(my_vect->array)@n`, `(my_vect->array),n`
  - Pour lire l'intégralité de la ligne `i` d'une matrice `PnlMat *my_mat` de taille `m x n`, utiliser `*(double(*)[n])(my_mat->array + i * n`, `*(my_mat->array + i * n)@n`, `(my_mat->array + i * n),n`.
  - Voir la discussion https://github.com/Microsoft/vscode-cpptools/issues/172 pour plus d'information.
