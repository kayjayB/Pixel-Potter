#include "Game.h"

Game::Game()
{
	window.SplashScreen();
	_elapsedTime=0.0f;
	srand(time(0));
	numberOfEnemies=5;
	for (auto i=0; i!=numberOfEnemies; i++)
	{
		Enemy newEnemy;
		deathEaters.push_back(newEnemy);
	}
	
}

Game::~Game()
{
}

void Game::Update()
{
	userInput Keyevent =window.Update();
	harryPotter.Update(harryPotter.MovementDirection(Keyevent), GetTime());
	
	for (auto &element:deathEaters)
	{
		element.movement(GetTime());
	}

}

void Game::Render()
{

	window.BeginDraw();
	harryPotter.show(window._window);
	
	for (auto &element:deathEaters)
	{
		element.show(window._window);
	}
	window.EndDraw(); 

}

Window* Game::GetWindow()
{ 
	return &window; 
}

float Game::GetTime()
{ 
	return _elapsedTime; 
}

void Game::RestartClock()
{ 
	_elapsedTime = _clock.restart().asSeconds();
}