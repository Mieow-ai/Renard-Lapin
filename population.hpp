#ifndef POPULATION
#define POPULATION

#include<iostream>
#include<vector>
#include <sstream>
#include <array>
#include "animal.hpp"
#include "Ensemble.hpp"
#include "coord.hpp"

using namespace std;

class Population{


	public:

	//CONSTRUCTEURS

	//* Créer une population vide
	Population();

	//MÉTHODES

	//* Renvoie l’animal ayant un identifiant donné
	Animal get(int id) const;

	//* Renvoie l’ensemble de tous les identifiants d’une population
	Ensemble getIds() const;

	//* Réserve un identifiant non déjà existant pour un nouvel animal
	int reserve() const;

	//* Range un animal dans la population
	void set(Animal a);

	//* Supprime un animal de la population connaissant son identifiant
	void supprime(int id);

	//* Ajoute un animal à la population
	void ajoute(Animal a);

	private:

	//* L'ensemble de la population
	vector<Animal> animaux;
};

#endif