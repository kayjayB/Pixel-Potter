#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

class animation
{
public:
	animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~animation();
	
	void Update(int row, float deltaTime, bool faceRight);
	
	sf::IntRect textureRect;
	
private:
	sf::Vector2u _imageCount;
	sf::Vector2u _currentImage;
	
	// timing variables
	float _totalTime;
	float _switchTime;

};

#endif // ANIMATION_H
