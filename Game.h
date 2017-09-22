#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "vector"
#include "PlayerBullet.h"
#include "EntityList.h"
//#include "Collide.h"
#include <memory> // required for smart pointers
//using std::unique_ptr;
//using std::make_unique;
//using std::shared_ptr;
//using std::make_shared;

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
	//Collide collision;
	Window window;
    //Player harryPotter;
	std::shared_ptr <Player> playerPtr{ new Player{}};
//	std::vector<Enemy> deathEaters;
	//std::vector<std::shared_ptr<Enemy> >deathEaters;
	//std::vector<std::weak_ptr<Enemy> >deathEaters;
    int numberOfEnemies;
    // float deltaTime;
    sf::Clock _clock;
	sf::Clock _clockTotal;
    float _elapsedTime;
	float _totalTime;
    bool _bulletExists;
    //std::vector<PlayerBullet> gameBullets;
	//std::vector<std::shared_ptr<PlayerBullet>> gameBullets;
	void createEnemies();
	void checkCollision();
	bool Collision(int i, int j);
	void entityCleanUp();
	float GetTotalTime();
	void RestartTotalTime();
	//void checkCollision(std::vector<std::shared_ptr<movingEntity>> &entityList);
	
};

#endif // GAME_H
