#include "Game.h"

Game::Game()
    : _create(gameClock, MAXENEMIES, playerPtr)
{
    window.SplashScreen();
    _elapsedTime = 0.0;
    _bulletExists = false;
    movingEntity::entityList.push_back(playerPtr);
    window.setGameState(gameState::playing);
	_create.reset();
}

Game::~Game()
{
}

void Game::Update()
{
    userInput Keyevent = window.Update();

    _create.create();

    playerPtr->Update(playerPtr->MovementDirection(Keyevent), GetTime());

    int size = movingEntity::entityList.size();

    // The for loop resizes dynamically since the size of the movingEntity::entityList vector is increasing
    // as the enemy bullets are created
    for(auto i = 1; i < size; i++) {
	int sizeInitial = movingEntity::entityList.size();
	movingEntity::entityList[i]->Update(1, GetTime());
	int sizeFinal = movingEntity::entityList.size();
	if(sizeFinal > sizeInitial) {
	    size += 1;
	}
    }

    collision.checkCollision();
    gameState state = collision.entityCleanUp(playerPtr);
    window.setGameState(state);

    if((Enemy::getTotalNumberofEnemies() % MAXENEMIES) == 0 && Enemy::getNumberofEnemiesAlive() == 0 &&
        Enemy::getTotalNumberofEnemies() != 0) {
	window.setGameState(gameState::win);
    }

    window.getGameState();

    if(window.reset == true) {
	Reset();
    }

    window.setLivesRemaining(playerPtr->getLives());
    window.setMaximumEnemies(MAXENEMIES);
}

void Game::Render()
{

    window.BeginDrawMain();

    for(auto i = begin(movingEntity::entityList); i != end(movingEntity::entityList); i++) {
	window.show((*i));
    }

    // for (auto i=begin(entityManager::body); i!=end(entityManager::body); i++)
    //{
    //	window.show((**i));
    //}

    window.EndDraw();
}

Window* Game::GetWindow()
{
    return &window;
}

float Game::GetTime()
{
    return gameClock->GetTime();
}

void Game::RestartClock()
{
    gameClock->RestartClock();
}

void Game::Reset()
{

    movingEntity::entityList.clear();
    Enemy::ResetEnemies();
    playerPtr->reset();
    movingEntity::entityList.push_back(playerPtr);
    window.setGameState(gameState::playing);
    Satellite::ResetSatellites();
    _create.reset();
}