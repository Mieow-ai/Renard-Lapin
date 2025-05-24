#include <iostream>
#include <iomanip> 
#include <sstream> 
#include <fstream>
#include <string>
#include "jeu.hpp"
#include "grille.hpp"
#include "population.hpp"
#include "animal.hpp"
#include "coord.hpp"
#include "ppm.hpp"

using namespace std;

int compteurFichier = 0;

void dessinerGrille(Jeu jeu_actuel){
	int r, g, b;
	ostringstream filename;
	filename << "img" << setfill('0') << setw(3) << compteurFichier << ".ppm";
	compteurFichier++;
	cout << "Ecriture dans le fichier : " << filename.str() << endl;
	ofstream fic(filename.str(), ios::out | ios::trunc);
	fic << "P3" << endl
	<< 40 << " " << 40 << " " << endl
	<< 255 << " " << endl;
	for (int i = 0;i<TAILLEGRILLE;i++){
		for (int j = 0;j<TAILLEGRILLE;j++){
			int id = jeu_actuel.getCase(Coord(i, j));
			Animal a = jeu_actuel.getPop().get(id);
			if(a.getEspece() == Espece::lapin){
				r = 0; g = 0; b = 255;
			}else if(a.getEspece() == Espece::renard){
				r = 255; g = 0; b = 0;
			}else{
				r = 255; g = 255; b = 255;
			}
			fic << r << " " << g << " " << b << " ";
		}
		fic << endl;
	}
	fic.close();
}