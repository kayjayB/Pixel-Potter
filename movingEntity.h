#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "EntityList.h"
#include <iostream>

using floatVector =std::vector<float>;
using string =std::string;

class movingEntity
{
public:

movingEntity(float entityWidth, float entityHeight, string texture, int lives);

virtual float getAngle()=0;

virtual floatVector getPosition();

virtual float getRadius()=0;

//virtual void Update(bool direction, float timeElapsed)=0;
virtual void Update(int direction, float timeElapsed) =0;	

void setTexture(string texture);

sf::RectangleShape getBody() const;

void setPosition(floatVector position);

static std::vector<std::shared_ptr<movingEntity>> entityList;
//static std::vector<EntityList> entities;
//static addEntities()

virtual EntityList getEntityType()=0;

floatVector getBodySize();

int getLives();

void setLives(int life);

protected:

sf::RectangleShape _body;

virtual floatVector calculatePosition(const bool& direction, float factor)=0;

//~movingEntity();

private:

sf::Texture _Texture;
float _entityWidth;
float _entityHeight;
int _lives;


};

#endif // MOVINGENTITY_H
