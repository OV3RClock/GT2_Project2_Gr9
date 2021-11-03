#pragma once

class Tilemap {

	public:
		sf::Sprite loadLevel(sf::Texture &t);

	protected:
		std::vector<sf::Sprite> Tiles;
};