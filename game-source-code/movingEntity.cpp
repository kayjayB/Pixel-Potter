#include "movingEntity.h"

movingEntity::movingEntity(float entityWidth, float entityHeight, int lives):
_scale{1.0},
_entityWidth{entityWidth},
_entityHeight{entityHeight},
_lives{lives}
{
}

std::vector<std::shared_ptr<movingEntity>> movingEntity::entityList;

floatVector movingEntity::getBodySize()
{
	floatVector bodySize;
	bodySize.push_back(_entityWidth*_scale);
	bodySize.push_back(_entityHeight*_scale);
	return bodySize;
}

int movingEntity::getLives()
{
	return _lives;
	
}

void movingEntity::setLives(int life)
{
	_lives=life;
}

float movingEntity::getScale()
{
	return _scale;
}