#ifndef BULLET_H
#define BULLET_H

#include "movingEntity.h"
#include <cmath>

// The bullet class is inherited from the movingEntity class
class PlayerBullet: public movingEntity
{
public:

	PlayerBullet(float currentPlayerAngle);
	PlayerBullet(const PlayerBullet &bullet);
	
	virtual floatVector getPosition() override;
	virtual float getAngle() override;
	virtual float getRadius() override;
//	virtual void Update(bool direction, float timeElapsed) override;	
virtual void Update(int direction, float timeElapsed) override;	

virtual EntityList getEntityType() override;

private:
float _minimumRadius;
float _bulletRadius;
float _angle;
float _speed=100;
double _x_center = 1920.0 / 2.0;
double _y_center = 1080.0/ 2.0;
virtual void calculatePosition(const bool& direction, float factor) override;
EntityList _entityType;
static int _copies;
};

#endif // BULLET_H
