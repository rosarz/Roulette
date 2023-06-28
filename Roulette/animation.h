#pragma once
#include <SFML/Graphics.hpp>

class animation
{
public: 
	animation();
	animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~animation(); 

	void update(int row, float deltaTime); 

	sf::IntRect uvRect; 

private:
	sf::Vector2u imageCount; 
	sf::Vector2u currentImage; 

	float totalTime; 
	float switchTime; 
};

