#ifndef COORD
#define COORD

#include<iostream>
#include <sstream>
#include <array>
#include "Ensemble.hpp"

using namespace std;

class Coord {

	public:

		// CONSTRUCTEURS

		//* Constructeur à partir d'un numéro de ligne et de colonne
		Coord(int lig, int col);

		//* Constructeur à partir d'un entier
		Coord(int b);

		// MÉTHODES

		//* Renvoi la ligne du point de coordonnées
		int get_lig() const;

		//* Renvoi la colonne du point de coordonnées
		int get_col() const;

		//* Renvoi la ligne et la colonne du point de coordonnées
		pair<int, int> get_coord() const;

		//* Renvoi l'entier associé de la paire de coordonnées
		int toInt() const;

		//* méthode voisines qui renvoi l'ensemble des cases voisines
		Ensemble voisines() const;

	private:

		//* Numéro de ligne
		int lig;
		//* Numéro de colonne
		int col;
};

//*Opérateur d'affichage des coordonnées d'un point
ostream& operator<<(ostream &out, Coord &point);

//*Opérateur d'égalité des coordonnées d'un point
bool operator==(const Coord &a, const Coord &b);

//*Opérateur d'inégalité des coordonnées d'un point
bool operator!=(const Coord &a, const Coord &b);

//*Fonction qui renvoi le maximum entre deux entiers
int max(int a, int b);

//*Fonction qui renvoi le maximum entre deux entiers
int min(int a, int b);


#endif
