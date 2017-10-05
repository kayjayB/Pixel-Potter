#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "movingEntity.h"
#include "EntityList.h"
#include <memory>
#include <cmath>


using floatVector=std::vector<float>;
class entityManager
{
public:
	entityManager(EntityList entitytype, float entityWidth, float entityHeight, string texture);
	~entityManager();
	
	//void setTexture(sf::RectangleShape &_body, string texture);
	void setTexture(std::shared_ptr<sf::RectangleShape> body, string texture);
	static void setPosition();
	
	void playerBody();
	void asteroidBody();
	
	static std::vector<std::shared_ptr< sf::RectangleShape>> body;

private:
sf::Vector2f convertVector(floatVector vec);
float _entityWidth;
float _entityHeight;
string _texture;

};

#endif // ENTITYMANAGER_H
