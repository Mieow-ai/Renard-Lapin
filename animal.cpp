#include<iostream>
#include <sstream>
#include <array>
#include <cstdlib>
#include "jeu.hpp"
#include "doctest.h"

using namespace std;

//Fonctions

ostream& operator<<(ostream& out, const Espece &esp) {
	switch(esp){
		case Espece::lapin : out << "lapin"; break;
		case Espece::renard : out << "renard"; break;
		default : out << "";
	}
	return out;
}

//MÉTHODES

int Animal::getId() const {
	return id;
}

Coord Animal::getCoord() const {
	return coord;
}

void Animal::setCoord(Coord c) {
	if ((c.get_lig() < 0) || (c.get_lig() >= 40) || (c.get_col() < 0) || (c.get_col() >= 40)) {
		throw invalid_argument("La coordonnées n'est pas valide");
	}else if(c == coord){
		return;
	}
	coord = c;
}

Espece Animal::getEspece() const {
	return esp;
}

ostream& Animal::affiche(ostream& out) {
	out << "L'espèce de l'animal : " << esp << endl;
	out << "L'identifiant de l'animal : " << id << endl;
	out << "Les coordonnées de l'animal : " << coord << endl;
	out << "La nourriture de l'animal : " << nourriture << endl;
	return out;
}

bool Animal::meurt() const {
	return (nourriture == 0 && esp == Espece::renard);
}

bool Animal::seReproduit(Ensemble voisins_vides, float proba_birth_lapin, float proba_birth_renard) const {
	if(esp == Espece::lapin){
		return voisins_vides.cardinal() >= 4 && (rand() / (double)RAND_MAX <= proba_birth_lapin);
	}
	return nourriture >= FoodReprod && (rand() / (double)RAND_MAX <= proba_birth_renard);
}

void Animal::mange() {
	if (esp == Espece::renard) {
	nourriture = min(nourriture + FoodLapin, MaxFood);
	}
}

void Animal::jeune() {
	if (esp == Espece::renard) {
		nourriture--;
		nourriture = max(nourriture, 0);
	}
}

//TESTS pour animal.cpp

TEST_CASE("opérateur d'affichage espèce"){
	cout << "------------------------------------------" << endl;

	cout << "Lancement des tests pour la class Animal.." <<endl;

	cout << "------------------------------------------" << endl;
	cout << "Test pour l'opérateur d'affichage espèce..." << endl;
	Espece esp1 = Espece::lapin;
	Espece esp2 = Espece::renard;
	cout << esp1 << endl;
	cout << esp2 << endl;
}

TEST_CASE("Test pour le constructeur par défault"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du Test pour le constructeur par défault..." << endl;
	Animal a = Animal();
	CHECK(a.getId() == -1);
	CHECK(a.getCoord() == Coord(0, 0));
}

TEST_CASE("Test pour le constructeur avec un identifiant, une espèce et une coordonnée"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du Test pour le constructeur avec un identifiant, une espèce et une coordonnée..." << endl;
	Animal a = Animal(10, Espece::renard, Coord(1, 2));
	CHECK(a.getId() == 10);
	CHECK(a.getCoord() == Coord(1, 2));
	CHECK(a.getEspece() == Espece::renard);
}


TEST_CASE("Test pour la méthode getId()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode getId()..." << endl;
	Animal a = Animal();
	CHECK(a.getId() == -1);
	Animal b = Animal(10, Espece::renard, Coord(1, 2));
	CHECK(b.getId() == 10);
}

TEST_CASE("Test pour la méthode getCoord()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode getCoord()..." << endl;
	Animal a = Animal();
	CHECK(a.getCoord() == Coord(0, 0));
	Animal b = Animal(10, Espece::renard, Coord(1, 2));
	CHECK(b.getCoord() == Coord(1, 2));
}

TEST_CASE("Test pour la méthode setCoord()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode setCoord()..." << endl;
	Animal a = Animal();
	a.setCoord(Coord(2, 1));
	CHECK(a.getCoord() == Coord(2, 1));
}

TEST_CASE("Test pour la méthode meurt()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode meurt()..." << endl;
	Animal a = Animal(10, Espece::renard, Coord(1, 2));
	a.jeune();a.jeune();a.jeune();a.jeune();a.jeune();
	CHECK(a.meurt());
}

/*
TEST_CASE("Test pour la méthode seReproduit()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode seReproduit()..." << endl;
	Animal a = Animal(10, Espece::renard, Coord(1, 2));
	a.mange(); 
	CHECK(a.seReproduit());
}
*/

TEST_CASE("Test pour la méthode mange()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode mange()..." << endl;
	Animal a = Animal(10, Espece::renard, Coord(1, 2)); // il commence à 3 de nourriture
	a.mange(); // on le fait manger une fois
	a.jeune(); a.jeune();
	a.jeune(); a.jeune();
	a.jeune(); a.jeune();
	a.jeune(); a.jeune();
	a.jeune(); a.jeune();// On le fait jeuner 10 fois
	CHECK(a.meurt()); // normalement nourriture == 0 donc il meurt
}

TEST_CASE("Test pour la méthode jeune()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode jeune()..." << endl;
	Animal a = Animal(10, Espece::renard, Coord(1, 2)); // il commence à 3 de nourriture
	a.jeune(); a.jeune(); a.jeune(); a.jeune(); a.jeune(); // On le fait jeuner 3 fois
	CHECK(a.meurt()); // normalement nourriture == 0 donc il meurt
}