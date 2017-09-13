#include "Game.h"

Game::Game()
{
	window.SplashScreen();
}

Game::~Game()
{
}

void Game::Update()
{
	window.Update();
	harryPotter.Update();

}

void Game::Render()
{

	window.BeginDraw(); // Clear.
	harryPotter.Draw(window._window);
	window.EndDraw(); // Display.

}

Window* Game::GetWindow()
{ 
	return &window; 
}