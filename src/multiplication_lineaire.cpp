#include "multiplication_lineaire.hpp"

void multiplicationLineaire(const std::vector<int> &A, std::vector<int> &B)
{
    // Insérer votre code ici

    // Notez que la fonction ne retourne pas de vecteur, elle modifie le
    // vecteur B directement.
    const int IDENTITY_ELEMENT = 1;
    const int ABSORBING_ELEMENT = 0;
    const int VECTOR_SIZE = A.size();

    int totalProductExceptZeroes = IDENTITY_ELEMENT;

    //std::unordered_map<int, int> map1 = std::unordered_map<int, int>(); À cause du pire cas en N, on peut arriver en n^2
    //std::vector<int> absorbingIndicesVector = std::vector<int>(VECTOR_SIZE); //O(n) pourrait être O(1) sans le paramètre, mais forcerait un constant ammorti
    std::vector<int> absorbingIndicesVector = std::vector<int>();

    // Parcourir tous les éléments du vecteur en multipliant les nombres non-absorbant et en conservant
    // les indices d'élément absorbant dans une liste à part.
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        const int value = A.at(i); // Temps contants
        if (value == ABSORBING_ELEMENT)
        {
            absorbingIndicesVector.push_back(i); //constant amorti
        }
        else
        {
            totalProductExceptZeroes *= value;
        }
    }

    //Affecter le produit au vecteur B.
    if (absorbingIndicesVector.size() > 1)
    {
        B.assign(VECTOR_SIZE, 0); //Puisqu'il y a au moins deux zéros dans le vecteur A, le produit sera toujours 0;
    } else if (absorbingIndicesVector.size() == 1)
    {
        B.assign(VECTOR_SIZE, 0); //S'il y a un zéro, alors tout le monde va avoir zero comme valeur, sauf l'index du zero, qui aura le produit au complet.
        int absorbingIndex = absorbingIndicesVector.back();
        B.at(absorbingIndex) = totalProductExceptZeroes;
    } else
    {
        // Puisqu'il y a aucun zéro, la valeur de B sera le produit, diviser par l'élément de l'index (pour le retirer)
        for (int i = 0; i < VECTOR_SIZE; i++)
        {
            B.push_back(totalProductExceptZeroes / A.at(i));
        }
    }
}
