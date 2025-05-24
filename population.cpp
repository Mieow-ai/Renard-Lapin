#include "doctest.h"
#include "population.hpp"
#include <exception>

using namespace std;


Population::Population(): animaux({}){}

Animal Population::get(int id) const{
	for(Animal v: animaux){
		if(v.getId() == id){
			return v;
		}
	}
	return Animal();
}


Ensemble Population::getIds() const{
	Ensemble res = Ensemble();
	for(Animal v: animaux){
		res.ajoute(v.getId());
	}
	return res;
}


int Population::reserve() const{
	int ind;
	for(int i =0; i<MAXCARD;i++){
		ind= 0;
		for(Animal an:animaux){
			if(an.getId()==i){
				ind=1;
				break;
			}
		}
		if(ind==1){continue;}
		else return i;
	}
	throw runtime_error("Il n'y a pas assez d'identifiants");
}


void Population::set(Animal a){
	animaux.push_back(a);
}

Population pop_test(){
	Population res = Population();
	res.set(Animal());
	res.set(Animal());
	res.set(Animal());
	res.set(Animal(42, Espece::renard, Coord(42)));
	res.set(Animal());
	return res;
}

void Population::supprime(int id){
	for(int i=0;i<animaux.size();i++){
		if(animaux[i].getId() == id){
			animaux[i] =  animaux[animaux.size()-1];
			animaux.pop_back();
			return;
		}
	}
}

void Population::ajoute(Animal a) {
    animaux.push_back(a);
}

TEST_CASE("get et getIds dans Population"){
	cout << "------------------------------------------" << endl;
	cout << "Lancement des tests pour la class Population.." <<endl;
	cout << "------------------------------------------" << endl;
	cout << "Lancement du Test pour get, getIds, reserve() et supprime() dans Population... " << endl;
	Population test = pop_test();
	Ensemble Ident = test.getIds();
	cout << Ident <<endl;
	test.supprime(42);
	Ident = test.getIds();
	cout << Ident <<endl;
}


