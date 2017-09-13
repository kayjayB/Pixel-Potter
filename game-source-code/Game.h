#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Window.h"
#include "Enemy.h"
#include "vector"

//using vector = std::vector;

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
//Enemy deathEater;
std::vector <Enemy> deathEaters;
sf::Event direction;
int numberOfEnemies;
float deltaTime;
sf::Clock _clock;
float _elapsedTime;
};

#endif // GAME_H
