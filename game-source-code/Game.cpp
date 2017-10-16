#include "Game.h"

Game::Game()
    : _create(_gameClock, _MAXENEMIES, _playerPtr)
{
    _window.SplashScreen();
    _elapsedTime = 0.0;
    _bulletExists = false;
    movingEntity::entityList.push_back(_playerPtr);
    _window.setGameState(gameState::playing);
    _create.reset();
	_window.setMaximumEnemies(_MAXENEMIES);
	srand(time(0));
	
	GameLoop();
}

Game::~Game()
{
}

void Game::GameLoop()
{
	while(!_window.IsDone())
{
	Update();
	Render();
	RestartClock();
		 
}	
}

void Game::Update()
{	  
    userInput Keyevent = _window.Update();
	
	_create.create();

    _playerPtr->Update(_playerPtr->MovementDirection(Keyevent), GetTime());

    int size = movingEntity::entityList.size();

    for(auto i = 1; i < size; i++) {
	int sizeInitial = movingEntity::entityList.size();
	movingEntity::entityList[i]->Update(1, GetTime());
	int sizeFinal = movingEntity::entityList.size();
		if(sizeFinal > sizeInitial) {
	    size += 1;
		}
    }

    _collision.checkCollision();
    gameState state = _collision.entityCleanUp(_playerPtr);
    _window.setGameState(state);

    if((Enemy::getTotalNumberofEnemies() % _MAXENEMIES) == 0 && Enemy::getNumberofEnemiesAlive() == 0 &&
        Enemy::getTotalNumberofEnemies() != 0) {
	_window.setGameState(gameState::win);
    }

    _window.getGameState();

    if(_window.reset == true) {
	Reset();
    }

    _window.setLivesRemaining(_playerPtr->getLives());
}

void Game::Render()
{

    _window.Draw();

}

float Game::GetTime()
{
    return _gameClock->GetTime();
}

void Game::RestartClock()
{
    _gameClock->RestartClock();
}

void Game::Reset()
{

    movingEntity::entityList.clear();
    Enemy::ResetEnemies();
    _playerPtr->reset();
    movingEntity::entityList.push_back(_playerPtr);
    _window.setGameState(gameState::playing);
    Satellite::ResetSatellites();
    _create.reset();
}