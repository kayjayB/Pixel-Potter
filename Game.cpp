#include "Game.h"

Game::Game()
{
	window.SplashScreen();
	_elapsedTime=0.0;
	_bulletExists=false;
//	srand(time(0));
	movingEntity::entityList.push_back(playerPtr);
	_timeAsteroid=0.0;
	_timeEnemy=0.0;
	_timeSatellite=0.0;
	window.setGameState(gameState::playing);
	generateAsteroid= fmod(rand(),5.0)+1;
	generateEnemy= 1;
	
}

Game::~Game()
{
}

void Game::createEnemies()
{
//	if ( enemiesAlive < 3 )
//	{
//	std::cout << " random no " << generateEnemy <<" time " << _timeEnemy;
//	if (_timeEnemy > (generateEnemy - 1) && _timeEnemy < (generateEnemy+1) && Enemy::getTotalNumberofEnemies()<MAXENEMIES)
//	{
//		std::cout << " enemies alive inside if 1 " << enemiesAlive ;
//		std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
//		movingEntity::entityList.push_back(enemyPtr);
//		generateEnemy=fmod(rand(),4)+_timeEnemy;
//		_clockEnemy.restart();
//	}
//	}

_timeEnemy+=_elapsedTime;
generateEnemy=fmod(rand(),4)+_timeEnemy;
if ( Enemy::getNumberofEnemiesAlive() < 3 )
	{
//	std::cout << " random no " << generateEnemy <<" time " << _timeEnemy;
	if (_timeEnemy > (generateEnemy - 1) && _timeEnemy < (generateEnemy+1) && Enemy::getTotalNumberofEnemies()<MAXENEMIES)
	{
	//	std::cout << " enemies alive inside if 1 " << enemiesAlive ;
		std::shared_ptr <Enemy> enemyPtr{ new Enemy{}};
		movingEntity::entityList.push_back(enemyPtr);
	//	_clockEnemy.restart();
//	_timeEnemy=0.0;
	}
}
}

void Game::CreateAsteroid()
{
	if (_timeAsteroid > (generateAsteroid - 1) && _timeAsteroid < (generateAsteroid+1))
	{
		
		std::shared_ptr <Asteroid> asteroidPtr{ new Asteroid{playerPtr->getAngle()}};
		movingEntity::entityList.push_back(asteroidPtr);
		generateAsteroid=fmod(rand(),8.0)+1;
		_clockAsteroid.restart();
	}
}

void Game::CreateSatellite()
{
	if ((fmod(_timeSatellite,5)>0) && fmod(_timeSatellite,5)<(0.2) && Satellite::getNumberofSatellitesAlive() ==0 )
	{
		floatVector position =playerPtr->getPosition();
		float angle =playerPtr->getAngle();
		std::shared_ptr <Satellite> satellitePtr{ new Satellite{position,angle}};
		std::shared_ptr <Satellite> satellitePtr2= std::make_shared<Satellite> (*satellitePtr);
		std::shared_ptr <Satellite> satellitePtr3= std::make_shared<Satellite> (*satellitePtr2);
		movingEntity::entityList.push_back(satellitePtr);
		movingEntity::entityList.push_back(satellitePtr2);
		movingEntity::entityList.push_back(satellitePtr3);
	}
}

void Game::Update()
{

//	if ((Enemy::getTotalNumberofEnemies()%MAXENEMIES) == 0 && Enemy::getNumberofEnemiesAlive()==0 && Enemy::getTotalNumberofEnemies()!=0)
//	{
//		window.setGameState(gameState::win);
//
//	}
//	
//	window.getGameState();
//
//	
//	if (window.reset==true)
//	{
//		Reset();
//	}
	
	userInput Keyevent =window.Update();
	
	createEnemies();
	
	CreateAsteroid();
	
	CreateSatellite();

	playerPtr->Update(playerPtr->MovementDirection(Keyevent), GetTime());

int size= movingEntity::entityList.size();

// The for loop resizes dynamically as the size of the movingEntity::entityList vector is increasing
// as the enemy bullets are created
for (auto i =1; i< size; i++) 
{
	int sizeInitial= movingEntity::entityList.size();
	movingEntity::entityList[i]->Update(1, GetTime());
	int sizeFinal= movingEntity::entityList.size();
	if (sizeFinal>sizeInitial)
	{
		size+=1;
	}
}

	checkCollision();

	entityCleanUp();
	
		if ((Enemy::getTotalNumberofEnemies()%MAXENEMIES) == 0 && Enemy::getNumberofEnemiesAlive()==0 && Enemy::getTotalNumberofEnemies()!=0)
	{
		window.setGameState(gameState::win);

	}
	
	window.getGameState();

	
	if (window.reset==true)
	{
		Reset();
	}
	
}

void Game::Render()
{
	
	window.BeginDrawMain();
	sf::Font font;
	font.loadFromFile("HARRYP__.TTF");
	sf::Text text("Enemies remaining:" + std::to_string(MAXENEMIES- Enemy::getNumberofEnemiesKilled()), font);
//	sf::Text text("Enemies alive:" + std::to_string(Enemy::getNumberofEnemiesAlive()), font);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color(255,1,1,255));
	text.setPosition(1600, 1);
	text.setStyle(sf::Text::Bold);
	window._window.draw(text);


	sf::Text lives("Lives remaining:" + std::to_string(playerPtr->getLives()), font);
//	sf::Text text("Enemies alive:" + std::to_string(Enemy::getNumberofEnemiesAlive()), font);
	lives.setCharacterSize(50);
	lives.setStyle(sf::Text::Bold);
	lives.setColor(sf::Color(255,1,1,255));
	lives.setStyle(sf::Text::Bold);
	window._window.draw(lives);
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
	_timeAsteroid=_clockAsteroid.getElapsedTime().asSeconds();
//	_timeEnemy=_clockEnemy.getElapsedTime().asSeconds();
	_timeSatellite=_clockSatellite.getElapsedTime().asSeconds();
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
				movingEntity::entityList[i]->setLives(playerPtr->getLives() -1);
				movingEntity::entityList[j]->setLives(0);
				//window.setGameState(gameState::lose);
				//return;
			}
		}
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::AsteroidEntity)
			{
				if (Collision(i,j)) 
				{
					//window.setGameState(gameState::lose);
					movingEntity::entityList[i]->setLives(playerPtr->getLives() -1);
					movingEntity::entityList[j]->setLives(0);
					//return;
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyBulletEntity)
			{
				if (Collision(i,j)) 
				{
				//	window.setGameState(gameState::lose);
				//	return;
					movingEntity::entityList[i]->setLives(playerPtr->getLives() -1);
					movingEntity::entityList[j]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::EnemyBulletEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
					movingEntity::entityList[j]->setLives(0);
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
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::AsteroidEntity)
			{
				if (Collision(i,j)) 
				{
					movingEntity::entityList[i]->setLives(0);
				}
			}
			
			if (movingEntity::entityList[i]->getEntityType() == EntityList::PlayerBulletEntity && movingEntity::entityList[j]->getEntityType()== EntityList::SatelliteEntity)
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
//			
		float deltaX= position1[0]-position2[0];
		float deltaY= position1[1]-position2[1];
		float intersectX= fabs(deltaX)- (halfSize1[0]/2+halfSize2[0]/2);
		float intersectY= fabs(deltaY)- (halfSize1[1]/2+halfSize2[1]/2);

//float distance = sqrt((position1[0]-position2[0])*(position1[0]-position2[0]) 
//+ (position1[1]-position2[1])*(position1[1]-position2[1]));
//
//if (distance < (halfSize1[0]/2+halfSize2[0]/2))
//{
//    return true;
//}
		
		if (intersectX < 0.0 && intersectY < 0.0)
		{
			return true;
		}
		
		return false;
}

void Game::entityCleanUp()
{
	if (playerPtr->getLives() <=0)
	{
		window.setGameState(gameState::lose);
		return;
	}
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
		Enemy::ResetEnemies();
		playerPtr->reset();
		movingEntity::entityList.push_back(playerPtr);
		window.setGameState(gameState::playing);
		_clockAsteroid.restart();
		_clockEnemy.restart();
		generateAsteroid= fmod(rand(),5.0)+1;
		generateEnemy= 1;
		Satellite::ResetSatellites();
}