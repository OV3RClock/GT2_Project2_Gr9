#pragma once

class Tilemap {

	public:
		std::vector<sf::Sprite> loadLevel(sf::Texture &t);
		sf::Sprite loadtile(std::string s, sf::Texture& t);

	protected:
		std::vector<sf::Sprite> Tiles;
};