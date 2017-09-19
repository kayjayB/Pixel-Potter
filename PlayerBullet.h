#ifndef BULLET_H
#define BULLET_H

#include "movingEntity.h"
#include <cmath>

// The bullet class is inherited from the movingEntity class
class PlayerBullet: public movingEntity
{
public:

	PlayerBullet(float currentPlayerAngle);
	~PlayerBullet();
	
	virtual floatVector getPosition() override;
	virtual float getAngle() override;
	virtual float getRadius() override;
//	virtual void Update(bool direction, float timeElapsed) override;	
virtual void Update(int direction, float timeElapsed) override;	

private:
float _minimumRadius;
float _bulletRadius;
float _angle;
float _speed=100;
double _x_center = 1920.0f / 2.0f;
double _y_center = 1080.0f / 2.0f;
virtual floatVector calculatePosition(const bool& direction, float factor) override;
};

#endif // BULLET_H
