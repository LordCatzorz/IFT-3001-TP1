#include <iostream>
#include <string>

#include "multiplication_lineaire.hpp"

void affiche_vecteur(const std::string& message, const std::vector<int>& vecteur) {
  std::cerr << message;
  std::cerr << "[";
  if (!vecteur.empty()) {
    std::cerr << vecteur.front();
  }
  for (unsigned int i = 1; i < vecteur.size(); i++) {
    std::cerr << ", " << vecteur[i];
  }
  std::cerr << "]" << std::endl;
}

bool execute_test(const std::string& nom_du_test, const std::vector<int>& A, const std::vector<int>& B) {
  std::vector<int> solution_retournee;
  multiplicationLineaire(A, solution_retournee);
  if (solution_retournee == B) {
    std::cerr << "+1 point: " << nom_du_test << " a passe" << std::endl;
    return true;
  } else {
    std::cerr << "+0 point: Le test " << nom_du_test << " a echoue" << std::endl;
    affiche_vecteur("   Vecteur A:          ", A);
    affiche_vecteur("   Solution retournee: ", solution_retournee);
    affiche_vecteur("   Solution desiree:   ", B);
    return false;
  }
}

bool testSimple() {
  const int A[3] = {1, 2, 3};
  const int B[3] = {6, 3, 2};
  return execute_test("Test simple", std::vector<int>(A, A+3), std::vector<int>(B, B+3));
}

bool testVecteurVide() {
  return execute_test("Test du vecteur vide", std::vector<int>(), std::vector<int>());
}

bool testAvecNombreNegatifs() {
  const int A[5] = {1, -2, 3, -4, 5};
  const int B[5] = {120, -60, 40, -30, 24};
  return execute_test("Test avec nombres negatifs", std::vector<int>(A, A+5), std::vector<int>(B, B+5));
}

bool testAvecNombreNul() {
  const int A[4] = {3, 2, 0, 3};
  const int B[4] = {0, 0, 18, 0};
  return execute_test("Test avec nombre nul", std::vector<int>(A, A+4), std::vector<int>(B, B+4));
}

bool testAvecNombresNuls() {
  const int A[5] = {2, 0, 4, 5, 0};
  const int B[5] = {0, 0, 0, 0, 0};
  return execute_test("Test avec nombres nuls", std::vector<int>(A, A+5), std::vector<int>(B, B+5));
}

int main() {
  testSimple();
  testVecteurVide();
  testAvecNombreNegatifs();
  testAvecNombreNul();
  testAvecNombresNuls();
  return 0;
}
