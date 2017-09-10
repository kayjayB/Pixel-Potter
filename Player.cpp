#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, double sizeX, double sizeY):
_playerAnimation{texture, imageCount, switchTime},
	_row{0},
	_speed{speed},
	_faceRight{true},
	_radiusTolerance{50.0f},
	_x_center{sizeX/2},
	_y_center{sizeY/2},
	_radius{_x_center-_radiusTolerance}
{
	srand(time(0));
	float randomAngle=rand()%360; // generate random number between 0 and 360 degrees
	_theta=randomAngle*pi/180;
	_body.setSize(sf::Vector2f(50.0f,100.0f));
	
	floatVector initialPosition=getPostition();
	_body.setPosition(initialPosition[x], initialPosition[y]);
	_body.setOrigin(128.0f/4.0f , 192.0f/4.0f);
	_body.setTexture(texture);
	
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{

	floatVector movement= getPostition();
	float factor = _speed * deltaTime;
	_row=0;
	bool direction = false;
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
	direction=true;
	movement= calculatePosition(direction, factor);
	_row=1;
	_faceRight=false;
	}
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
	direction=false;
	movement= calculatePosition(direction, factor);
	_row=1;
	_faceRight=true;
	}
	
	_playerAnimation.Update(_row, deltaTime,_faceRight);
	_body.setTextureRect(_playerAnimation.textureRect);
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
	{
	_theta+=factor;
	movement.push_back(_radius*cos(_theta)+_x_center);
	movement.push_back(_radius*sin(_theta) +_y_center);
	return movement;
	}
	
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