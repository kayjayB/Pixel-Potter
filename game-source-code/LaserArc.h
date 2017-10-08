#ifndef LASERARC_H
#define LASERARC_H

#include <vector>
#include <cmath>
#include "movingEntity.h"
#include "EntityList.h"
#include "LaserGenerator.h"

using floatVector= std::vector<float>;

class LaserArc: public movingEntity
{
public:
	LaserArc(float LaserAngle, std::shared_ptr<LaserGenerator> laserGen1,std::shared_ptr<LaserGenerator> laserGen2);
	~LaserArc();
	
virtual float getAngle() override;

virtual floatVector getPosition() override;

virtual float getRadius() override;

virtual void Update(int direction, float timeElapsed) override;	

virtual EntityList getEntityType() override;

private:
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 470.0;
	float _x_center = 1920.0/2.0;
	float _y_center = 1080.0/2.0;
	const float _speed = 43.5;
	EntityList _entityType;
	std::shared_ptr<LaserGenerator> _laser1;
	std::shared_ptr<LaserGenerator> _laser2;
	virtual void calculatePosition(const bool& direction, float factor) override;

};

#endif // LASERARC_H
