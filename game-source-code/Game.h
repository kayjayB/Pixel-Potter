#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <memory> // required for smart pointers
#include <vector>
#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "EntityList.h"
#include "Clock.h"
#include "CollisionManager.h"
#include "entityCreator.h"
//#include "entityManager.h"

class Game
{
public:
    Game();
    ~Game();
    void Update();
    void Render();
    Window* GetWindow();
    void RestartClock();
	

private:
	Window window;
	std::shared_ptr< Clock> gameClock{new Clock{}};
	std::shared_ptr <Player> playerPtr{ new Player{}};
    int numberOfEnemies;
    float _elapsedTime;
    bool _bulletExists;
	float GetTotalTime();
	void RestartTotalTime();
	float generateAsteroid;
	float generateEnemy;
	void Reset();
	float GetTime();
	CollisionManager collision;
	
	const int MAXENEMIES=20;
	
	entityCreator _create;
	
};

#endif // GAME_H
