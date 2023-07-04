#include "animation.h"

animation::animation()
{
}

animation::animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage.x; 

	uvRect.width = texture->getSize().x / float(imageCount.x)+1; 
	uvRect.height = texture->getSize().y / float(imageCount.y)+1; 
}

animation::~animation()
{
}

void animation::update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) 
	{
		totalTime -= switchTime; 
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0; 
		}
	}
	uvRect.left = currentImage.x * uvRect.width; 
	uvRect.top = currentImage.y * uvRect.height; 
}

