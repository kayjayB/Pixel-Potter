#ifndef ENEMYBULLETS_H
#define ENEMYBULLETS_H

#include "movingEntity.h"
#include "EntityList.h"
#include <cmath>

class EnemyBullet: public movingEntity
{
public:
EnemyBullet(float currentEnemyAngle, float currentEnemyRadius);
	
	virtual floatVector getPosition() override;
	virtual float getAngle() override;
	virtual float getRadius() override;
	virtual void Update(int direction, float timeElapsed) override;	

	virtual EntityList getEntityType() override;

	private:
	const float _MAXIMUM_RADIUS=480.0;
	float _bulletRadius;
	float _angle;
	float _speed=200;
	double _x_center = 1920.0 / 2.0;
	double _y_center = 1080.0/ 2.0;
	virtual floatVector calculatePosition(const bool& direction, float factor) override;
	EntityList _entityType;

};

#endif // ENEMYBULLETS_H
