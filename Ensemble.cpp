#include "doctest.h"
#include "coord.hpp"
#include "Ensemble.hpp"
#include<stdexcept>
#include<iostream>

using namespace std;

//OPÉRATEURS

ostream& operator<<(ostream &out, Ensemble &e){
	return e.affiche(out);
}

//MÉTHODES

ostream& Ensemble::affiche(ostream& out) const{
	if (card == 0) {
		out << "{}" << endl;
		return out;
	}
	out << "{";
	for(int i = 0;i<card - 1;i++){
	out << ens[i] << ", ";
	}
	out << ens[card - 1] << "}" << endl;
	return out;
}

bool Ensemble::estVide() const{
	return card == 0;
}

int Ensemble::cardinal() const{
	return card;
}

void Ensemble::ajoute(Objet a){
	if(card == MAXCARD) throw invalid_argument("L'ensemble est déjà rempli");
	ens[card] = a;
	card++;
}

Objet Ensemble::tire(){
	if(card == 0) throw invalid_argument("L'ensemble est vide");
	int random = rand() % card;
	Objet retirer = ens[random];
	for(int i = random;i<card - 1;i++){
		ens[i] = ens[i + 1];
	}
	card--;
	return retirer;
}

//TESTS

TEST_CASE("Test pour l'opérateur d'afffichage la class Ensemble"){
	cout << " " << endl;
	cout << " " << endl;
	cout << "------------------------------------------" << endl;

	cout << "Lancement des tests pour la class Ensemble.." << endl;

	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour l'affichage de la class Ensemble.." << endl;
	GIVEN("On créer notre ensemble de test"){
		Ensemble test = Ensemble();
		WHEN("Ce que l'on doit obtenir"){
			cout << "Affichage des coordonnées attendues : {}" << endl;
			THEN("On affiche le point de coordonnées et on test si c'est bon"){
				cout << "Affichage grâce à l'opérateur d'affichage : " << test << endl;
			}
		}
	}
}

TEST_CASE("Test pour la méthode ajoute(Objet a) d'un ensemble"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour la méthode ajoute(Objet a).." << endl;
	GIVEN("On créer notre ensemble"){
		Ensemble ens = Ensemble();
		cout << "Affichage avant ajout : " << ens << endl;
		WHEN("On ajoute des éléments"){
			ens.ajoute(2);ens.ajoute(5);ens.ajoute(1);
			THEN("On vérifie si les éléments ont bien été ajoutés"){
				cout << "Affichage après ajout : " << ens << endl;
			}
		}
	}
}

TEST_CASE("Test pour la méthode tire() d'un ensemble"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement du test pour la méthode tire().." << endl;
	GIVEN("On créer notre ensemble"){
		Ensemble ens = Ensemble();
		cout << "Affichage avant ajout : " << ens << endl;
		WHEN("On ajoute des éléments"){
			ens.ajoute(2);ens.ajoute(5);ens.ajoute(1);
			cout << "Affichage après ajout : " << ens << endl;
			THEN("On tire des éléments et vérifie que cela fonctionne"){
				ens.tire();
				cout << "On retire un élément aléatoire : " << ens << endl;
				ens.tire();
				cout << "On retire un élément aléatoire : " << ens << endl;
				ens.tire();
				cout << "On retire un élément aléatoire : " << ens << endl;
				CHECK_THROWS_AS(ens.tire(), invalid_argument);
			}
		}
	}
}