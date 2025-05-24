CXX = clang++  # Compilateur
CXXFLAGS = -Wall -std=c++17  # Options de compilation
LDFLAGS= # Lien de base
LDFLAGSFML = -lsfml-graphics -lsfml-window -lsfml-system  # Bibliothèques SFML
EXEC_FILES = main tests  # Executables à générer

all: main

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

tests: test.o coord.o Ensemble.o animal.o population.o grille.o jeu.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main: main.o coord.o Ensemble.o animal.o population.o grille.o jeu.o ppm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

sfml: mainsfml.o coord.o Ensemble.o animal.o population.o grille.o jeu.o ppm.o sfml.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGSFML)

clean:
	rm -f *.o $(EXEC_FILES) *.ppm movie.gif *.csv

gif: img*.ppm
	convert -scale 300 -delay 10 img*.ppm movie.gif