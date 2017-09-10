#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "math.h"
#include <SFML/Graphics.hpp>
#include "animation.h"

using floatVector =std::vector <float> ;

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, double sizeX, double sizeY);
	~Enemy();
	
	void Update(float deltaTime, sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	
	private:

sf::RectangleShape _body;
animation _enemyAnimation;
unsigned int _row;
float _speed;
bool _faceRight;
double _theta;
double _x_center;
double _y_center;
double _radius;
floatVector calculatePosition(float factor, sf::RenderWindow& window);
floatVector getPostition();
};

#endif // ENEMY_H

