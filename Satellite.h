#ifndef SATELLITE_H
#define SATELLITE_H

#include <cmath>
#include "MovingShootingEntity.h"
#include "EnemyBullet.h"

using floatVector = std::vector<float>;

class Satellite: public MovingShootingEntity
{
public:
	Satellite(floatVector position, float playerAngle);
	~Satellite();
	
	// Copy constructor
    Satellite(const Satellite &satellite);
	
	virtual floatVector getPosition() override;
	
	virtual float getAngle() override;
	
	virtual float getRadius() override;
	
	virtual void Update(int direction, float timeElapsed) override;	
	
	virtual floatVector calculatePosition(const bool& direction, float factor) override;
	
	virtual EntityList getEntityType() override;
	
	static int getNumberofSatellitesAlive();
	
	static int getTotalNumberofSatellites();
	
	static int getNumberofSatellitesKilled();
	
	static void ResetSatellites();
	
	virtual void createBullets() override;
	
private:
	float _theta;
	float _radius;
	const float _MAX_RADIUS = 480.0;
	float _x_center;
	float _y_center;
	const float _x_centerPlayer=1920.0/2.0;
	const float _y_centerPlayer=1080.0/2.0;
	const float _speed = 1.0;
	float _randomAngle;
	EntityList _entityType;
	static int _NumberSatellitesAlive;
	static int _TotalNumberOfSatellites;
	static int 	_NumberSatellitesKilled;
	float _time;
	float _spawnBullet;
	static bool _copies;
	const int changeRadius=150;
	float _playerAngle;

};

#endif // SATELLITE_H
