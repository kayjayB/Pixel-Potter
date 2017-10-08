#ifndef LASERGENERATOR_H
#define LASERGENERATOR_H
#include "movingEntity.h"
#include "EntityList.h"
#include <vector>
#include <cmath>
#include <iostream>

using floatVector= std::vector<float>;

class LaserGenerator: public movingEntity
{
public:
	LaserGenerator();
	LaserGenerator(const LaserGenerator &generator);
	~LaserGenerator();
	
virtual float getAngle() override;

virtual floatVector getPosition() override;

virtual float getRadius() override;

virtual void Update(int direction, float timeElapsed) override;	

virtual EntityList getEntityType() override;

static int _NumberLasersAlive;

static int getNumberofLasersAlive();

private:
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 520.0;
	float _x_center = 1920.0/2.0;
	float _y_center = 1080.0/2.0;
	const float _speed = 50.0;
	float _randomAngle;
	EntityList _entityType;
	virtual floatVector calculatePosition(const bool& direction, float factor) override;
};

#endif // LASERGENERATOR_H
