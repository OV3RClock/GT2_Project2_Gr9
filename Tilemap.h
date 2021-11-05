#pragma once

class Tilemap {

	public:
		std::vector<sf::Sprite> loadLevel(int dim, int scale, sf::Texture &t);
		std::vector<sf::Sprite> loadGround(int dim, int scale, sf::Texture& t);

		sf::Sprite loadtile(int dim, int scale, std::string s, sf::Texture& t);

	protected:
		std::vector<sf::Sprite> Tiles;
		std::vector<sf::Sprite> Ground;
};
