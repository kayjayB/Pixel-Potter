#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "vector"
#include "PlayerBullet.h"
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

private:
	Window window;
    Player harryPotter;
	std::vector<Enemy> deathEaters;
    int numberOfEnemies;
    // float deltaTime;
    sf::Clock _clock;
    float _elapsedTime;
    bool _bulletExists;
    std::vector<PlayerBullet> gameBullets;
};

#endif // GAME_H
