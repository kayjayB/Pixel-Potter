#include "Player.h"

Player::Player():
//movingEntity(50.0, 100.0, "HP.png"),
MovingShootingEntity(50.0, 100.0, "HP.png", 5),
//_row{0},
_theta{90*pi/180},
//_imageCount(4,4),
//_faceRight{true},
stationary{false},
_entityType{EntityList::PlayerEntity},
_checkShoot{0}
{
		floatVector initialPosition=getPosition();
		//_body.setPosition(initialPosition[x], initialPosition[y]);
		setPosition(initialPosition);
		
}

void Player::reset()
{
	_theta=90*pi/180;
	floatVector initialPosition=getPosition();
	setPosition(initialPosition);
	_body.setRotation(_theta*(180.0f/pi)+90);
	setLives(_numberLives);
	_upgradeBullets.clear();
}

//Player::~Player()
//{
//}

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
		_checkShoot+=1;
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
	//std::cout << movement[0] << " " << movement[1] << "end";
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
	
//	if (Satellite::getNumberofSatellitesKilled()%3==0 && Satellite::getTotalNumberofSatellites()!=0)
//	{
//		std::shared_ptr <PlayerBullet> bulletPtr{ new PlayerBullet(_theta)};
//		std::shared_ptr <PlayerBullet> bulletPtr1= std::make_shared<PlayerBullet> (*bulletPtr);
//		std::shared_ptr <PlayerBullet> bulletPtr2= std::make_shared<PlayerBullet> (*bulletPtr1);
//		std::shared_ptr <PlayerBullet> bulletPtr3= std::make_shared<PlayerBullet> (*bulletPtr2);
//		movingEntity::entityList.push_back(bulletPtr1);
//		movingEntity::entityList.push_back(bulletPtr2);
//		movingEntity::entityList.push_back(bulletPtr3);
//	}
//	else
//	{
//		std::shared_ptr <PlayerBullet> bulletPtr{ new PlayerBullet(_theta)};
//		movingEntity::entityList.push_back(bulletPtr);
//	}
if (Satellite::getNumberofSatellitesKilled()%3==0 && Satellite::getTotalNumberofSatellites()!=0
&& Satellite::getNumberofSatellitesKilled()!=0)
{
_upgradeBullets.push_back(1);
}
else
{
_upgradeBullets.push_back(0);
}

auto index= std::find (begin(_upgradeBullets), end(_upgradeBullets), 1);

if (index != end(_upgradeBullets))
{
		std::shared_ptr <PlayerBullet> bulletPtr{ new PlayerBullet(_theta)};
		std::shared_ptr <PlayerBullet> bulletPtr1= std::make_shared<PlayerBullet> (*bulletPtr);
		std::shared_ptr <PlayerBullet> bulletPtr2= std::make_shared<PlayerBullet> (*bulletPtr1);
	//	std::shared_ptr <PlayerBullet> bulletPtr3= std::make_shared<PlayerBullet> (*bulletPtr2);
		movingEntity::entityList.push_back(bulletPtr1);
		movingEntity::entityList.push_back(bulletPtr2);
	//	movingEntity::entityList.push_back(bulletPtr3);
	
}
else
{
		std::shared_ptr <PlayerBullet> bulletPtr{ new PlayerBullet(_theta)};
		movingEntity::entityList.push_back(bulletPtr);
}

}

EntityList Player::getEntityType()
{
	return _entityType;
}