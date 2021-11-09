#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
	public:

	protected:
		int nbFrames = 3;
		float holdTime = 0.1f;
		float time = 0.0f;
		int iFrame = 0;
		//sf::IntRect frames[nbFrames];
		sf::Texture texture;
		
};