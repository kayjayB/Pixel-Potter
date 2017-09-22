#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "vector"
#include "PlayerBullet.h"
#include "EntityList.h"
#include <memory> // required for smart pointers

class Game
{
public:
    Game();
    ~Game();
    void Update();
    void Render();
    Window* GetWindow();
    float GetTime();
    void RestartClock();
	void Reset();
	

private:
	Window window;
	std::shared_ptr <Player> playerPtr{ new Player{}};
    int numberOfEnemies;
    sf::Clock _clock;
	sf::Clock _clockTotal;
    float _elapsedTime;
	float _totalTime;
    bool _bulletExists;
	void createEnemies();
	void checkCollision();
	bool Collision(int i, int j);
	void entityCleanUp();
	float GetTotalTime();
	void RestartTotalTime();
	
	const int MAXENEMIES=5;
	
};

#endif // GAME_H
