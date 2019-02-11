#ifndef ARBRE_H
#define ARBRE_H

#include <memory>
#include <vector>
#include <string>
#include <iostream>

struct Point {
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};

struct Noeud {
    std::unique_ptr<Noeud> enfantGauche;
    std::unique_ptr<Noeud> enfantDroit;

    // Vecteur Y dans l'énoncé
    std::vector<int> valeursY;
    // Vecteur G dans l'énoncé
    std::vector<long> pointeursGauche;
    // Vecteur D dans l'énoncé
    std::vector<long> pointeursDroite;
    int x;
    int xMax;
    const Point* point;

    // Constructeur par défaut. Utilisez ce constructeur pour initialiser un noeud
    // autre qu'une feuille et assignez les valeurs requises manuellement.
    Noeud() : x(0), xMax(0), point(nullptr) {
    }

    // Constructeur pour initialiser une feuille de l'arbre
    explicit Noeud(const Point* point) : x(point->x), xMax(point->x), point(point) {
        valeursY.emplace_back(point->y);
        pointeursGauche.emplace_back(-1);
        pointeursDroite.emplace_back(-1);
    }

    bool is_feuille() const {
        return point != nullptr;
    }
};

class Arbre {
private:
    std::unique_ptr<Noeud> racine;

    Noeud construire_noeud(const std::vector<const Point*>& points);
    void fusion(Noeud& parent);
    void rapporter(const Noeud* noeud, long indexY, std::vector<const Point*>& resultats) const;
public:
    explicit Arbre(const std::vector<Point>& points);
    std::vector<const Point*> requete(int chi, int gamma) const;

    friend std::ostream& operator<< (std::ostream& out, const Arbre& arbre);
};

#endif
