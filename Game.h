#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Window.h"

class Game
{
public:
	Game();
	~Game();
	void Update();
	void Render();
	Window* GetWindow();
	
private:
Window window;
Player harryPotter;

};

#endif // GAME_H
