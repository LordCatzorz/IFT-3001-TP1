#include "arbre.h"
#include "utilitaire.h"
#include <iostream>
#include <stdio.h>
#include <limits>
#include <assert.h>

using namespace std;

// Type d'une fonction qui travaille sur un vecteur sans avoir à le copier.
// Obliger de faire ainsi, puisque je ne peux pas modifier le .h.
typedef std::function<Noeud(const vector<const Point *> &points, const size_t beginIndex, const size_t endIndex)> fncBuildNode;

// La méthode construire_noeud doit construire un noeud dont les feuilles représentent les points contenus dans le
// le vecteur points. S'il y a un seul point, le noeud est en fait une feuille. Utilisez la technique de conception
// Diviser pour régner pour faire cette méthode. Vous pouvez vous inspirer de l'algorithme de tri fusion.
Noeud Arbre::construire_noeud(const vector<const Point *> &points)
{
    // Déclaration d'une fonction lambda récursive pour initialiser l'arbre à partir
    // d'un vecteur sans avoir à le copier.
    fncBuildNode build_node;
    build_node = [&build_node, this](const vector<const Point *> &points, const size_t beginIndex, const size_t endIndex) {
        size_t nbPoints = (endIndex - beginIndex) + 1;
        if (nbPoints == 1)
        {
            return Noeud(points.at(beginIndex));
        }
        else
        {
            size_t middleIndex = beginIndex + std::ceil(nbPoints/2.0f) - 1; // Fonction plafond pour privilégier la première moitié.

            std::unique_ptr<Noeud> node1 = std::make_unique<Noeud>(build_node(points, beginIndex, middleIndex));
            std::unique_ptr<Noeud> node2 = std::make_unique<Noeud>(build_node(points, middleIndex + 1, endIndex));

            Noeud currentNode = Noeud();
            //Déterminer quel noeud est le gauche et le droit.
            if (node1->x <= node2->xMax)
            {
                currentNode.enfantGauche = std::move(node1);
                currentNode.enfantDroit = std::move(node2);
            }
            else
            {
                currentNode.enfantGauche = std::move(node2);
                currentNode.enfantDroit = std::move(node1);
            }

            currentNode.xMax = currentNode.enfantDroit->xMax;
            currentNode.x = currentNode.enfantGauche->xMax;

            this->fusion(currentNode);

            return currentNode;
        }
    };
    
    return build_node(points, 0, points.size() - 1);
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
void Arbre::fusion(Noeud &parent)
{
    // Insérer votre code ici
    size_t nbLeafsLeft = parent.enfantGauche->valeursY.size();
    size_t nbLeafsRight = parent.enfantDroit->valeursY.size();
    size_t nbLeafsParent = nbLeafsLeft + nbLeafsRight;
    size_t currentLeftIndex = 0;
    size_t currentRightIndex = 0;
    size_t currentParentIndex = 0;
    size_t* ptrIncrementingIndex = &currentLeftIndex;

    int currentLeftValue = parent.enfantGauche->valeursY.at(currentLeftIndex);
    int currentRightValue = parent.enfantDroit->valeursY.at(currentRightIndex);
    int pushedValue = std::numeric_limits<int>::min();
    
    for(currentParentIndex; currentParentIndex < nbLeafsParent; currentParentIndex++)
    {
        if (currentLeftIndex < nbLeafsLeft 
            && (currentRightIndex >= nbLeafsRight 
                || currentLeftValue <= currentRightValue))
        {
            pushedValue = currentLeftValue;
            //Garder en pointeur l'indexeur de gauche
            ptrIncrementingIndex = &currentLeftIndex;
        }
        else
        {
            pushedValue = currentRightValue;
            //Garder en pointeur l'indexeur de droit
            ptrIncrementingIndex = &currentRightIndex;
        }

        //Ajouter la valeur dans Y
        parent.valeursY.push_back(pushedValue);

        // Ajouter l'index dans G
        int pushedLeftIndex = currentLeftIndex - 1;
        if (currentLeftValue <= pushedValue)
        {
            pushedLeftIndex = std::min<int>(currentLeftIndex, nbLeafsLeft - 1);
        }
        parent.pointeursGauche.push_back(pushedLeftIndex);

        // Ajouter l'index dans D
        int pushedRightIndex = currentRightIndex - 1;
        if (currentRightValue <= pushedValue)
        {
            pushedRightIndex = std::min<int>(currentRightIndex, nbLeafsRight -1);
        }
        parent.pointeursDroite.push_back(pushedRightIndex);

        // Incrémenter le pointeur d'idexeur garder plus haut
        (*ptrIncrementingIndex)++;

        // Rafraichir les valeurs des noeud.
        if (currentLeftIndex < nbLeafsLeft)
        {
            currentLeftValue = parent.enfantGauche->valeursY.at(currentLeftIndex);
        }

        if (currentRightIndex < nbLeafsRight)
        {
            currentRightValue = parent.enfantDroit->valeursY.at(currentRightIndex);
        }
    }


    // Le code qui suit est composé de post-conditions que la méthode fusion doit respecter pour
    // construire l'arbre correctement.
    // N'en prenez pas compte dans l'analyse.
    for (size_t i = 0; i < parent.valeursY.size() - 1; i++)
    {
        assert(parent.valeursY.at(i) <= parent.valeursY.at(i + 1));

        assert(parent.pointeursGauche.at(i) == -1 ||
               parent.enfantGauche->valeursY.at(parent.pointeursGauche.at(i)) <= parent.valeursY.at(i));
        assert(parent.pointeursDroite.at(i) == -1 ||
               parent.enfantDroit->valeursY.at(parent.pointeursDroite.at(i)) <= parent.valeursY.at(i));
    }
}

// La méthode requete doit retourner un vecteur contenant tous les points (x, y) tels que (x <= chi && y <= gamma).
// Vous pouvez faire appel à la méthode rapporter. Inspirez-vous de l'exemple de requête de l'énoncé.
vector<const Point *> Arbre::requete(int chi, int gamma) const
{
    auto indexY = recherche_binaire(racine->valeursY, gamma);
    if (indexY == -1)
    {
        // Tous les points sont en dehors de la requête
        return vector<const Point *>();
    }

    vector<const Point *> resultats;

    const Noeud *courant = racine.get();

    // Insérer votre code ici.
    vector<const Point *> pointsSatisfaisantGamma;
    rapporter(courant, indexY, pointsSatisfaisantGamma);

    for (auto rit = pointsSatisfaisantGamma.crbegin(); rit != pointsSatisfaisantGamma.crend(); ++rit)
    {
        if ((*rit)->x <= chi)
        {
            resultats.push_back((*rit));
        }
    }

    return resultats;
}
