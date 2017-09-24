#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
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
	std::shared_ptr <Player> playerPtr{ new Player{}};
    int numberOfEnemies;
    sf::Clock _clock;
	sf::Clock _clockEnemy;
	sf::Clock _clockAsteroid;
	sf::Clock _clockSatellite;
    float _elapsedTime;
	float _timeEnemy;
	float _timeAsteroid;
	float _timeSatellite;
    bool _bulletExists;
	void createEnemies();
	void checkCollision();
	bool Collision(int i, int j);
	void entityCleanUp();
	float GetTotalTime();
	void RestartTotalTime();
	void CreateAsteroid();
	void CreateSatellite();
	float generateAsteroid;
	float generateEnemy;
	void Reset();
	float GetTime();
	
	const int MAXENEMIES=10;
	
};

#endif // GAME_H
