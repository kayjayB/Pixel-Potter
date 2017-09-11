#include "Player.h"

Player::Player():
_row{0},
_imageCount(4,4),
_faceRight{true}
{
		srand(time(0));
		float randomAngle=rand()%360; // generate random number between 0 and 360 degrees
		_theta=randomAngle*pi/180;
		_body.setSize(sf::Vector2f(50.0f,100.0f));
		setTexture();
		_body.setOrigin(25.0f,50.0f);
		floatVector initialPosition=getPostition();
		_body.setPosition(initialPosition[x], initialPosition[y]);
}

Player::~Player()
{
}

void Player::Update()
{

	floatVector movement= getPostition();
	float factor = _speed*_speedFactor;
	_row=0;
	bool direction = false;
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	direction=false;
	movement= calculatePosition(direction, factor);
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	direction=true;
	movement= calculatePosition(direction, factor);
	}
	
	_body.setPosition(movement[x], movement[y]);
	_body.setRotation(_theta*(180.0f/pi)+90);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(_body);
}

floatVector Player::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	if (direction)
	_theta+=factor;
	else
	_theta-=factor;
	
	movement.push_back(_radius*cos(_theta)+_x_center);
	movement.push_back(_radius*sin(_theta) +_y_center);
	return movement;
}

floatVector Player::getPostition()
{
	floatVector currentPosition;
	currentPosition.push_back(_radius*cos(_theta) + _x_center);
	currentPosition.push_back(_radius*sin(_theta) + _y_center);
	return currentPosition;
}

void Player::setTexture()
{
	_playerTexture.loadFromFile("/Users/KJ/Documents/SoftwareProject/SFMLTest/HP.png", sf::IntRect(0, 0, 150, 150));
	_body.setTexture(&_playerTexture);
}