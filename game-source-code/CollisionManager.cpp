#include "CollisionManager.h"

CollisionManager::CollisionManager():
_collidedArc{false}
{
}

void CollisionManager::checkCollision()
{
_collidedArc=false;
    for(int i = 0; i < movingEntity::entityList.size(); i++)

    {
	for(int j = 0; j < movingEntity::entityList.size(); j++) {
	    if(i != j) {
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}
		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::AsteroidEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyBulletEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::ArcEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
			_collidedArc=true;
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::LaserEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::LaserEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::ArcEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyBulletEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::EnemyEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::AsteroidEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
		    }
		}

		if(movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity &&
		    movingEntity::entityList[j]->getEntityType() == EntityList::SatelliteEntity) {
		    if(Collision(i, j)) {
			movingEntity::entityList[i]->collide();
			movingEntity::entityList[j]->collide();
		    }
		}
	    }
	}
    }
	
	for (int i = 0; i < movingEntity::entityList.size(); i++)
	{
		if (_collidedArc==true && movingEntity::entityList[i]->getEntityType() == EntityList::LaserEntity)
		{
			movingEntity::entityList[i]->collide();
		}
	}
}

bool CollisionManager::Collision(int i, int j)
{
    floatVector position1 = movingEntity::entityList[i]->getPosition();
    floatVector position2 = movingEntity::entityList[j]->getPosition();
    floatVector Size1 = movingEntity::entityList[i]->getBodySize();
    floatVector Size2 = movingEntity::entityList[j]->getBodySize();

    float deltaX = position1[0] - position2[0];
    float deltaY = position1[1] - position2[1];
    float intersectX = fabs(deltaX) - (Size1[0] / 2 + Size2[0] / 2);
    float intersectY = fabs(deltaY) - (Size1[1] / 2 + Size2[1] / 2);

    if(intersectX < 0.0 && intersectY < 0.0) {
	return true;
    }

    return false;
}

gameState CollisionManager::entityCleanUp(std::shared_ptr<Player> playerPtr)
{
    if(playerPtr->getLives() <= 0) {
	return gameState::lose;
    }
    for(auto i = begin(movingEntity::entityList); i != end(movingEntity::entityList);) {
	if((*i)->getLives() <= 0) {
	    movingEntity::entityList.erase(i);
	} else {
	    i++;
	}
    }
	return gameState::playing;
}