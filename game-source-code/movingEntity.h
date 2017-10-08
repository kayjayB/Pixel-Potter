#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H
#include <vector>
#include <string>
#include <memory>

#include "EntityList.h"

using floatVector =std::vector<float>;
using string =std::string;

class movingEntity
{
public:

movingEntity(float entityWidth, float entityHeight, int lives);

virtual float getAngle()=0;

virtual floatVector getPosition()=0;

virtual float getRadius()=0;

virtual void Update(int direction, float timeElapsed) =0;	

void setTexture(string texture);

static std::vector<std::shared_ptr<movingEntity>> entityList;

virtual EntityList getEntityType()=0;

floatVector getBodySize();

int getLives();

void setLives(int life);

float getScale();

protected:

virtual void calculatePosition(const bool& direction, float factor)=0;

float _scale;


private:

float _entityWidth;
float _entityHeight;
int _lives;



};

#endif // MOVINGENTITY_H
