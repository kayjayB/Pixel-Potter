#include "movingEntity.h"

movingEntity::movingEntity(float entityWidth, float entityHeight, int lives):
_scaleX{1.0},
_scaleY{1.0},
_entityWidth{entityWidth},
_entityHeight{entityHeight},
_lives{lives}
{
}

std::vector<std::shared_ptr<movingEntity>> movingEntity::entityList;

floatVector movingEntity::getBodySize()
{
	floatVector bodySize;
	bodySize.push_back(_entityWidth*_scaleX);
	bodySize.push_back(_entityHeight*_scaleY);
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
