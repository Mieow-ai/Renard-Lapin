#include "grille.hpp"
#include "doctest.h"

//CONSTRUCTEUR

Grille::Grille() : grille{} {
	for (auto& ligne : grille) {
        ligne.fill(-1);
    }
}

//MÉTHODES

int Grille::getCase(Coord coord) const {
	return grille[coord.get_lig()][coord.get_col()];
}

bool Grille::caseVide(Coord coord) const {
	return getCase(coord) == -1;
}

void Grille::videCase(Coord coord) {
	grille[coord.get_lig()][coord.get_col()] = -1;
}

void Grille::setCase(Animal a){
	if (not(caseVide(a.getCoord()))){
		throw invalid_argument("Il y a déjà un animal sur cette case");
	}
	grille[a.getCoord().get_lig()][a.getCoord().get_col()] = a.getId();
}


//TESTS pour la grille.cpp 

TEST_CASE("Test pour la méthode getCase() et setCase()"){
	cout << "------------------------------------------" << endl;

	cout << "Lancement des tests pour la class Grille.." <<endl;
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode getCase() et setCase()..." << endl;
	Grille g;
	Animal a = Animal(10, Espece::renard, Coord(1, 2));
	g.setCase(a);
	CHECK(g.getCase(Coord(1, 2)) == 10);
	cout << "Identifiant de la case trouvée à la coordonnée (1, 2) : " << g.getCase(Coord(1, 2)) << endl;
}

TEST_CASE("Test pour la méthode caseVide()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode getCase() et caseVide()..." << endl;
	Grille g = Grille();
	CHECK(g.caseVide(Coord(0, 0)));
	CHECK(g.caseVide(Coord(2, 3)));
	Animal a = Animal(10, Espece::renard, Coord(1, 2));
	g.setCase(a);
	CHECK_FALSE(g.caseVide(Coord(1, 2)));
}

TEST_CASE("Test pour la méthode videCase()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode getCase() et videCase()..." << endl;
	Grille g = Grille();
	CHECK(g.caseVide(Coord(0, 0)));
	Animal a = Animal(10, Espece::renard, Coord(0, 0));
	g.setCase(a);
	CHECK_FALSE(g.caseVide(Coord(0, 0)));
	g.videCase(Coord(0, 0));
	CHECK(g.caseVide(Coord(0, 0)));
}