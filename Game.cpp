#include "Game.h"

Game::Game()
{
	window.SplashScreen();
	_elapsedTime=0.0f;
	_bulletExists=false;
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
		element.Update(true, GetTime());
	}
	
//	if (Keyevent== userInput::PressSpace)
//	{
//		PlayerBullet bullet(harryPotter.getAngle());
//		bulletList.push_back(bullet);
//	}
//
//		for (int j=0; j<bulletList.size();j++)
//		{
//			bulletList[j].Update(true, GetTime());
//			if (bulletList[j].getPosition()[0] > 4000)
//				bulletList.erase(bulletList.begin()+j);
//		}
}

void Game::Render()
{
	
	window.BeginDraw();
	window.show(harryPotter);
	gameBullets=harryPotter.getBullets();
for (auto &bullets:gameBullets)
{
	window.show(bullets);
}
	
	for (auto &element:deathEaters)
	{
		//element.show(window._window);
		window.show(element);
	}
	
	window.EndDraw(); 
	//	_bulletExists=false;
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