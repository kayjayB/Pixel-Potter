#ifndef MOVINGSHOOTINGENTITY_H
#define MOVINGSHOOTINGENTITY_H

#include <vector>
#include <memory> 

#include "movingEntity.h"

class MovingShootingEntity: public movingEntity
{
public:
MovingShootingEntity(float entityWidth, float entityHeight, int lives);

virtual float getAngle() override =0;

virtual floatVector getPosition() override =0;

virtual float getRadius() override =0;

virtual void Update(int direction, float timeElapsed) override =0;

virtual void createBullets()=0;

protected:
virtual void calculatePosition(const bool& direction, float factor) override=0;

};

#endif // MOVINGSHOOTINGENTITY_H
