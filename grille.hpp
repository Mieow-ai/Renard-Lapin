#ifndef GRILLE
#define GRILLE

#include<iostream>
#include <sstream>
#include <array>
#include "animal.hpp"
#include "Ensemble.hpp"
#include "coord.hpp"
#include "population.hpp"

using namespace std;

class Grille{
	

	public:

	//* Constructeur par défault
	Grille();

	//* Renvoie l’identifiant de l’animal qui est dans la grille à des coordonnées données
	int getCase(Coord coord) const;

	//* Renvoie true ou false selon que la case est vide ou non
	bool caseVide(Coord coord) const;

	//* Vide une case connaissant ses coordonnées
	void videCase(Coord coord);

	//* Range l'identifiant d'un animal dans la case de ses coordonnées
	void setCase(Animal a);

	private:

	//* La grille
	array<array<int, TAILLEGRILLE>, TAILLEGRILLE> grille;

};

#endif