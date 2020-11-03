#include "class.h"
#include <fstream>

void upgradeMenu(sf::RenderWindow& window) {
	team Player;
	inventory PlayersInventory;
	sf::Sprite Background;
	sf::Texture BackTexture;
	BackTexture.loadFromFile("Asset/Upgrade.png");
	Background.setTexture(BackTexture);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.draw(Background);
		PlayersInventory.show(window);
		window.display();
	}
}