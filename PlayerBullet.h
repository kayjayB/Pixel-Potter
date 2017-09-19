#ifndef BULLET_H
#define BULLET_H

#include "Player.h"
using std::shared_ptr;
using std::make_shared;

// The bullet class is inherited from the player class
class PlayerBullet //: public Player
{
public:
//	Bullet();
	PlayerBullet(float currentPlayerAngle);
	~PlayerBullet();
//	bool MovementDirection(userInput event);
	//void Update(bool isShooting, float timeElapsed);
	void Update(float timeElapsed);
	floatVector getPostition();
	void setPos(floatVector position);
	//auto bullet_ptr;
	//shared_ptr<Bullet> bullet_prt{new Bullet{}};
	 void show(sf::RenderWindow& window);

private:
float _minimumRadius;
floatVector calculatePosition(float factor);
float _bulletRadius;
float _angle;
const double _x_center = 1920.0f / 2.0f;
const double _y_center = 1080.0f / 2.0f;
sf::RectangleShape _body;
};

#endif // BULLET_H
