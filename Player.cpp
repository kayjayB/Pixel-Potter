#include "Player.h"

Player::Player():
_row{0},
_theta{90*pi/180},
//_imageCount(4,4),
//_faceRight{true},
stationary{false}
{
	//	_theta= 90*pi/180;
		_body.setSize(sf::Vector2f(50.0f,100.0f));
		setTexture();
		_body.setOrigin(25.0f,50.0f);
		floatVector initialPosition=getPostition();
		_body.setPosition(initialPosition[x], initialPosition[y]);
}

Player::~Player()
{
}

bool Player::MovementDirection(userInput event)
{
	switch (event)
	{
		case userInput::PressLeft:
				stationary=false;
				return false;
		case userInput::PressRight:
				stationary=false;
				return true;
		case userInput::NoButtonPress:
				stationary=true;
				return true;
	}
}
	
void Player::Update(bool direction, float timeElapsed)
{

	floatVector movement= getPostition();
	float factor = _speed*timeElapsed;
	_row=0;
	
	if (!direction && !stationary)
	{
	bool antiClockwise=false;
	movement= calculatePosition(antiClockwise, factor);
	}
	
	if(direction && !stationary)
	{
	bool clockwise=true;
	movement= calculatePosition(clockwise, factor);
	}
	
	_body.setPosition(movement[x], movement[y]);
	_body.setRotation(_theta*(180.0f/pi)+90);
}

void Player::show(sf::RenderWindow& window)
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
	movement = getPostition();
	return movement;
}

floatVector Player::getPostition()
{
	floatVector currentPosition;
	currentPosition.push_back(_radius*cosf(_theta) + _x_center);
	currentPosition.push_back(_radius*sinf(_theta) + _y_center);
	return currentPosition;
}

float Player::getAngle()
{
	return _theta;
}

void Player::setTexture()
{
	_playerTexture.loadFromFile("HP.png", sf::IntRect(0, 0, 150, 150));
	_body.setTexture(&_playerTexture);
}