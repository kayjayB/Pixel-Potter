#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>


class Enemy
{
public:
	Enemy();
	~Enemy();
	
	void show(sf::RenderWindow& window);
	
	void movement(float timeElapsed);
	
	float getAngle();
	
	float shoot(float bulletSpeed, float shootPositionX, float shootPositionY, float bulletAngle);
	
	
private:
	sf::RectangleShape _body;
	const float _bullet_size = 5.0f;
	sf::CircleShape _bullet;
	const float _width = 60.0f;
	const float _height = 30.0f;
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 480.0f;
	float _xPosition = 1920.0f/2.0f;
	float _yPosition = 1080.0f/2.0f;
	const float _speed = 100.9f;
};

#endif // ENEMY_H

