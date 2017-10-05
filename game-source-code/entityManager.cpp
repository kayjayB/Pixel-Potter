#include "entityManager.h"

//std::vector<sf::RectangleShape> entityManager::body;
std::vector <std::shared_ptr<sf::RectangleShape>> entityManager::body;
entityManager::entityManager(EntityList entitytype, float entityWidth, float entityHeight, 
string texture):
_entityWidth{entityWidth},
_entityHeight{entityHeight},
_texture{texture}
{
	
	switch (entitytype)
	{
		case EntityList::PlayerEntity:
		playerBody();
		break;
		case EntityList::AsteroidEntity:
		asteroidBody();
		break;
	}
}

entityManager::~entityManager()
{
}

void entityManager::playerBody()
{
		 std::shared_ptr<sf::RectangleShape> ptr {new sf::RectangleShape()};
//		_body.setSize(sf::Vector2f(_entityWidth,_entityHeight));
//		setTexture(_body, _texture);
//		_body.setOrigin(_entityHeight/2,_entityHeight/2);
	ptr -> setSize(sf::Vector2f(_entityWidth,_entityHeight));
	//setTexture(ptr, _texture);
		if (_texture.size()!=0)
	{
		sf::Texture _Texture;
		_Texture.loadFromFile(_texture, sf::IntRect(0, 0, 150, 150));
		ptr->setTexture(&_Texture);
	}
		ptr->setOrigin(_entityHeight/2,_entityHeight/2);
	//	ptr->setFillColor(sf::Color::Blue);
		entityManager::body.push_back(ptr);
}

void entityManager::asteroidBody()
{
	std::shared_ptr<sf::RectangleShape> ptr {new sf::RectangleShape()};
	ptr -> setSize(sf::Vector2f(_entityWidth,_entityHeight));
		if (_texture.size()!=0)
	{
		sf::Texture _Texture;
		_Texture.loadFromFile(_texture, sf::IntRect(0, 0, 150, 150));
		ptr->setTexture(&_Texture);
	}
		ptr->setOrigin(_entityHeight/2,_entityHeight/2);
		entityManager::body.push_back(ptr);
}

//void entityManager::setTexture(sf::RectangleShape &_body, string texture)
void entityManager::setTexture(std::shared_ptr<sf::RectangleShape> _body, string texture)
{
	if (texture.size()!=0)
	{
		sf::Texture _Texture;
		_Texture.loadFromFile(texture, sf::IntRect(0, 0, 150, 150));
		_body->setTexture(&_Texture);
	}
}

void entityManager::setPosition()
{
	for (auto i=0; i<movingEntity::entityList.size(); i++)
	{
		floatVector pos=movingEntity::entityList[i]->getPosition();
	//	sf::Vector2f entityPosition= convertVector(pos);
		entityManager::body[i]->setPosition(pos[0],pos[1]);
		
		float angle =movingEntity::entityList[i]->getAngle();
		entityManager::body[i]->setRotation(angle*(180.0f/M_PI)+90);
	}
}

sf::Vector2f entityManager::convertVector(floatVector vec)
{
	sf::Vector2f sfmlVector;
	sfmlVector.x=vec[0];
	sfmlVector.y=vec[1];
	
	return sfmlVector;
}