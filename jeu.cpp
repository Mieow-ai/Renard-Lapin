#include "jeu.hpp"
#include "animal.hpp"
#include "coord.hpp"
#include "doctest.h"
#include<iostream>
#include <sstream>
#include <array>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

//FONCTIONS UTILITAIRES//

void CSV(const vector<int> &lapins, const vector<int> &renards) {
    ofstream fichier("evolutions.csv");
    fichier << "Tours,Lapins,Renards\n";
    for (int i = 0;i<lapins.size();i++) {
        fichier << i << "," << lapins[i] << "," << renards[i] << "\n";
    }
    fichier.close();
}

//DANS LA CLASSE JEU//

Jeu::Jeu(float probLapins, float probRenard) : grille{Grille()}, pop{Population()}, tour{0} {
    int nbLapins = int(probLapins * MAXCARD);
    int nbRenards = int(probRenard * MAXCARD);
    vector<Coord> coordonnees;
    for (int i = 0; i < TAILLEGRILLE; ++i) {
        for (int j = 0; j < TAILLEGRILLE; ++j) {
            coordonnees.push_back(Coord(i, j));
        }
    }
    random_shuffle(coordonnees.begin(), coordonnees.end());
    for (int i = 0;i<nbLapins;i++) {
        Coord c = coordonnees[i];
        Animal a(c.toInt(), Espece::lapin, c);
        grille.setCase(a);
        pop.ajoute(a);
    }
    for (int j = nbLapins;j<nbLapins+nbRenards;j++) {
        Coord c = coordonnees[j];
        Animal a(c.toInt(), Espece::renard, c);
        grille.setCase(a);
        pop.ajoute(a);
    }
}

ostream& Jeu::affiche(ostream& out) const {
	for(int i = 0; i < TAILLEGRILLE; i++) {
		for(int j = 0; j < TAILLEGRILLE; j++) {
			out << "|";
			int id = grille.getCase(Coord(i, j));
			if (id == -1) {
				out << " ";
			} else {
				Espece esp = pop.get(id).getEspece();
				if (esp == Espece::renard) {
					out << "R";
				} else if (esp == Espece::lapin) {
					out << "L";
				}
			}
		}
		out << "|" << endl;
	}
	return out;
}

ostream& Jeu::loop(ostream& out){
	tour++;
	cout << "---------------------------------" << endl;
	out << "Tour : " << tour << endl;
	cout << "---------------------------------" << endl;
	return out;
}

void Jeu::ajouteAnimal(Coord coord, Espece esp){
	int id = coord.toInt();
	if(grille.getCase(coord) != -1){
		throw invalid_argument("Il y a déjà un animal dans cette case");
	}
	Animal a = Animal(id, esp, coord);
	grille.setCase(a);
	pop.ajoute(a);
}



bool Jeu::verifieGrille() const{
	Ensemble ids = pop.getIds();
	for(int i = 0;i<ids.cardinal();i++){
		int id = ids.tire();
		Animal a = pop.get(id);
		Coord c = a.getCoord();
		if(id != grille.getCase(c)){
			return false;
		}
	}
	if(grille.getCase(Coord(pop.reserve())) != -1){
		return false;                                //Cas limite
	}
	return true;	
}

Ensemble Jeu::voisinsVides(Coord coord) const{
	Ensemble voisins = coord.voisines();
	Ensemble res;
	int cardinal = voisins.cardinal();
	for(int i = 0;i<cardinal;i++){
		Coord voisin = Coord(voisins.tire());
		if(grille.getCase(voisin) == - 1){
			res.ajoute(voisin.toInt());
		}
	}
	return res;
}

Ensemble Jeu::voisins(Coord coord) const {
	return coord.voisines();
}

int Jeu::getCase(Coord coord) const{
	return grille.getCase(coord);
}

Ensemble Jeu::voisinsEspece(Espece e, Coord coord) const{
	Ensemble voisins = coord.voisines();
	Ensemble res;
	int cardinal = voisins.cardinal();
	for(int i = 0;i<cardinal;i++){
		Coord voisin = Coord(voisins.tire());
		if(pop.get(grille.getCase(voisin)).getEspece() == e){
			res.ajoute(voisin.toInt());
		}
	}
	return res;
}

void Jeu::deplace(int id){
	Animal a = pop.get(id);
	if(a.getId() == -1) throw invalid_argument("L'animal n'existe pas dans la population");
	Coord init = a.getCoord();
	Ensemble voisinsv = voisinsVides(init);
	if(voisinsv.cardinal() == 0) return;
	Coord newCoord = Coord(voisinsv.tire());
	a.setCoord(newCoord);
	grille.videCase(init);
	grille.setCase(a);
	pop.supprime(id);
	pop.set(a);
}

Ensemble Jeu::getIds() const{
	return pop.getIds();
}

void Jeu::coherence() const{
	Ensemble ids = pop.getIds();
	for(int i = 0;i<ids.cardinal();i++){
		int id1 = ids.tire();
		Animal a = pop.get(id1);
		Coord c = a.getCoord();
		int idGrille = grille.getCase(c);
		if(idGrille != id1){
			cout << "L'animal " << id1 << " pense être à (" << c.get_lig() << ", " << c.get_col() << ") mais la grille n'a pas cet identifiant à cet endroit " << endl;
			throw runtime_error("Incohérence animal-grille");
		}
	}
	for(int j = 0;j<TAILLEGRILLE;j++){
		for(int k = 0;k<TAILLEGRILLE;k++){
			Coord coord = Coord(j, k);
			int id2 = grille.getCase(coord);
			if(id2 != -1){
				if(pop.get(id2).getId() == -1){
					cout << "La grille contient un animal à (" << j << ", " << k << ") mais il n'existe pas dans la population" << endl;
					throw runtime_error("Incohérence grille-population");
				}
				Animal b = pop.get(id2);
				if(not(b.getCoord() == coord)){
					cout << "La grille dit que l'animal est à (" << j << ", " << k << ") mais cet animal pense être à (" << b.getCoord().get_lig() << ", " << b.getCoord().get_col() << ")" << endl;
					throw runtime_error("Incohérence grille-animal");
				}
			}
		}
	}
}

void Jeu::deplacement_aleatoire(){
	Ensemble ids = pop.getIds();
	for(int i = 0;i<ids.cardinal();i++){
		int id = ids.tire();
		deplace(id);
	}
	loop(cout);
}

void Jeu::deplacements_lapins(float proba_birth, int &pop_lapin, bool sfml){
    Ensemble ids = pop.getIds();
    vector<int> lapins;
	int card = ids.cardinal();
	int compteur = 0;
    for(int i = 0;i<card; i++) {
        int id = ids.tire();
        if(pop.get(id).getEspece() == Espece::lapin) {
            lapins.push_back(id);
        }
    }
	int card_tot = lapins.size();
	pop_lapin = card_tot;
	if(not(sfml)){
		cout << "------------------------------------------" << endl;
		cout << "Nombre de lapins avant déplacements : " << card_tot << endl;
	}
    for(int id : lapins) {
		Animal lapin_avant = pop.get(id);
		Coord avant = lapin_avant.getCoord();
		Ensemble voisins_vides = voisinsVides(avant);
        deplace(id);
		if(lapin_avant.seReproduit(voisins_vides, proba_birth, 0.)){
			Animal nouveau_lapin = Animal(pop.reserve(), Espece::lapin, avant);
			grille.setCase(nouveau_lapin);
			pop.set(nouveau_lapin);
			compteur++;
		}
    }
	if(not(sfml)){
		cout << "Nombre de lapins nés : " << compteur << endl;
		cout << "------------------------------------------" << endl;
	}
}

void Jeu::deplacements_renards(float proba_birth, int &pop_renard, bool sfml) {
    Ensemble ids = pop.getIds();
    vector<int> renards;
	int lapins_morts = 0;
	int renards_nes = 0;
	int renards_morts = 0;
    int card = ids.cardinal();
    for (int i = 0; i < card; i++) {
        int id = ids.tire();
        if (pop.get(id).getEspece() == Espece::renard) {
            renards.push_back(id);
        }
    }
	int renards_size = renards.size();
	pop_renard = renards_size;
	if(not(sfml)){
		cout << "------------------------------------------" << endl;
		cout << "Nombre de Renards avant déplacements : " << renards_size << endl;
	}
    for (int id : renards) {
        if (pop.get(id).getId() == -1) continue;
        Animal a = pop.get(id);
        Coord init = a.getCoord();
        Ensemble voisins_Lapins = voisinsEspece(Espece::lapin, init);
        int card_Lapins = voisins_Lapins.cardinal();
        if (card_Lapins > 0) {
            Coord cible = Coord(voisins_Lapins.tire());
            int id_Lapin = grille.getCase(cible);
            if (id_Lapin != -1 && pop.get(id_Lapin).getEspece() == Espece::lapin) {
                grille.videCase(init);
                grille.videCase(cible);
                a.setCoord(cible);
                a.mange();
                grille.setCase(a);
                pop.supprime(id_Lapin);
                pop.supprime(id);
                pop.set(a);
				lapins_morts++;
				if(a.seReproduit(Ensemble(), 0., proba_birth)){
					Animal nouveau_renard = Animal(pop.reserve(), Espece::renard, init);
					grille.setCase(nouveau_renard);
					pop.set(nouveau_renard);
					renards_nes++;
				}
                continue;
            }
        }
        deplace(id);
		// le même renard mais après déplacement
		Animal b = pop.get(id);
		b.jeune();
		if (b.meurt()) {
		    grille.videCase(b.getCoord());
		    pop.supprime(id);
			renards_morts++;
		} else {
			pop.supprime(id);
		    pop.set(b);
			if(b.seReproduit(Ensemble(), 0., proba_birth)){
				Animal nouveau_renard = Animal(pop.reserve(), Espece::renard, init);
				grille.setCase(nouveau_renard);
				pop.set(nouveau_renard);
				renards_nes++;
			}
		}
    }
	if(not(sfml)){
		cout << "Nombre de lapin morts : " << lapins_morts << endl;
		cout << "Nombre de renards nés : " << renards_nes << endl;
		cout << "Nombre de renards morts : " << renards_morts << endl;
		cout << "------------------------------------------" << endl;
	}
}

Population Jeu::getPop() const{
	return pop;
}

int Jeu::get_tour() const{
	return tour;
}


//TESTS pour jeu.cpp

TEST_CASE("Test pour le constructeur par défault jeu et la méthode affiche()"){
	cout << "------------------------------------------" << endl;

	cout << "Lancement des tests pour la class jeu.." <<endl;

	cout << "------------------------------------------" << endl;
	cout << "Test pour le constructeur par défault jeu et la méthode affiche()..." << endl;
	Jeu jeu = Jeu(0.20, 0.07);
	jeu.affiche(cout);
}

TEST_CASE("Test pour la méthode ajouteAnimal()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode ajouteAnimal()..." << endl;
	Jeu jeu = Jeu();
	jeu.affiche(cout);
	cout << " " << endl;
	jeu.ajouteAnimal(Coord(12, 2), Espece::lapin);
	jeu.ajouteAnimal(Coord(10, 2), Espece::renard);
	jeu.ajouteAnimal(Coord(1, 1), Espece::renard);
	cout << "Affichage de la grille après ajouts d'animaux" << endl;
	jeu.affiche(cout);
}

TEST_CASE("Test pour la méthode vérifieGrille()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode vérifieGrille()..." << endl;
	Jeu jeu = Jeu(0.20, 0.07);
	CHECK(jeu.verifieGrille());
}

TEST_CASE("Test pour la méthode voisinsVides() et voisinsEspece"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode voisinsVides()..." << endl;
	Jeu jeu = Jeu(0.20, 0.07);
	jeu.affiche(cout);
	Ensemble voisins_1 = jeu.voisins(Coord(0, 2));
	Ensemble voisins_vides1 = jeu.voisinsVides(Coord(0, 2));
	cout << "Nombre de voisins vides trouvés au point de coordonnées (0, 2): " << voisins_vides1.cardinal() << endl;
	cout << "Ensemble voisins trouvés au point de coordonnées (0, 2) " << voisins_1 <<endl;
	cout << "Ensemble voisins vides trouvés au point de coordonnées (0, 2) " << voisins_vides1 <<endl;
	cout << "Contenu de (0,1) : " << jeu.getCase(Coord(1)) << endl;
	cout << "Contenu de (0,3) : " << jeu.getCase(Coord(3)) << endl;
	cout << "Contenu de (1,1) : " << jeu.getCase(Coord(41)) << endl;
	cout << "Contenu de (1,2) : " << jeu.getCase(Coord(42)) << endl;
	cout << "Contenu de (1,3) : " << jeu.getCase(Coord(43)) << endl;
	Ensemble voisins_2 = jeu.voisinsVides(Coord(15, 5));
	cout << "Nombre de voisins vides trouvés au point de coordonnées (15, 5): " << voisins_2.cardinal() << endl;
	Ensemble voisins_3 = jeu.voisinsVides(Coord(8, 2));
	cout << "Nombre de voisins vides trouvés au point de coordonnées (8, 2): " << voisins_3.cardinal() << endl;

	Ensemble voisins_renard = jeu.voisinsEspece(Espece::renard, Coord(3, 11));
	Ensemble voisins_4 = jeu.voisins(Coord(3, 11));
	cout << "Nombre de voisins renard trouvés au point de coordonnées (3, 11): " << voisins_renard.cardinal() << endl;
	cout << "Ensemble voisins trouvés au point de coordonnées (3, 11) " << voisins_4 <<endl;
	cout << "Ensemble voisins renard trouvés au point de coordonnées (3, 11) " << voisins_renard <<endl;

	Ensemble voisins_lapin = jeu.voisinsEspece(Espece::lapin, Coord(3, 11));
	cout << "Nombre de voisins lapin trouvés au point de coordonnées (3, 11): " << voisins_lapin.cardinal() << endl;
	cout << "Ensemble voisins trouvés au point de coordonnées (3, 11) " << voisins_4 <<endl;
	cout << "Ensemble voisins lapin trouvés au point de coordonnées (3, 11) " << voisins_lapin <<endl;

}

TEST_CASE("Test pour la méthode deplace() dans Jeu"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode deplace() dans Jeu..." << endl;
	Jeu jeu = Jeu(0.20, 0.07);
	jeu.affiche(cout);
	Ensemble Ids = jeu.getIds();
	int id = Ids.tire();
	Coord coord = Coord(id);
	cout <<"L'animal déplacé est en : "<< coord << endl;
	jeu.deplace(id);
	CHECK_THROWS_AS(jeu.deplace(3), invalid_argument);
	coord = Coord(3);
	cout <<"L'animal déplacé est en : "<< coord << endl;
	jeu.deplace(4);
	coord = Coord(4);
	cout <<"L'animal déplacé est en : "<< coord << endl;
	jeu.affiche(cout);
}

TEST_CASE("Test de la cohérence de la grille"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode coherence()..." << endl;
	Jeu jeu = Jeu(0.20, 0.07);
	jeu.affiche(cout);
	jeu.coherence();
	cout << "La cohérence est vérifiée" << endl;
}

TEST_CASE("Test pour la méthode deplacement_aleatoire()"){
	cout << "------------------------------------------" << endl;
	cout << "Test pour la méthode deplacement_aleatoire()..." << endl;
	Jeu jeu = Jeu(0.20, 0.07);
	jeu.affiche(cout);
	Ensemble popu = jeu.getPop().getIds();
	jeu.deplacement_aleatoire();
	Ensemble popu2 = jeu.getPop().getIds();
	jeu.affiche(cout);
	CHECK(popu.cardinal() == popu2.cardinal());
	
}
