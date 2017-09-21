#include "Game.h"

Game::Game()
{
	window.SplashScreen();
	_elapsedTime=0.0f;
	_bulletExists=false;
	srand(time(0));
	movingEntity::entityList.push_back(playerPtr);
	createEnemies();
}

Game::~Game()
{
}

void Game::createEnemies()
{
	numberOfEnemies=10;
	for (auto i=0; i!=numberOfEnemies; i++)
	{

	std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
	deathEaters.push_back(enemyPtr);

	movingEntity::entityList.push_back(enemyPtr);
	}
}

void Game::Update()
{
	
	userInput Keyevent =window.Update();
	playerPtr->Update(playerPtr->MovementDirection(Keyevent), GetTime());
	
	for (auto & element: deathEaters)
	{
		element->Update(1, GetTime());
	}

checkCollision();

entityCleanUp();
	
}

void Game::Render()
{
	
	window.BeginDraw();
//	window.showPointer(playerPtr);
//	gameBullets=playerPtr->getBullets();
//
//for (auto &bullets:gameBullets)
//{
//	window.showPointer(bullets);
//}
//	
//	for (auto &element:deathEaters)
//	{
//		window.showPointer(element);
//	}


	for (auto element: movingEntity::entityList)
	{
		window.showPointer(element);
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

void Game::checkCollision()
{
	
for (int i=0; i<movingEntity::entityList.size();i++)

{
	for (int j =0 ; j< movingEntity::entityList.size() ;j++)
	{
		if (i!=j)
		{
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyEntity)
			{
				if (Collision(i,j)) 
				{
				// movingEntity::entityList[i]->setLives(movingEntity::entityList[i]->getLives()-1);
				// std:: cout << movingEntity::entityList[i]->getLives();
				// movingEntity::entityList[j]->setLives(movingEntity::entityList[j]->getLives()-1);
					//movingEntity::entityList.erase(movingEntity::entityList.begin()+i);
					//movingEntity::entityList.erase(movingEntity::entityList.begin()+j);
					movingEntity::entityList[i]->setLives(0);
					movingEntity::entityList[j]->setLives(0);
				}
		}
		if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyEntity)
		{
		
			if (Collision(i,j))
			{
				window.Lose();
				//return;
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
	for (auto i=begin(movingEntity::entityList); i!=end(movingEntity::entityList); i++)
	{
		if ((*i)->getLives() == 0)
		{
		//	std::cout << "Deleting";
			i= movingEntity::entityList.erase(i);
		}
	}
	
}