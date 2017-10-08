#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <algorithm> 
#include <memory> 
#include "userInput.h"
#include "PlayerBullet.h"
#include "MovingShootingEntity.h"
#include "Satellite.h"
#include "movingEntity.h"

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
		
		virtual void createBullets() override;
		
		virtual EntityList getEntityType() override;
		
		void reset();
		
   private:
        unsigned int _row;
		const int _numberLives=5;
		float _speed = 0.9f;
		double _theta;
        const double _x_center = 1920.0f / 2.0f;
        const double _y_center = 1080.0f / 2.0f;
        const double _radius = 480.0f;
       virtual void calculatePosition(const bool& direction, float factor) override;
	   EntityList _entityType;
	   int _checkShoot;
	   std::vector <int> _upgradeBullets;
	  
};

#endif
