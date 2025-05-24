#include "coord.hpp"
#include "Ensemble.hpp"
#include "doctest.h"
#include<stdexcept>
#include<iostream>

using namespace std;

//Fonctions

int max(int a, int b){
	if(a > b) return a;
	return b;
}

int min(int a, int b){
	if(a < b) return a;
	return b;
}

//OPÉRATEURS

ostream& operator<<(ostream &out, Coord &point){
	out << "(" << point.get_lig() << ", " << point.get_col() << ")" << endl;
	return out;
}

bool operator==(const Coord &a, const Coord &b){
	return a.get_lig() == b.get_lig() && a.get_col() == b.get_col();
}

bool operator!=(const Coord &a, const Coord &b){
	return not(a == b);
}

//CONSTRUCTEURS

Coord::Coord(int lig, int col) : lig{lig}, col{col} {
	if(lig < 0 || col < 0){
		throw invalid_argument("Les lignes et les colonnes ne peuvent pas être négatives");
	}else if(lig > 40 || col > 40){
		throw invalid_argument("Les lignes et les colonnes ne peuvent pas être supérieures à 40");
	}
}

Coord::Coord(int p) : lig{}, col{} {
	if (p < 0 || ((p - p % TAILLEGRILLE) / TAILLEGRILLE) >= TAILLEGRILLE){
		throw invalid_argument("L'entier n'est pas valide");
	}
	lig = (p - p % TAILLEGRILLE) / TAILLEGRILLE;
	col = p % TAILLEGRILLE;
}

//MÉTHODES

int Coord::get_lig() const{
	return lig;
}

int Coord::get_col() const{
	return col;
}

pair<int, int> Coord::get_coord() const{
	pair<int, int> res;
	res.first = lig;
	res.second = col;
	return res;
}

int Coord::toInt() const {
	return get_lig() * TAILLEGRILLE + get_col();
}

Ensemble Coord::voisines() const{
	Ensemble ev = Ensemble();
	for(int i = max(lig - 1, 0) ; i < min(lig + 1, TAILLEGRILLE - 1) + 1 ; i++){
		for(int j = max(col - 1, 0) ; j < min(col + 1, TAILLEGRILLE - 1) + 1 ; j++){
			Coord voisin  = Coord(i, j);
			if(i != lig || j != col){
				ev.ajoute(voisin.toInt());
			}
		}
	}
	return ev;
}

//TESTS pour coord.cpp

TEST_CASE("Constructeur (int lig, int col)"){
	cout << "------------------------------------------" << endl;

	cout << "Lancement des tests pour la class Coord.." <<endl;

	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour le constructeur à partir d'un int de ligne et un int de colonne.." << endl;
	Coord point = Coord(4, 3);
	CHECK(point.get_lig() == 4);
	CHECK(point.get_col() == 3);
	CHECK(point.get_coord().first == 4);
	CHECK(point.get_coord().second == 3);
	CHECK_THROWS_AS(Coord({-50, 30}), invalid_argument);
	CHECK_THROWS_AS(Coord({-5, 20}), invalid_argument);
	CHECK_THROWS_AS(Coord({20, 60}), invalid_argument);
}

TEST_CASE("Constructeur (int p)"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour le constructeur à partir d'un entier.." << endl;
	GIVEN("On créer nos points"){
		Coord point = Coord(124);
		Coord point2 = Coord(206);
		THEN("On test si ça donne bien le point que l'on souhaite"){
			CHECK(point.get_lig() == 3);
			CHECK(point.get_col() == 4);
			CHECK(point2.get_lig() == 5);
			CHECK(point2.get_col() == 6);
		}
	}
}

TEST_CASE("Opérateur d'affichage pour la class Coord"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour les opérateurs d'affichage pour un point de coordonnées.." << endl;
	GIVEN("On créer notre coordonnées de test"){
		Coord test = Coord(5, 2);
		WHEN("On vérifie que les coordonnées ont bien été transmises"){
			CHECK(test.get_coord().first == 5);
			CHECK(test.get_coord().second == 2);
			cout << "Affichage des coordonnées attendues : (5, 2)" << endl;
			THEN("On affiche le point de coordonnées et on test si c'est bon"){
				cout << "Affichage grâce à l'opérateur d'affichage : " << test << endl;
			}
		}
	}
}

TEST_CASE("Opérateurs d'égalité et d'inégalité"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour les opérateurs d'égalité et d'inégalité.." << endl;
	GIVEN("On initialise nos points"){
		Coord a = Coord(4, 6);
		Coord b = Coord(1, 2);
		Coord c = Coord(1, 2);
		Coord d = Coord(2, 1);
		THEN("On test les opérateurs"){
			CHECK(b == c);
			CHECK_FALSE(a == b);
			CHECK_FALSE(d == c);
		}
	}
}

TEST_CASE("Test pour la méthode toInt()"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour la méthode toInt().." << endl;
	GIVEN("On créer nos points"){
		Coord a = Coord(3, 4);
		Coord b = Coord(5, 6);
		WHEN("On applique la méthode toInt()"){
			int l = a.toInt();
			int m = b.toInt();
			THEN("On test les résultats"){
				CHECK(l == 124);
				CHECK(m == 206);
			}
		}
	}
}

TEST_CASE("Test pour la méthode voisines()"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour la méthode voisines().." << endl;
	GIVEN("On créer nos points"){
		Coord a = Coord(2, 1);
		Coord b = Coord(0, 0);
		Coord c = Coord(39, 39);
		WHEN("On applique la méthode voisines()"){
			Ensemble ensa = a.voisines();
			Ensemble ensb = b.voisines();
			Ensemble ensc = c.voisines();
			THEN("On test les résultats"){
				cout << "Ensemble voisin de a : " << ensa << endl;
				cout << "Cardinal de l'ensemble voisin de a : " << ensa.cardinal() << endl;
				cout << "Ensemble voisin de a : " << ensb << endl;
				cout << "Cardinal de l'ensemble voisin de b : " << ensb.cardinal() << endl;
				cout << "Ensemble voisin de a : " << ensc << endl;
				cout << "Cardinal de l'ensemble voisin de c : " << ensc.cardinal() << endl;
				cout << "------------------------------------------" << endl;
			}
		}
	}
}