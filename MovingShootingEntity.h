#ifndef MOVINGSHOOTINGENTITY_H
#define MOVINGSHOOTINGENTITY_H

#include "movingEntity.h"
//#include <template>

#include <vector>
#include <memory> // required for smart pointers
//using std::unique_ptr;
//using std::make_unique;
//using std::shared_ptr;
//using std::make_shared;

class MovingShootingEntity: public movingEntity
{
public:
	MovingShootingEntity(float entityWidth, float entityHeight, string texture,  int lives);

virtual float getAngle() override =0;

virtual floatVector getPosition() override =0;

virtual float getRadius() override =0;

//virtual void Update(bool direction, float timeElapsed) override =0;
virtual void Update(int direction, float timeElapsed) override =0;

virtual void createBullets()=0;
//virtual void updateBullets(float timeElapsed)=0;
//virtual std::vector<movingEntity> shoot(float timeElapsed)=0;
//virtual shared_ptr<movingEntity> shoot(float timeElapsed)=0;
//virtual shared_ptr<std::vector<movingEntity>> shoot(float timeElapsed) =0;
//virtual std::vector<shared_ptr<movingEntity>> shoot(float timeElapsed)=0;
//void setPosition(floatVector position);

protected:
virtual floatVector calculatePosition(const bool& direction, float factor) override=0;

//~MovingShootingEntity();

};

#endif // MOVINGSHOOTINGENTITY_H
