#include "Player.h"

Player::Player():
movingEntity(50.0, 100.0, "HP.png"),
//_row{0},
_theta{90*pi/180},
//_imageCount(4,4),
//_faceRight{true},
stationary{false}
{
		floatVector initialPosition=getPosition();
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
		case userInput::PressSpace:
				stationary=true;
				return true;
	}
}
	
void Player::Update(bool direction, float timeElapsed)
{

	floatVector movement= getPosition();
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

floatVector Player::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	if (direction)
	_theta+=factor;
	else
	_theta-=factor;
	//getPostition(movement);
	movement = getPosition();
	return movement;
}

floatVector Player::getPosition()
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

//void Player::setTexture()
//{
//	_playerTexture.loadFromFile("HP.png", sf::IntRect(0, 0, 150, 150));
//	_body.setTexture(&_playerTexture);
//}

float Player::getRadius()
{
	return _radius;
}