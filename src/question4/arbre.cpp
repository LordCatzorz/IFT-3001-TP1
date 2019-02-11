#include "arbre.h"
#include "utilitaire.h"
#include <iostream>
#include <stdio.h>
#include <limits>
#include <assert.h>

using namespace std;

Arbre::Arbre(const std::vector<Point>& points) {
    vector<const Point*> pointsPointeurs;
    pointsPointeurs.reserve(points.size());
    for (const Point& point : points) {
        pointsPointeurs.push_back(&point);
    }

    sort(pointsPointeurs.begin(), pointsPointeurs.end(), [](const Point* p1, const Point* p2){return p1->x < p2->x;});
    racine = make_unique<Noeud>(construire_noeud(pointsPointeurs));
    // Si vous n'êtes pas familier avec les unique_ptr et make_unique, je vous suggère de lire cet article
    // https://rufflewind.com/2016-03-05/unique-ptr
}

// La méthode rapporter ajoute au vecteur resultats tous les points associés aux feuilles de noeud qui ont une valeur de y
// plus petite ou égale à noeud.valeursY[indexY]. Cette méthode s'exécute en O(log n + k) où k est le nombre de points ajoutés à résultats.
void Arbre::rapporter(const Noeud* noeud, long indexY, std::vector<const Point*>& resultats) const {
    if (indexY < 0) {
        return;
    }
    if (noeud->is_feuille()) {
        resultats.push_back(noeud->point);
    } else {
        rapporter(noeud->enfantGauche.get(), noeud->pointeursGauche.at(indexY), resultats);
        if (noeud->enfantDroit != nullptr) {
            rapporter(noeud->enfantDroit.get(), noeud->pointeursDroite.at(indexY), resultats);
        }
    }
}


// Je vous conseille de ne pas passer du temps à comprendre le code en dessous de cette ligne.
// Il est utilisé uniquement pour afficher un arbre dans la console. 
void print_format(std::ostream& out, size_t largeur, size_t espacement, std::string texte) {
    assert (largeur < 1024);
    char buffer[1024]; // Ne fonctionnera pas sur des arbres très grands. Dans le cadre du TP, c'est suffisant.
    sprintf(buffer, ("|%-" + to_string(largeur) + "s|").c_str(), texte.c_str());
    string s(espacement, ' ');
    out << string(espacement, ' ') << buffer << string(espacement, ' ');
}

template<class T>
string vector_to_string(const vector<T> vecteur) {
    if (vecteur.empty()) {
        return "[]";
    }

    string out = "[";
    for (auto elem : vecteur) {
        out += to_string(elem) + ", ";
    }

    out[out.size() - 2] = ']';

    return out;
}

void print_niveau(std::ostream& out, size_t n, const vector<const Noeud*>& noeuds) {
    vector<const Noeud*> prochainNiveau;

    for (auto noeud : noeuds) {
        if (!noeud->is_feuille()) {
            prochainNiveau.push_back(noeud->enfantGauche.get());
            if (noeud->enfantDroit != nullptr) {
                prochainNiveau.push_back(noeud->enfantDroit.get());
            }
        }
    }


    size_t largeur = noeuds.at(0)->valeursY.size() * static_cast<size_t>(3) + static_cast<size_t>(10);
    size_t largeurFeuilles = n * 15;
    size_t nb_noeuds = n / noeuds.at(0)->valeursY.size();
    size_t espacement = (largeurFeuilles - largeur * nb_noeuds) / nb_noeuds;
    espacement /= 2;

    for (size_t i = 0; i < noeuds.size(); i++) {
        out << string(espacement, ' ') << string(largeur+1, '-')  << string(espacement, ' ') << " ";
    }
    out << endl;

    for (auto noeud : noeuds) {
        print_format(out, largeur, espacement, "x = " + to_string(noeud->x));
    }
    out << endl;

    for (auto noeud : noeuds) {
        print_format(out, largeur, espacement, "xMax = " + to_string(noeud->xMax));
    }
    out << endl;

    for (auto noeud : noeuds) {
        string vecteur = vector_to_string(noeud->valeursY);
        print_format(out, largeur, espacement, "Y = " + vecteur);
    }
    out << endl;

    for (auto noeud : noeuds) {
        string vecteur = vector_to_string(noeud->pointeursGauche);
        print_format(out, largeur, espacement, "G = " + vecteur);
    }
    out << endl;

    for (auto noeud : noeuds) {
        string vecteur = vector_to_string(noeud->pointeursDroite);
        print_format(out, largeur, espacement, "D = " + vecteur);
    }
    out << endl;

    for (size_t i = 0; i < noeuds.size(); i++) {
        out << string(espacement, ' ') << string(largeur+1, '-')  << string(espacement, ' ') << " ";
    }
    out << endl;

    if (!prochainNiveau.empty()) {
        print_niveau(out, n, prochainNiveau);
    }
}

size_t plus_grande_puissance2(size_t n) {
    size_t puissance = 1;
    while (puissance < n) {
        puissance *= 2;
    }

    return puissance;
}

std::ostream& operator<< (std::ostream& out, const Arbre& arbre) {
    size_t n = plus_grande_puissance2(arbre.racine->valeursY.size());
    print_niveau(out, n, {arbre.racine.get()});
    return out;
}
