#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "coord.hpp"
#include "Ensemble.hpp"
#include "animal.hpp"
#include "population.hpp"
#include "grille.hpp"
#include "jeu.hpp"
#include "ppm.hpp"
#include "sfml.hpp"
#include<iostream>

using namespace std;


int main(int argc, const char **argv) {
    doctest::Context context(argc, argv);
    int test_result = context.run();
	vector<int> evolution_renards;
	vector<int> evolution_lapins;
	vector<int> tours;
	int lapin_size = 0;
	int renard_size = 0;
    if (context.shouldExit()) return test_result;
	cout << "---------------------------------" << endl;
    cout << "//////////DÉBUT DU MAIN//////////" << endl;
	cout << " " << endl;
	float prop_lapin, prop_renard;
	float proba_birth_lapin, proba_birth_renard;
	do {
		cout << "Veuillez choisir la proportion de lapin que vous voulez (recommandé 0.20) : ";
		cin >> prop_lapin;
		if(prop_lapin <= 0 || prop_lapin >= 1){
			cout << "Ce n'est pas une proportion valable, veuillez réessayer ! " << endl;
		}
	} while(prop_lapin <= 0 || prop_lapin >= 1);
	
	do {
		cout << "Veuillez choisir la proportion de renard que vous voulez (recommandé 0.07) : ";
		cin >> prop_renard;
		if(prop_renard <= 0 || prop_renard >= 1){
			cout << "Ce n'est pas une proportion valable, veuillez réessayer ! " << endl;
		}
	} while(prop_renard <= 0 || prop_renard >= 1);

	do {
		cout << "Veuillez choisir la probabilité de naissance des lapins que vous voulez (recommandé 0.15) : ";
		cin >> proba_birth_lapin;
		if(proba_birth_lapin <= 0 || proba_birth_lapin >= 1){
			cout << "Ce n'est pas une probabilité valable, veuillez réessayer ! " << endl;
		}
	} while(proba_birth_lapin <= 0 || proba_birth_lapin >= 1);

	do {
		cout << "Veuillez choisir la probabilité de naissance des renards que vous voulez (recommandé 0.05) : ";
		cin >> proba_birth_renard;
		if(proba_birth_renard <= 0 || proba_birth_renard >= 1){
			cout << "Ce n'est pas une probabilité valable, veuillez réessayer ! " << endl;
		}
	} while(proba_birth_renard <= 0 || proba_birth_renard >= 1);
	
	Jeu jeu = Jeu(prop_lapin, prop_renard);
	cout << "INITIALISATION DU JEU" << endl;
	cout << "Tour : 0" << endl;
	jeu.affiche(cout);
	for(int i = 0;i<30;i++){
		lapin_size = 0;
		renard_size = 0;
		jeu.loop(cout);
		jeu.deplacements_lapins(proba_birth_lapin, lapin_size, false);
		evolution_lapins.push_back(lapin_size);
		cout << "---------------------------------" << endl;
		cout << "AFFICHAGE DU JEU APRÈS LE DÉPLACEMENT DES LAPINS" << endl;
		cout << "---------------------------------" << endl;
		jeu.affiche(cout);
		dessinerGrille(jeu);
		jeu.deplacements_renards(proba_birth_renard, renard_size, false);
		evolution_renards.push_back(renard_size);
		cout << "---------------------------------" << endl;
		cout << "AFFICHAGE DU JEU APRÈS LE DÉPLACEMENT DES RENARDS" << endl;
		cout << "---------------------------------" << endl;
		jeu.affiche(cout);
		dessinerGrille(jeu);
	}
	cout << "---------------------------------" << endl;
	cout << "Évolution de la population des lapins au fil des tours : ";
	cout << "[";
	for(int k = 0;k<evolution_lapins.size() - 1;k++){
		cout << evolution_lapins[k] << ", ";
	}
	cout << evolution_lapins[evolution_lapins.size() - 1] << "]" << endl;
	cout << "---------------------------------" << endl;
	cout << "Évolution de la population des renards au fil des tours : ";
	cout << "[";
	for(int l = 0;l<evolution_renards.size() - 1;l++){
		cout << evolution_renards[l] << ", ";
	}
	cout << evolution_renards[evolution_renards.size() - 1] << "]" << endl;
	cout << "---------------------------------" << endl;
	for(int n = 1;n<jeu.get_tour();n++){
		tours.push_back(n);
	}
	CSV(evolution_lapins, evolution_renards);
    return 0;
}