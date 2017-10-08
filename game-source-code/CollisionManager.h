#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <memory>

#include "movingEntity.h"
#include "Player.h"
#include "Window.h"
#include "gameState.h"


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	void checkCollision();
	bool Collision(int i, int j);
	void entityCleanUp(std::shared_ptr <Player> playerPtr,  Window& window);

private:

};

#endif // COLLISIONMANAGER_H