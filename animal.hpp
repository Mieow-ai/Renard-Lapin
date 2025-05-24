#ifndef ANIMAL
#define ANIMAL

#include<iostream>
#include <sstream>
#include <array>

#include "coord.hpp"

using namespace std;

//*Type Espèce
enum class Espece {lapin, renard, undef};

const int FoodInit = 5;
const int FoodLapin = 5;
const int FoodReprod = 8;
const int MaxFood = 10;
//const float ProbBirthRenard = 0.05;
// Pour les lapins :
//const float ProbBirthLapin = 0.15;
const int MinFreeBirthLapin = 4;

class Animal{

	public :

	//CONSTRUCTEURS

	Animal(int id, Espece espece, Coord coord) : esp{espece}, id{id}, coord{coord}, nourriture{FoodInit} {}

	Animal() : esp{Espece::undef}, id{-1}, coord{Coord(0,0)}, nourriture{0} {}

	//MÉTHODES

	//* Renvoie l’identifiant de l’animal
	int getId() const;

	//* Renvoie les coordonnées de l’animal
	Coord getCoord() const;

	//* Change les coordonnées de l’animal
	void setCoord(Coord c);

	//* Renvoie l’espèce de l’animal
	Espece getEspece() const;

	//* Affiche l’animal sur un flux
	ostream& affiche(ostream& out);

	//* Est-ce que l’animal meurt de faim
	bool meurt() const;

	//* Est-ce que l’animal se reproduit
	bool seReproduit(Ensemble voisins_vides, float proba_birth_lapin, float proba_birth_renard) const;

	//* L’animal se nourrit
	void mange();

	//* L’animal ne mange pas
	void jeune();

	private :

	//* L'espèce de l'animal
	Espece esp;

	//* L'identifiant de l'animal
	int id;

	//* Les coordonnées de l'animal
	Coord coord;

	//* La nourriture de l'animal
	int nourriture;
};

//Opérateur d'affichage d'une espèce
ostream& operator<<(ostream& out, const Espece &esp);

#endif