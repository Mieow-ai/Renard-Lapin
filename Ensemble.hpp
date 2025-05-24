#ifndef ENSEMBLE
#define ENSEMBLE

#include<iostream>
#include <sstream>
#include <array>

using namespace std;

const int TAILLEGRILLE = 40;

const int MAXCARD = 1600;

using Objet = int;

class Ensemble{

	public:

	//CONSTRUCTEURS

	Ensemble() : ens{{}}, card{0} {}

	//MÉTHODES

	//* méthode affiche() qui affiche l'ensemble
	ostream& affiche(ostream& out) const;

	//* méthode estVide() qui dit si un ensemble est vide ou non
	bool estVide() const;

	//* méthode cardinal() qui renvoi le cardinal de l'ensemble
	int cardinal() const;

	//* méthode ajoute(Objet a) qui ajoute un Objet à un ensemble
	void ajoute(Objet a);

	//* méthode qui tire au hasard un Objet de l'ensemble et le retire
	Objet tire();

	private:

	//* array représentant l'ensemble de taille constante
	array<Objet, MAXCARD> ens;

	//* le nombre d’éléments présents dans l’ensemble
	int card;

};

//*Opérateur d'affichage pour un Ensemble
ostream& operator<<(ostream &out, Ensemble &e);

#endif