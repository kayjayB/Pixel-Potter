#include "Enemy.h"

Enemy::Enemy():
	_radius{0}
{
	float randomAngle = rand()%360;
	_theta = randomAngle*M_PI/180;
	_body.setSize(sf::Vector2f(_width,_height));
	_body.setOrigin(_width/2,_height/2);
	_body.setFillColor(sf::Color::Blue);
	_body.setRotation(randomAngle);
	_bullet.setFillColor(sf::Color::Green);
	_bullet.setRadius(_bullet_size);
	_bullet.setOrigin(_bullet_size,_bullet_size);
}

Enemy::~Enemy()
{
	
}

void Enemy::show(sf::RenderWindow& window)
{
	window.draw(_body);
	window.draw(_bullet);
}

void Enemy::movement(const float incrementRate)
{
	
	if(_radius < _MAX_RADIUS)
	{
		_body.setPosition(_xPosition + _radius*cosf(_theta),_yPosition + _radius*sinf(_theta));
		_radius = _radius + incrementRate;
	}
	else
	{
	float randomAngle = rand()%360;
	_theta = randomAngle*M_PI/180;
	_body.setRotation(randomAngle);
	_radius = 0;
	}
	//~Enemy();
}

float Enemy::shoot(float bulletSpeed, float shootPositionX, float shootPositionY, float bulletAngle)
{
	bulletSpeed = 2.0f*bulletSpeed;
	
	return bulletSpeed;
}