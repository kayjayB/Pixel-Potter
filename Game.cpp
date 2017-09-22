#include "Game.h"

Game::Game()
{
	window.SplashScreen();
	_elapsedTime=0.0;
	_bulletExists=false;
	srand(time(0));
	movingEntity::entityList.push_back(playerPtr);
	_totalTime=0.0;
}

Game::~Game()
{
}

void Game::createEnemies()
{
	if (_elapsedTime > 0.01 && Enemy::getNumberofEnemies()<5)
	{
		std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	//	std::weak_ptr <Enemy> weakEnemy(enemyPtr);
	//	deathEaters.push_back(weakEnemy);

		movingEntity::entityList.push_back(enemyPtr);
		_clockTotal.restart();
		
	}
}

void Game::Update()
{
	if (window.reset==true)
	{
		playerPtr->resetPosition();
		movingEntity::entityList.push_back(playerPtr);
	}
	createEnemies();

	userInput Keyevent =window.Update();
	playerPtr->Update(playerPtr->MovementDirection(Keyevent), GetTime());

for (auto i =(begin(movingEntity::entityList )+1); i!=end(movingEntity::entityList); ++i)
{
	(*i)->Update(1, GetTime());
}

	checkCollision();

	entityCleanUp();
}

void Game::Render()
{
	
	window.BeginDraw();

for (auto i= begin(movingEntity::entityList); i!=end(movingEntity::entityList);i++)
{
	window.showPointer((*i));
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
	_totalTime=_clockTotal.getElapsedTime().asSeconds();
}

void Game::checkCollision()
{
	
for (int i=0; i<movingEntity::entityList.size();i++)

{
	for (int j =0 ; j< movingEntity::entityList.size() ;j++)
	{
		if (i!=j)
		{
		if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyEntity)
		{
		
			if (Collision(i,j))
			{
				
				window.Lose();
			}
		}
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
					movingEntity::entityList[j]->setLives(0);
				}
		}
		
		}
	}
}

}

bool Game::Collision(int i, int j)
{
		floatVector position1= movingEntity::entityList[i]->getPosition();
		floatVector position2= movingEntity::entityList[j]->getPosition();
		floatVector halfSize1=movingEntity::entityList[i]->getBodySize();
		floatVector halfSize2=movingEntity::entityList[j]->getBodySize();
			
		float deltaX= position1[0]-position2[0];
		float deltaY= position1[1]-position2[1];
		float intersectX= fabs(deltaX)- (halfSize1[0]+halfSize2[0]);
		float intersectY= fabs(deltaY)- (halfSize1[1]+halfSize2[1]);
		
		if (intersectX < 0.0 && intersectY < 0.0)
		{
			return true;
		}
		
		return false;
}

void Game::entityCleanUp()
{
	for (auto i=begin(movingEntity::entityList); i!=end(movingEntity::entityList);)
	{
		if ((*i)->getLives() == 0)
		{
			movingEntity::entityList.erase(i);
		}
		else 
		{
			i++;
		}
	}
}

void Game::Reset()
{
	movingEntity::entityList.clear();
	movingEntity::entityList.push_back(playerPtr);
}