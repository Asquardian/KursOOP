#include "class.h"
#include <fstream>

void upgradeMenu(sf::RenderWindow& window) {
	team Player;
	inventory PlayersInventory;
	sf::Sprite Background;
	sf::Texture BackTexture;
	Button itemLife(520, 200, 340, 20);
	Button itemPower(520, 178, 340, 20);
	Button itemSpirit(520, 156, 340, 20);
	BackTexture.loadFromFile("Asset/Upgrade.png");
	Background.setTexture(BackTexture);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (itemLife.click(window) == true)
			exit(0);
		window.draw(Background);
		PlayersInventory.show(window);
		window.display();
	}
}