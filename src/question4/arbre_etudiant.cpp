#include "arbre.h"
#include "utilitaire.h"
#include <iostream>
#include <stdio.h>
#include <limits>
#include <assert.h>

using namespace std;

// La méthode construire_noeud doit construire un noeud dont les feuilles représentent les points contenus dans le
// le vecteur points. S'il y a un seul point, le noeud est en fait une feuille. Utilisez la technique de conception
// Diviser pour régner pour faire cette méthode. Vous pouvez vous inspirer de l'algorithme de tri fusion.
Noeud Arbre::construire_noeud(const vector<const Point*>& points) {
    // Insérez votre code ici.
}

// La méthode fusion doit initialiser les vecteurs de parent en se basant parent.enfantGauche et parent.enfantDroit.
//
// parent.valeursY doit être une fusion de parent.enfantGauche.valeursY et parent.enfantDroit.valeursY. Ce vecteur doit être trié.
//
// parent.pointeursGauche[i] doit être l'index du plus grand élément dans parent.enfantGauche.valeursY qui
// est plus petit ou égal à parent.valeursY[i]. Si aucun élément n'est plus petit ou égal, parent.pointeurGauche[i] doit être -1.
//
// parent.pointeursDroite[i] doit être l'index du plus grand élément dans parent.enfantDroit.valeursY qui
// est plus petit ou égal à parent.valeursY[i]. Si aucun élément n'est plus petit ou égal, parent.pointeurDroit[i] doit être -1.
//
// Cette méthode doit s'exécuter en Theta(parent.size()).
void Arbre::fusion(Noeud& parent) {
    // Insérer votre code ici

    // Le code qui suit est composé de post-conditions que la méthode fusion doit respecter pour
    // construire l'arbre correctement.
    // N'en prenez pas compte dans l'analyse.
    for (size_t i = 0; i < parent.valeursY.size() - 1; i++) {
        assert(parent.valeursY.at(i) <= parent.valeursY.at(i+1));

        assert(parent.pointeursGauche.at(i) == -1 ||
               parent.enfantGauche->valeursY.at(parent.pointeursGauche.at(i)) <= parent.valeursY.at(i));
        assert(parent.pointeursDroite.at(i) == -1 ||
               parent.enfantDroit->valeursY.at(parent.pointeursDroite.at(i)) <= parent.valeursY.at(i));
    }

}

// La méthode requete doit retourner un vecteur contenant tous les points (x, y) tels que (x <= chi && y <= gamma).
// Vous pouvez faire appel à la méthode rapporter. Inspirez-vous de l'exemple de requête de l'énoncé.
vector<const Point*> Arbre::requete(int chi, int gamma) const {
    auto indexY = recherche_binaire(racine->valeursY, gamma);
    if (indexY == -1) {
        // Tous les points sont en dehors de la requête
        return vector<const Point*>();
    }

    vector<const Point*> resultats;

    const Noeud* courant = racine.get();

    // Insérer votre code ici.
}
