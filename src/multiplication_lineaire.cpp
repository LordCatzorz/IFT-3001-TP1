#include "multiplication_lineaire.hpp"

void multiplicationLineaire(const std::vector<int> &A, std::vector<int> &B)
{
    const int IDENTITY_ELEMENT = 1; // Valeur dans le vecteur qui ne changera pas le résultat de la production.
    const int ABSORBING_ELEMENT = 0; // Valeur dans le vecteur qui forcera la production à avoir toujours le même résultat.
    const int VECTOR_SIZE = A.size();
    const int ABSORBING_INDEX_DEFAUT_VALUE = -1; // Valeur sentinelle pour indiquer que l'on a pas trouvé dans le vecteur une valeur absorbante.

    int totalProductExceptZeroes = IDENTITY_ELEMENT; // Variable pour garder en mémoire la valeur de la production, en exclant les valeurs absorbantes.

    int indexOfAbsorbingElement = ABSORBING_INDEX_DEFAUT_VALUE; // Cette variable sera modifié si l'on trouve UNE(1) valeur absorbante dans le vecteur.
    bool productIsAlwaysZero = false; // Cette variable sera modifié si l'on trouve au moins DEUX(2) valeurs absorbantes.

    // Parcourir tous les éléments du vecteur en multipliant les nombres non-absorbant et en conservant
    // les indices d'élément absorbant dans une liste à part.
    for (int i = 0; !productIsAlwaysZero && i < VECTOR_SIZE; i++)
    {
        const int value = A.at(i); // Temps contants
        if (value == ABSORBING_ELEMENT)
        {
            if (indexOfAbsorbingElement == ABSORBING_INDEX_DEFAUT_VALUE)
            {
                indexOfAbsorbingElement = value;
            }
            else
            {
                productIsAlwaysZero = true;
            }
        }
        else
        {
            totalProductExceptZeroes *= value;
        }
    }

    //Affecter le produit au vecteur B.
    if (productIsAlwaysZero)
    {
        B.assign(VECTOR_SIZE, 0); //Puisqu'il y a au moins deux zéros dans le vecteur A, le produit sera toujours 0;
    } else if (indexOfAbsorbingElement != ABSORBING_INDEX_DEFAUT_VALUE)
    {
        B.assign(VECTOR_SIZE, 0); //S'il y a un zéro, alors tout le monde va avoir zero comme valeur, sauf l'index du zero, qui aura le produit au complet.
        B.at(indexOfAbsorbingElement) = totalProductExceptZeroes;
    } else
    {
        // Puisqu'il y a aucun zéro, la valeur de B sera le produit, diviser par l'élément de l'index (pour le retirer)
        for (int i = 0; i < VECTOR_SIZE; i++)
        {
            B.push_back(totalProductExceptZeroes / A.at(i));
        }
    }
}
