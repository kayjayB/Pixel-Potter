#ifndef PLAYER_H
#define PLAYER_H
#include "animation.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "math.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const double pi = M_PI;
const int x=0;
const int y=1;

using floatVector =std::vector <float> ;

class Player
{
public:
	//PlayerRefactored(sf::Texture* texture);
	Player();
	~Player();
	void Update();
	void Draw(sf::RenderWindow& window);

private:

sf::Texture _playerTexture;
sf::RectangleShape _body;
unsigned int _row;
const float _switchTime=0.3f;
const float _speed = 0.9f;
bool _faceRight;
double _theta;
const double _x_center=1920.0f/2.0f;
const double _y_center=1080.0f/2.0f;
const double _radius =480.0f;
const double _speedFactor=0.0025;
const sf::Vector2u _imageCount;
//animation _playerAnimation;
//playerMovement _harryMovement;
floatVector calculatePosition(const bool &direction, float factor);
floatVector getPostition();
void setTexture();
};


#endif // PLAYERREFACTORED_H
