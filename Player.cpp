#include "Player.h"

Player::Player():
//movingEntity(50.0, 100.0, "HP.png"),
MovingShootingEntity(50.0, 100.0, "HP.png"),
//_row{0},
_theta{90*pi/180},
//_imageCount(4,4),
//_faceRight{true},
stationary{false}
{
		floatVector initialPosition=getPosition();
		//_body.setPosition(initialPosition[x], initialPosition[y]);
		setPosition(initialPosition);
}

Player::~Player()
{
}

int Player::MovementDirection(userInput event)
{
	switch (event)
	{
		case userInput::PressSpace:
				return 0;
		case userInput::PressLeft:
				return 1;
		case userInput::PressRight:
				return 2;
		case userInput::NoButtonPress:
				return 3;
		break;
	}
}
	
void Player::Update(int direction, float timeElapsed)
{

	floatVector movement= getPosition();
	float factor = _speed*timeElapsed;
	_row=0;
	bool clockwise;
	
	switch (direction)
	{
		case 0:
		createBullets();
		break;
		case 1:
		clockwise=false;
		movement= calculatePosition(clockwise, factor);
		break;
		case 2:
		clockwise=true;
		movement= calculatePosition(clockwise, factor);
		break;
		case 3:
		break;
	}
	
	updateBullets(timeElapsed);
	setPosition(movement);
	_body.setRotation(_theta*(180.0f/pi)+90);
}

floatVector Player::calculatePosition(const bool &direction, float factor)
{
	floatVector movement;
	if (direction)
	_theta+=factor;
	else
	_theta-=factor;
	movement = getPosition();
	return movement;
}

floatVector Player::getPosition()
{
	floatVector currentPosition;
	currentPosition.push_back(_radius*cosf(_theta) + _x_center);
	currentPosition.push_back(_radius*sinf(_theta) + _y_center);
	return currentPosition;
}

float Player::getAngle()
{
	return _theta;
}


float Player::getRadius()
{
	return _radius;
}

void Player::createBullets()
{
		PlayerBullet bullet(_theta);
		bulletList.push_back(bullet);
}

void Player::updateBullets(float timeElapsed)
{
			for (int j=0; j<bulletList.size();j++)
		{
			bulletList[j].Update(true, timeElapsed);
			if (bulletList[j].getPosition()[0] > 4000)
				bulletList.erase(bulletList.begin()+j);
		}
}

std::vector<PlayerBullet> Player::getBullets()
{
	return bulletList;
} 
