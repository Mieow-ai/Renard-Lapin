#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "sfml.hpp"
#include<iostream>

using namespace std;

int main(){
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

	game(prop_lapin, prop_renard, proba_birth_lapin, proba_birth_renard);
	return 0;
}
