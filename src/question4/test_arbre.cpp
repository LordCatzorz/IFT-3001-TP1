#include "arbre.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

void print_points(const vector<const Point*> points) {
    cout << "[ ";
    for (const Point* point : points) {
        cout << "(" << point->x << ", " << to_string(point->y) << ") ";
    }
    cout << "]";
}

void print_erreur(vector<const Point*> attendu, vector<const Point*> obtenu, int chi, int gamma) {
    cout << "Requête avec χ = " << to_string(chi) << " et γ = " << to_string(gamma) << ":" << endl;
    cout << "Attendu: ";
    print_points(attendu);
    cout << endl << "Obtenu: ";
    print_points(obtenu);
    cout << endl;
}

vector<const Point*> requete_force_brute(int chi, int gamma, const vector<Point>& points) {
    vector<const Point*> resultat;
    for (const Point& point: points) {
        if (point.x <= chi && point.y <= gamma) {
            resultat.push_back(&point);
        }
    }
    return resultat;
}

bool test_requete(const vector<Point>& points, const Arbre& arbre, int chi, int gamma) {
    auto attendu = requete_force_brute(chi, gamma, points);
    auto obtenu = arbre.requete(chi, gamma);

    if (attendu.size()!= obtenu.size()) {
        print_erreur(attendu, obtenu, chi, gamma);
        return false;
    }
    for (const Point* point : attendu) {
        if (find(obtenu.begin(), obtenu.end(), point) == obtenu.end()) {
            print_erreur(attendu, obtenu, chi, gamma);
            return false;
        }
    }
    return true;
}


bool test_toutes_requetes(const Arbre& arbre, const vector<Point>& points) {
    bool pass = true;
    for (const Point& point : points) {
        pass &= test_requete(points, arbre, point.x, point.y);

        pass &= test_requete(points, arbre, point.x+1, point.y);
        pass &= test_requete(points, arbre, point.x-1, point.y);

        pass &= test_requete(points, arbre, point.x, point.y+1);
        pass &= test_requete(points, arbre, point.x, point.y-1);

        pass &= test_requete(points, arbre, point.x+1, point.y+1);
        pass &= test_requete(points, arbre, point.x-1, point.y-1);

        if (!pass) {
            return pass;
        }
    }

    return pass;
}

bool test(const vector<Point>& points, const Arbre& arbre, const string& nom, bool trace) {
    cout << "Test " << nom << ": " << endl;

    if (trace)
        cout << arbre;
    bool pass = test_toutes_requetes(arbre, points);

    if (pass) {
        cout << "+1 point, le test a passé.";
    } else {
        cout << "+0 point, le test a échoué.";
    }
    cout << endl << endl;

    return pass;
}

void test_arbre_simple(bool trace) {
    vector<Point> points = {Point(1, 1), Point(2, 2)};
    Arbre arbre(points);
    test(points, arbre, "Arbre simple", trace);
}

void test_4_points(bool trace) {
    vector<Point> points = {Point(3, 5), Point(1, 2), Point(6, 4), Point(1, 3)};
    Arbre arbre(points);
    test(points, arbre, "Arbre 4 points", trace);
}

void test_5_points(bool trace) {
    vector<Point> points = {Point(1, 1), Point(2, 2), Point(3, 1), Point(4, 5), Point(1, 6)};

    Arbre arbre(points);
    test(points, arbre, "Arbre 5 points", trace);
}

void test_8_points(bool trace) {
    vector<Point> points = {Point(8, 10), Point(1, 25), Point(4, 4), Point(6, 1), Point(1, 6), Point(5, 29), Point(4, 3), Point(1, 1)};

    Arbre arbre(points);
    test(points, arbre, "Arbre 8 points", trace);
}

void test_immense() {
    vector<Point> points;
    int n = 25;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            points.emplace_back(i+1, j+1);
        }
    }

    Arbre arbre(points);
    test(points, arbre, "Arbre immense", false);
}


int main(int argc, char** argv) {
    // Si vous voulez afficher la trace de l'arbre généré pour un des tests, passez true en paramètre à la fonction.

    test_arbre_simple(false);
    test_4_points(true);
    test_5_points(false);
    test_8_points(false);
    test_immense();

    return 0;
}
