#include "utilitaire.h"

long recherche_binaire(const std::vector<int>& vecteur, int element) {
    auto resultat = std::upper_bound(vecteur.begin(), vecteur.end(), element) ;
    long index = resultat - vecteur.begin();
    return index - 1;
}
