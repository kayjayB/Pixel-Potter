#include "movingEntity.h"

movingEntity::movingEntity(float entityWidth, float entityHeight, int lives, int red, int blue, int green, const string &texture):
_scaleX{1.0},
_scaleY{1.0},
_red{red},
 _blue{blue},
_green{green},
_entityWidth{entityWidth},
_entityHeight{entityHeight},
_lives{lives},
_texture{texture}
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

void movingEntity::collide()
{
	_lives-=1;
}

void movingEntity::setLives(int life)
{
	_lives=life;
}

std::vector<int> movingEntity::getColour()
{
	std::vector<int> colour{_red,_blue,_green};
	return colour;
}
	
string movingEntity::getTextureName()
{
	return _texture;
}