#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory> 
#include <iostream>
#include "math.h"
#include "userInput.h"
#include "PlayerBullet.h"
#include "MovingShootingEntity.h"
#include "movingEntity.h"

using floatVector =std::vector <float>;

class Asteroid: public movingEntity
{
public:

Asteroid(float angle);

virtual float getAngle() override;

virtual floatVector getPosition() override;

virtual float getRadius() override;

virtual void Update(int direction, float timeElapsed) override;	

virtual EntityList getEntityType() override;


private:
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 480.0f;
	float _x_center = 1920.0f/2.0f;
	float _y_center = 1080.0f/2.0f;
	const float _speed = 100.9f;
	EntityList _entityType;
	virtual floatVector calculatePosition(const bool& direction, float factor) override;
};

#endif // ASTEROID_H
