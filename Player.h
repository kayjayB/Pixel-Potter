#ifndef PLAYER_H
#define PLAYER_H
//#include "animation.h"
#include "movingEntity.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "math.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "userInput.h"

const double pi = M_PI;
const int x=0;
const int y=1;

using floatVector =std::vector <float>;

// The player class inherits from the movingEntity class
class Player: public movingEntity
{
	public:
		Player();
		~Player();
		
		// Function to draw the object to the screen
		//void show(sf::RenderWindow& window); 
	//	floatVector getPostition();
		virtual floatVector getPosition() override;
		virtual float getAngle() override;
		virtual float getRadius() override;
		bool MovementDirection(userInput event);
		virtual void Update(bool direction, float timeElapsed) override;	
		
   private:
        unsigned int _row;
      //  const float _switchTime = 0.3f;
		float _speed = 0.9f;
//        bool _faceRight;
		double _theta;
        bool stationary;
        const double _x_center = 1920.0f / 2.0f;
        const double _y_center = 1080.0f / 2.0f;
        const double _radius = 480.0f;
        const sf::Vector2u _imageCount;
       virtual floatVector calculatePosition(const bool& direction, float factor) override;
};

#endif // PLAYERREFACTORED_H
