#ifndef PLAYER_H
#define PLAYER_H
#include "animation.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "math.h"
//#include "playerMovement.h"

const double pi = M_PI;
const int x=0;
const int y=1;

using floatVector =std::vector <float> ;

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, double sizeX, double sizeY);
	~Player();

void Update(float deltaTime);
void Draw(sf::RenderWindow& window);

private:

sf::RectangleShape _body;
animation _playerAnimation;
unsigned int _row;
float _speed;
bool _faceRight;
double _radiusTolerance;
double _theta;
double _x_center;
double _y_center;
double _radius;
//playerMovement _harryMovement;
floatVector calculatePosition(const bool &direction, float factor);
floatVector getPostition();
};

#endif // PLAYER_H
