#pragma once

class Tilemap 
{
	public:
		Tilemap(int dim, int scale);
		~Tilemap();
		
		std::vector<sf::Sprite> getVectorTiles();
		std::vector<sf::Sprite> getVectorGround();

		std::vector<sf::Sprite> loadLevel(int dim, int scale, sf::Texture &t);
		std::vector<sf::Sprite> loadGround(int dim, int scale, sf::Texture& t);
		sf::Sprite loadtile(int dim, int scale, std::string s, sf::Texture& t);

		void drawTilemap(sf::RenderWindow& rw);

	protected:
		std::vector<sf::Sprite> vecTiles;
		std::vector<sf::Sprite> vecGround;
		sf::Texture mapTexture;
};
