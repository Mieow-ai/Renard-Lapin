#include <sstream> 
#include <string>
#include <SFML/Graphics.hpp>
#include "jeu.hpp"
#include "grille.hpp"
#include "population.hpp"
#include "animal.hpp"
#include "coord.hpp"
#include "sfml.hpp"


using namespace std;

void game(float prop_lapin, float prop_renard, float proba_birth_lapin, float proba_birth_renard){
	int a;
	int b;
	sf::Texture textureLapin;
    if (!textureLapin.loadFromFile("lapin.png")) {
        cerr << "Erreur de chargement de lapin.png!" << endl;
        return;
    }

    sf::Texture textureRenard;
    if (!textureRenard.loadFromFile("renard.png")) {
        cerr << "Erreur de chargement de renard.png!" << endl;
        return;
    }

	Jeu jeu = Jeu(prop_lapin, prop_renard);
    sf::RenderWindow window(sf::VideoMode(720, 720), "Simulation Lapin-renard");
    int taille_case = 720 / TAILLEGRILLE;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        jeu.deplacements_lapins(proba_birth_lapin, a, true);
		jeu.deplacements_renards(proba_birth_renard, b, true);
        window.clear(sf::Color::White);
        for (int i = 0; i < TAILLEGRILLE; i++) {
            for (int j = 0; j < TAILLEGRILLE; j++) {
                int id = jeu.getCase(Coord(i, j));
                Animal a = jeu.getPop().get(id);
				sf::Sprite sprite;
                if(a.getEspece() == Espece::lapin) {
                    sprite.setTexture(textureLapin);
                } else if(a.getEspece() == Espece::renard) {
                    sprite.setTexture(textureRenard);
                } else {
					continue;
                }
                float scale_x = static_cast<float>(taille_case) / sprite.getTexture()->getSize().x;
                float scale_y = static_cast<float>(taille_case) / sprite.getTexture()->getSize().y;
                sprite.setScale(scale_x, scale_y);

                // Placer le sprite dans la case (i, j)
                sprite.setPosition(i * taille_case, j * taille_case);

                // Dessiner le sprite sur la fenêtre
                window.draw(sprite);
            }
        }
        window.display();
    }
}