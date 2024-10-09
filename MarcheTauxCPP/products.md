# Liste des produits à implémenter

## Option d'achat sur action étrangère : call quanto

id : `call_quanto`

1 seule devise étrangère contenant un actif risqué : $`n_0 = 0`$, $`\bar n = 1`$ et $`n_1 = 1`$.

Le payoff de l'option s'écrit $`(S^{1,1}_T X^1_T - K)_+`$ où le strike $`K`$ est exprimé en devise domestique.

## Option d'achat sur devise étrangère

id : `call_currency`

1 seule devise étrangère mais pas d'actif risqué étranger : $`n_0 = 0`$, $`\bar n = 1`$ et $`n_1 = 0`$.

Le payoff de l'option s'écrit $`(X^1_T e^{r^1 T} - K)_+`$ où le strike $`K`$ est exprimé en devise domestique.

## Option d'échange sur actif étranger

id : `quanto_exchange`

1 actif domestique et 1 devise étrangère contenant un actif risqué étranger : $`n_0 = 1`$, $`\bar n = 1`$ et $`n_1= 1`$.

Le payoff de l'option s'écrit $`(S^{0, 1}_T - S^{1,1}_T X^1_T - K)_+`$ où le strike $`K`$ est exprimé en devise domestique.

## Option asiatique sur devise étrangère

id : `foreign_asian`

1 actif risqué domestique, 1 seule devise étrangère contenant un actif risqué : $`\bar n = 1`$ et $`n_1 = 1`$.

Le payoff de l'option s'écrit $`(\frac{1}{N} \sum_{j=1}^N X^1_{t_j} S^1_{t_j} - S^0_T)_+`$.

## Option performance sur paniers étrangers

id : `foreign_perf_basket`

N = 3.

- A la date $`t_2`$, on calcule dans chaque devise la performance du panier d'actifs de la devise entre les dates $`t_1`$ et $`t_2`$

  ```math
  P_i = \frac{\sum_{\ell = 1}^{n_i} S^{i, \ell}_{t_2}}{\sum_{\ell = 1}^{n_i} S^{i, \ell}_{t_1}} \; \text{ pour } i \in \{1, \dots, \bar n\}
  ```

  Soit $`i_{max}`$ l'indice de la devise réalisant le maximum des $`P_i`$, $`P_{i_{max}} = \max_{i \in \{1, \dots, \bar n\}} P_i`$.

- A la date $`t_3 = T`$, on échange le panier étranger ayant le mieux performé à la date $`t_2`$ contre le panier domestique et du cash.

  ```math
  \left( \frac{1}{n_{i_{max}}} \sum_{\ell = 1}^{n_{i_{max}}} S^{i_{max}, \ell}_T X^{i_{max}}_T- \frac{1}{n_0} \sum_{\ell = 1}^{n_0} S^{0, \ell}_T - K \right)_+
  ```
