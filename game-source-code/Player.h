#ifndef PLAYER_H
#define PLAYER_H
//#include "animation.h"
#include "movingEntity.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include "math.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "userInput.h"
#include "PlayerBullet.h"
#include "MovingShootingEntity.h"
#include <memory> // required for smart pointers
#include "Satellite.h"
//using std::unique_ptr;
//using std::make_unique;
//using std::shared_ptr;
//using std::make_shared;

const double pi = M_PI;
const int x=0;
const int y=1;

using floatVector =std::vector <float>;

// The player class inherits from the movingEntity class
class Player: public MovingShootingEntity
{
	public:
		Player();
	//	~Player();
		
		virtual floatVector getPosition() override;
		
		virtual float getAngle() override;
		
		virtual float getRadius() override;
		
		int MovementDirection(userInput event);
		
		virtual void Update(int direction, float timeElapsed) override;	
		
		//std::vector<PlayerBullet> getBullets();
	//	std::vector<std::shared_ptr<PlayerBullet>> getBullets();
	std::vector<std::weak_ptr<PlayerBullet>> getBullets();
		
		virtual void createBullets() override;
		
	//	virtual void updateBullets(float timeElapsed) override;
		
		virtual EntityList getEntityType() override;
		
		void reset();
		
   private:
        unsigned int _row;
		const int _numberLives=5;
      //  const float _switchTime = 0.3f;
		float _speed = 0.9f;
//        bool _faceRight;
		double _theta;
        bool stationary;
        const double _x_center = 1920.0f / 2.0f;
        const double _y_center = 1080.0f / 2.0f;
        const double _radius = 480.0f;
        const sf::Vector2u _imageCount;
		//std::vector<PlayerBullet> bulletList;
		//std::vector<std::shared_ptr<PlayerBullet>> bulletList;
	//	std::vector<std::weak_ptr<PlayerBullet> >bulletList;
       virtual floatVector calculatePosition(const bool& direction, float factor) override;
	   EntityList _entityType;
	   int _checkShoot;
	   std::vector <int> _upgradeBullets;
	  
};

#endif // PLAYERREFACTORED_H
