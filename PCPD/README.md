# Projet de couverture de produits dérivés

Ce projet a pour but de développer un outil de valorisation et de couverture de produits financiers en C++ en mettant en application d'une part les principes de conception et de programmation étudiés dans les cours de 2A et d'autre part la théorie de Black Scholes présentée dans le cours _Introduction aux Produits Dérivés_.

## Projet

* Sujet : [pricer.pdf](pricer.pdf)

### Grandes étapes du projet

1. Du formalisme mathématique à la conception informatique
    - Comment représenter le modèle mathématique d’un point de vue informatique ?
    - A quoi correspondent les différents paramètres du modèle mathématique ?
    - De quelles fonctionnalités a-t-on besoin ?
1. Proposer une architecture pour votre outil.
1. Proposer des tests pour les différentes fonctionnalités.
1. Implémenter les différents composants : simulation stochastique, moteur Monte-Carlo, ...
    - Penser à tester séparément les différentes fonctionnalités au fur et à mesure.
    - Comment optimiser le code ?
    - Ne pas hésiter à refactoriser le code.

### Fonctionnalités à implémenter

- Calcul du prix en 0
- Calcul du prix en t
- Calcul du delta en t
- Calcul du portefeuille de couverture et du P&L

## Architecture

Une suggestion d'architecture est fournie dans le fichier [architecture.md](architecture.md).

## Organisation

Le projet devra être réalisé par équipes de 4 en C++.

Un squelette du projet contenant un exemple de parseur et des fichiers de données avec résultat est fourni : [pricer-skel](pricer-skel).
**Dans les fichiers de données, les lignes std\_dev ou standard deviation correspondent à l'écart type de l'estimateur Monte Carlo associé. Avec les notations du sujet, cela correspond à $\xi\_M / \sqrt{M}$.**

Vous créerez 2 exécutables différents pour le calcul des prix en 0 et pour la couverture

* Calcul du prix et des delta en zéro avec les déviations standards des estimateurs correspondant et affichage sur la console en utilisant

  ```cpp
  PricingResults res(prix, prix_std_dev, delta, delta_std_dev);
  std::cout << res << std::endl;
  ```

  Votre exécutable sera invoqué par la commande ./price0 data\_input

* Calcul du prix en 0 et de la couverture et affichage sur la console en utilisant

  ```cpp
  HedgingResults res(prix, prix_std_dev, erreur_couverture);
  std::cout << res << std::endl;
  ```

  Votre exécutable sera invoqué par la commande `./hedge market_file data_input`

  Attention, vos exécutables ne doivent rien afficher d'autre.

## Tests automatiques

Télécharger le script Python [PythonForModProg.py](PythonForModProg.py) et le répertoire [data](data) contenant des fichiers de données et les résultats attendus.

Pour tester vos prix à l'instant 0

```
python ./PythonForModProg.py --price --exec="chemin vers price0" --datadir="chemin vers le répertoire data" --outdir="répertoire de sortie"
```

Un timeout de 1 minute est appliqué au calcul du prix et des deltas en 0.

Pour tester vos couvertures, télécharger le répertoire [data-hedge](data-hedge) contenant des fichiers de données, des simulations de marchés et les résultats attendus.

```
python ./PythonForModProg.py --hedge --exec="chemin vers hedge" --datadir="chemin vers le répertoire data-hedge" --outdir="répertoire de sortie"
```

Un timeout de 5 minutes est appliqué au calcul de la couverture.

## Quelques informations techniques

Votre projet utilisera les outils/libraires suivantes

- `CMake`
- Une version récente de `g++` ou `clang++`.
- [PNL](https://pnlnum.github.io/pnl) : installer la dernière version à partir de https://github.com/pnlnum/pnl/releases. 
  - Les fichiers `win64` sont des versions binaires pour Windows uniquement.
  - Sous Linux et OSX, il faut télécharger le code source et le compiler

    ```
    cd /relative/path/to/pnl
    mkdir build
    cd  build
    cmake ..
    make
    make install
    ```

    Sous Ubuntu, il faut préalablement installer `libblas-dev`, `liblapack-dev` et `gfortran`.

  La librairie PNL est déjà installée sur les machines de l'école
  - Version optimisée: `/matieres/5MMPCPD/pnl`
  - Version avec symboles de débuggage: `/matieres/5MMPCPD/pnl-dbg`

  **Lisez la documentation [html](https://pnlnum.github.io/pnl/manual-html/pnl-manual.html) ou [pdf](https://pnlnum.github.io/pnl/pnl-manual.pdf)**
- Une libraire de manipulation de fichiers `.json` en C++ : [nlohmann_json](https://github.com/nlohmann/). Cette librairie est disponible dans la plupart des gestionnaires de paquets
  - Homebrew : `brew install nlohmann-json`
  - Ubuntu : installer `nlohmann-json3-dev`.

  Voir un exemple d'utilisation dans [`pricer-skel/src/test_json_reader.cpp`](pricer-skel/src/test_json_reader.cpp).

### Chaîne de compilation

La compilation du projet se fera à l'aide de l'outil [cmake](http://www.cmake.org/documentation/) qui permet de générer aussi bien des Makefile Unix qu'un projet Visual. C'est un outil permettant de gérer la compilation multi-plateforme.
CMake est conçu pour lancer la compilation hors des sources de la manière suivante.

```
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/matieres/5MMPCPD/pnl ..
```

Il est possible de modifier d'autres variables utilisées par cmake

* `CMAKE_BUILD_TYPE` : Debug ou Release
* `CMAKE_CXX_COMPILER` : nom du compilateur C++
* `CMAKE_CXX_CFLAGS` : options du compilateur C++

### Profiling et fuites mémoire

Comme indiqué dans le sujet, il est important de rapidement s'assurer que le code tourne efficacement et ne contient pas de fuite mémoire.
L'utilisation d'un outil de profiling est décrite dans le [sujet](pricer.pdf). La détection de fuites mémoire se fait à l'aide de l'outil Valgrind, via la commande
```bash 
valgrind --tool=memcheck --leak-check=full --show_reachable=yes <nom-executable>
```

### L'éditeur Visual Studio Code

Nous recommandons l'utilisation de l'éditeur Visual Studio Code

* Installer l'extension C/C++ [ms-vscode.cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* Configurer l'extension: voir [https://code.visualstudio.com/docs/cpp/customize-default-settings-cpp](https://code.visualstudio.com/docs/cpp/customize-default-settings-cpp). Les propriétés sont accessibles depuis la Palette de Commandes en choisissant _C/C++: Edit Configurations (UI)_. Si après avoir configuré correctement la variable \_Include Path\_, l'intellisense ne fonctionne toujours pas, vérifiez que C\_Cpp.intelliSenseEngine = Default.
* Configurer un débuggueur: [https://code.visualstudio.com/docs/cpp/cpp-debug](https://code.visualstudio.com/docs/cpp/cpp-debug). Créer un fichier `launch.json` dans le répertoire `.vscode` contenant

  ```json
  {
    "configurations": [
        {
            "name": "(lldb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "enter program name, for example ${workspaceFolder}/a.out",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb"
        }
    ],
    "version": "2.0.0"
  }
  ```

* Installer l'extension CMake (twxs.cmake) pour activer la coloration syntaxique des fichiers CMakeLists.txt
* Il est également possible de compiler le projet directement à l'intérieur de VSCode en utilisant CMake. Pour ce faire, il faut installer l'extension CMake Tools (ms-vscode.cmake-tools). Penser à ajouter la variable CMAKE\_PREFIX\_PATH à [cmake.configureSettings](https://vector-of-bool.github.io/docs/vscode-cmake-tools/settings.html#cmake-configuresettings)

#### Comment inspecter le contenu d'un `PnlVect` ou `PnlMat` depuis la fenêtre espion (_Watch_) de Visual Studio ou Visual Studio Code

- Pour lire le contenu de l'emplacement `i` d'un `PnlVect* my_vect`, utiliser `my_vect->array[i]`.
- Pour lire l'intégralité d'un `PnlVec* my_vect` taille `n`, utiliser l'une des syntaxes `*(double(*)[n])my_vect->array`, `*(my_vect->array)@n`, `(my_vect->array),n`
- Pour lire l'intégralité de la ligne `i` d'une matrice `PnlMat *my_mat` de taille `m x n`, utiliser `*(double(*)[n])(my_mat->array + i * n`, `*(my_mat->array + i * n)@n`, `(my_mat->array + i * n),n`.
- Voir la discussion https://github.com/Microsoft/vscode-cpptools/issues/172 pour plus d'information.

## Instructions pour le rendu du projet

### Arborescence du rendu (A respecter scrupuleusement)

Le projet sera rendu sous la forme d'une archive au format `.tar.gz` dont le nom sera construit sur le format `Equipe_i.tar.gz` où `i` est le numéro de l'équipe. Cette archive créera à l'extraction l'arborescence suivante

```
Equipe_i/
   |
   |---- AUTHORS
   |---- CMakeLists.txt
   |---- README
   |---- src/
```

Vous pouvez vérifier la structure de votre archive, l'extraire et la compiler en utilisant le script [CheckArchive.py](CheckArchive.py)

```
python ./CheckArchive.py --check [--extract --destdir="chemin ou extraire l'archive" --build --pnldir="chemin vers pnl/build"] "chemin vers Equipe_i.tar.gz"
```

Si vous omettez la partie entre `[...]`, seule la structure de l'archive est vérifiée.

## FAQ

### Problèmes avec l'interface graphique de VSCode sous Ubuntu

Ce problème peut être dû à l'accélération gpu mise en place par VSCode pour le rendu graphique. Pour le désactiver:
- Lancer VSCode avec la commande suivante:
  ```bash
  code --disable-gpu
  ```
- Lancer la palette de commande (*ctrl+shift+P*)
- Choisir `Preferences: Configure Runtime Arguments`
- Ajouter l'instruction `"disable-hardware-acceleration": true`
- Redémarrer VSCode
