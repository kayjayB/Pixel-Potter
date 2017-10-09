#ifndef ENTITYLIST_H
#define ENTITYLIST_H

/**
* \brief EntityList is strongly typed enum class 
* It is used to classify the type of the various enemy entities
*/
enum class EntityList
{
	PlayerEntity=0,
	PlayerBulletEntity,
	EnemyEntity,
	EnemyBulletEntity,
	AsteroidEntity,
	SatelliteEntity,
	LaserEntity,
	ArcEntity,
};

#endif