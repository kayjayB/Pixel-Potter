#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, double sizeX, double sizeY):
_enemyAnimation{texture, imageCount, switchTime},
	_row{0},
	_speed{speed},
	_faceRight{true},
	_x_center{sizeX/2},
	_y_center{sizeY/2},
	_radius{0.0f}
{
	//srand(time(0));
	float randomAngle=rand()%360; // generate random number between 0 and 360 degrees
	_theta=randomAngle*M_PI/180;
	_body.setSize(sf::Vector2f(50.0f,100.0f));
	
	floatVector initialPosition=getPostition();
	_body.setPosition(initialPosition[0], initialPosition[1]);
	_body.setOrigin(128.0f/4.0f , 192.0f/4.0f);
	_body.setTexture(texture);
	
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime, sf::RenderWindow& window)
{

	float factor = _speed * deltaTime;
	_row=0;
	bool direction = false;
	
	floatVector movement = calculatePosition(factor, window);
	
	_enemyAnimation.Update(_row, deltaTime,_faceRight);
	_body.setTextureRect(_enemyAnimation.textureRect);
	_body.setPosition(movement[0], movement[1]);
	_body.setRotation(_theta*(180.0f/M_PI)+90);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(_body);
}

floatVector Enemy::calculatePosition(float factor, sf::RenderWindow& window)
{
	floatVector movement;
	_radius+=factor;
	movement.push_back(_radius*cos(_theta)+_x_center);
	movement.push_back(_radius*sin(_theta) +_y_center);
	
	//if (movement[0] >= window.getSize().x || movement[1]>=window.getSize().y)
	if (sqrt(movement[0]*movement[0]+movement[1]*movement[1])>= 1400)
	{
		float randomAngle2=rand()%360; // generate random number between 0 and 360 degrees
		_theta=randomAngle2*M_PI/180;
		_radius=0;
		movement[0]=(_radius*cos(_theta)+_x_center);
		movement[1]=(_radius*sin(_theta) +_y_center);
	}
	
	return movement;
	
}

floatVector Enemy::getPostition()
{
	floatVector currentPosition;
	currentPosition.push_back(_radius*cos(_theta) + _x_center);
	currentPosition.push_back(_radius*sin(_theta) + _y_center);
	return currentPosition;
	
}
