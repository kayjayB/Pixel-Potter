#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "movingEntity.h"

using floatVector =std::vector <float>;

// The enemy class inherits from the movingEntity class
class Enemy: public movingEntity
{
public:
	Enemy();
	~Enemy();
	
	virtual floatVector getPosition() override;
	
	virtual float getAngle() override;
	
	virtual float getRadius() override;
	
	virtual void Update(int direction, float timeElapsed) override;	
	
	virtual floatVector calculatePosition(const bool& direction, float factor) override;
	
	static floatVector angles;
	
	static bool angleCompare();
	
	virtual EntityList getEntityType() override;
	
	static int getNumberofEnemies();
	
	
private:
	//const float _bullet_size = 5.0f;
	sf::CircleShape _bullet;
	//const float _width = 60.0f;
	//const float _height = 30.0f;
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 480.0f;
	float _x_center = 1920.0f/2.0f;
	float _y_center = 1080.0f/2.0f;
	const float _speed = 100.9f;
	float _randomAngle;
	EntityList _entityType;
	static int _NumberEnemies;

};

#endif // ENEMY_H

