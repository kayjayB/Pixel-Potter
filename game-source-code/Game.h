#ifndef GAME_H
#define GAME_H
//#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "vector"
#include "PlayerBullet.h"
#include "EntityList.h"
#include "Asteroid.h"
#include "Satellite.h"
#include <cstdlib>
#include <ctime>
#include <memory> // required for smart pointers
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
	float _timeEnemy;
	float _timeAsteroid;
	float _timeSatellite;
    bool _bulletExists;
	void createEnemies();
	float GetTotalTime();
	void RestartTotalTime();
	void CreateAsteroid();
	void CreateSatellite();
	float generateAsteroid;
	float generateEnemy;
	void Reset();
	float GetTime();
	CollisionManager collision;
	
	const int MAXENEMIES=20;
	
	entityCreator _create;
	
};

#endif // GAME_H
