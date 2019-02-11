#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <vector>
#include <algorithm>

// Cette version de la recherche binaire retourne le plus
// grand index i tel que vecteur[i] <= element. -1 est retourné si
// tous les éléments sont > element.
long recherche_binaire(const std::vector<int>& vecteur, int element);

#endif
