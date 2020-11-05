#include "class.h"
#include <fstream>

int upgradeMenu(sf::RenderWindow& window) {
	team Player;
	inventory PlayersInventory;
	sf::Sprite Background;
	sf::Texture BackTexture;
	Button itemLife(520, 200, 340, 20);
	Button itemPower(520, 178, 340, 20);
	Button itemSpirit(520, 156, 340, 20);
	Button Exit(520, 134, 340, 20, "Exit");
	BackTexture.loadFromFile("Asset/Upgrade.png");
	Background.setTexture(BackTexture);
	int charNum = 3;
	PlayersInventory.setPosition();
	Player.setFont();
	bool delay = false;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	PlayersInventory.set();
		window.clear();
		if (Player.onMouse(window, 200, -40) != 3)
			charNum = Player.onMouse(window, 200, -40);
		if (itemLife.click(window) == true && charNum != 3 && PlayersInventory.id[0] > 0 && delay == false) {
			Player.health[charNum] += 10;
			PlayersInventory.id[0] -= 1;
			delay = true;
		}
		if (itemPower.click(window) == true && charNum != 3 && PlayersInventory.id[1] > 0 && delay == false) {
			Player.power[charNum] += 10;
			Player.minPower[charNum] += 10;
			PlayersInventory.id[1] -= 1;
			delay = true;
		}
		if (itemSpirit.click(window) == true && charNum != 3 && PlayersInventory.id[2] > 0 && delay == false) {
			Player.spirit[charNum] += 10;
			PlayersInventory.id[2] -= 1;
			delay = true;
		}
		if (itemSpirit.click(window) == false && itemPower.click(window) == false && itemLife.click(window) == false) {
			delay = false;
		}
		if (Exit.click(window) == true) {
			std::ofstream team("Save/TeamStat.save");
			std::ofstream inv("Save/inventory.save");
			for (int i = 0; i < 3; i++) {
				inv << PlayersInventory.id[i] << " ";
				team << Player.health[i] << " " << Player.spirit[i] << " " << Player.power[i] << " " << Player.minPower[i] << " ";
			}
			inv.close();
			team.close();
			return 0;
		}
		window.draw(Background);
		Exit.draw(window);
		PlayersInventory.show(window);
		Player.draw(window);
		Player.fullStat(window);
		window.display();
	}
	return 1;
}