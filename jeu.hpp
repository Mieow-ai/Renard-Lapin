#ifndef JEU
#define JEU

#include<iostream>
#include <sstream>
#include <array>
#include "animal.hpp"
#include "Ensemble.hpp"
#include "coord.hpp"
#include "population.hpp"
#include "grille.hpp"
using namespace std;

class Jeu{

	public:

	//* Constructeur par défault
	Jeu() : grille{Grille()}, pop{Population()}, tour{0} {}

	//* Constructeur à partir d'une proportion de lapins et de Renards
	Jeu(float probLapins, float probRenard);

	//* Affiche le jeu
	ostream& affiche(ostream& out) const;

	//* Rajoute un tour et affiche le tour auquel on est
	ostream& loop(ostream& out);

	//* Crée un nouvel animal et le place dans la grille
	void ajouteAnimal(Coord coord, Espece esp);

	//* Qui vérifie que chaque animal est bien à sa place dans la grille
	bool verifieGrille() const;

	//* Qui retourne l’ensemble des cases voisines d’une case
	Ensemble voisins(Coord coord) const;


	//* Qui retourne l’ensemble des cases voisines vides d’une case
	Ensemble voisinsVides(Coord coord) const;

	//* Qui retourne l’ensemble des cases voisines contenant une espèce donnée autour d'une case
	Ensemble voisinsEspece(Espece e, Coord coord) const;

	//* Obtiens l'ensemble des identifiants du jeu
	Ensemble getIds() const;

	//* Renvoi la population actuelle du jeu
	Population getPop() const;

	//* Déplace l’animal sur une case voisine libre et le range dans la grille
	void deplace(int id);

	//* Renvoi l'indice d'une case
	int getCase(Coord coord) const;

	//* Vérifie la cohérence du jeu
	void coherence() const;

	//* Fonction qui déplace aléatoirement les animaux
	void deplacement_aleatoire();

	//* Fonction qui déplace les lapins
	void deplacements_lapins(float proba_birth, int &lapin_size, bool sfml);

	//* Fonction qui déplace les renards
	void deplacements_renards(float proba_birth, int &renard_size, bool sfml);

	//* Getter pour le nombre de tour
	int get_tour() const;

	private:

	//* La grille du jeu
	Grille grille;

	//* La population du jeu
	Population pop;

	//* stock le numéro du tour
	int tour;

};

//* Fonction qui créer un fichier csv avec l'évolution des populations
void CSV(const vector<int> &lapins, const vector<int> &renards);

#endif