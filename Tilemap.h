#pragma once

class Tilemap 
{
	public:
		Tilemap(int dim);
		~Tilemap();
		
		void loadTileSet();
		std::vector<sf::Sprite> loadLayer(int dim, std::string s);
		sf::Sprite loadTile(int dim, int i);
		std::vector<int> split(std::string s);

		void drawTilemap(sf::RenderWindow& rw);

	protected:
		sf::Texture mapTexture;

		std::vector<sf::Vector2i> tileOffsets;

		std::vector<sf::Sprite> grassLayer;
		std::vector<sf::Sprite> groundLayer;
		std::vector<sf::Sprite> worldLayer;
		std::vector<sf::Sprite> elements1Layer;
		std::vector<sf::Sprite> treesLayer;
		std::vector<sf::Sprite> elements2Layer;
};
