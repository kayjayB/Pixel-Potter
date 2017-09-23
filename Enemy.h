#ifndef ENEMY_H
#define ENEMY_H
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "MovingShootingEntity.h"
#include "EnemyBullet.h"

using floatVector =std::vector <float>;

// The enemy class inherits from the movingEntity class
class Enemy: public MovingShootingEntity
{
public:
	Enemy();
	~Enemy();
	
	virtual floatVector getPosition() override;
	
	virtual float getAngle() override;
	
	virtual float getRadius() override;
	
	virtual void Update(int direction, float timeElapsed) override;	
	
	virtual floatVector calculatePosition(const bool& direction, float factor) override;
	
	virtual EntityList getEntityType() override;
	
	static int getNumberofEnemiesAlive();
	
	static int getTotalNumberofEnemies();
	
	static int getNumberofEnemiesKilled();
	
	static void ResetEnemies();
	
	virtual void createBullets() override;
	
private:
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 480.0;
	float _x_center = 1920.0/2.0;
	float _y_center = 1080.0/2.0;
	const float _speed = 100.9;
	float _randomAngle;
	EntityList _entityType;
	static int _NumberEnemiesAlive;
	static int _TotalNumberOfEnemies;
	static int 	_NumberEnemiesKilled;
	float _time;
	float _spawnBullet;

};

#endif // ENEMY_H

