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
	float switchTime;
	float totalTime;

	sf::Vector2u imageCount; 
	sf::Vector2u currentImage; 

private:
	
};

/*void player::deleteSaveFile(const std::string filename)
{
	std::filesystem::path filePath(filename);

	if (std::filesystem::exists(filePath))
	{
		std::filesystem::remove(filePath);
		std::cout << "Zapis gry usuniêty: " << filename << std::endl;
	}
	else
	{
		std::cout << "Nie mo¿na odnaleŸæ zapisu gry: " << filename << std::endl;
	}
}*/
