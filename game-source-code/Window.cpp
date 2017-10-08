#include "Window.h"

Window::Window()
    : _window(sf::VideoMode(1920, 1080), "Pixel Potter", sf::Style::Titlebar | sf::Style::Close)
    , reset{ false }
    , _isDone{ false }
    , _isShooting{ false }
    , disableShooting{ false }
{
    fileLoader();
}

Window::~Window()
{
    _window.close();
}

void Window::fileLoader()
{
    if(!_splashTexture.loadFromFile("Slide1.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!_loseTexture.loadFromFile("lose.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!_winTexture.loadFromFile("win.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!_backgroundTexture.loadFromFile("vortex.png", sf::IntRect(0, 0, 1920, 1080)))
	throw FileNotFound();
    if(!font.loadFromFile("HARRYP__.TTF"))
	throw FileNotFound();
    if(!_playerTexture.loadFromFile("HP.png", sf::IntRect(0, 0, 150, 150)))
	throw FileNotFound();
    if(!_enemyTexture.loadFromFile("voldy.png", sf::IntRect(0, 0, 150, 150)))
	throw FileNotFound();
    if(!_satelliteTexture.loadFromFile("dementor.png", sf::IntRect(0, 0, 150, 150)))
	throw FileNotFound();
    if(!_asteroidTexture.loadFromFile("quaffle.png", sf::IntRect(0, 0, 150, 150)))
	throw FileNotFound();
    if(!_arcTexture.loadFromFile("arcMedium.png", sf::IntRect(0, 0, 150, 150)))
	throw FileNotFound();
}

void Window::closeWindow()
{
    _window.close();
}

void Window::BeginDrawMain()
{
    _window.clear(sf::Color::White);
    sf::Sprite background(_backgroundTexture);
    _window.draw(background);
    drawText();
}

void Window::drawText()
{

    sf::Text text("Enemies remaining:" + std::to_string(_enemies - Enemy::getNumberofEnemiesKilled()), font);
    textSetup(1500, 1, text);
    _window.draw(text);

    sf::Text lives("Lives remaining:" + std::to_string(_playerLives), font);
    textSetup(0, 0, lives);
    _window.draw(lives);
}

void Window::textSetup(float xPos, float yPos, sf::Text& text)
{
    text.setCharacterSize(50);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color(255, 0, 0, 255));
    text.setPosition(xPos, yPos);
}

void Window::BeginDraw()
{
    _window.clear(sf::Color::White);
}

void Window::EndDraw()
{
    _window.display();
}

bool Window::IsDone()
{
    return _isDone;
}

userInput Window::Update()
{
    reset = false;
    sf::Event event;
    while(_window.pollEvent(event)) {
	if(event.type == sf::Event::Closed) {
	    _isDone = true;
	}
	//		if (event.type==sf::Event::KeyPressed)
	//		{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	    // keyBoard.push_back(userInput::PressLeft);
	    keyBoard = userInput::PressLeft;
	    _isShooting = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	    // keyBoard.push_back(userInput::PressRight);
	    keyBoard = userInput::PressRight;
	    _isShooting = false;
	}

	if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	    // keyBoard.push_back(userInput::NoButtonPress);
	    keyBoard = userInput::NoButtonPress;
	    _isShooting = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // && !disableShooting)
	{
	    keyBoard = userInput::PressSpace;
	    _isShooting = true;
	    //	keyBoard.push_back(userInput::PressSpace);
	}
	//	disableShooting=!disableShooting;
    }
    //		else if (event.type==sf::Event::KeyReleased)
    //		{
    //			disableShooting=false;
    //		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    //		&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    //		{
    //			//keyBoard.push_back(userInput::NoButtonPress);
    //			keyBoard=userInput::NoButtonPress;
    //			_isShooting=false;
    //		}
    //		}
    return keyBoard;
}

void Window::SplashScreen()
{
    sf::Sprite background(_splashTexture);
    while(_window.isOpen()) {

	BeginDraw();

	_window.draw(background);

	_window.display();

	if(End())
	    return;
    }
}

bool Window::End()
{
    sf::Event end;

    while(_window.pollEvent(end)) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
	    _isDone = false;
	    return true;
	}

	if(end.type == sf::Event::Closed) {
	    _isDone = true;
	    _window.close();
	    return false;
	}
    }
}

void Window::DisplayGameState(sf::Sprite& texture)
{
    movingEntity::entityList.clear();
    while(_window.isOpen()) {

	BeginDraw();

	_window.draw(texture);

	_window.display();

	if(End()) {
	    return;
	}
    }
}

bool Window::isShooting()
{
    return _isShooting;
}

void Window::show(std::shared_ptr<movingEntity> entity)
{
    sf::RectangleShape _body;
    _body.setSize(sf::Vector2f(entity->getBodySize()[0], entity->getBodySize()[1]));
    _body.setOrigin(entity->getBodySize()[0] / 2, entity->getBodySize()[1] / 2);
    _body.setScale(1.0, 1.0);
    int red = 255;
    int green = 255;
    int blue = 255;
    switch(entity->getEntityType()) {
    case EntityList::ArcEntity: {
	_body.setTexture(&_arcTexture);
	_body.setOrigin(_body.getSize().x / 2, _body.getSize().y / 2);
	break;
    }
    case EntityList::AsteroidEntity: {
	_body.setTexture(&_asteroidTexture);
	break;
    }
    case EntityList::EnemyBulletEntity: {
	red = 1;
	blue = 1;
	green = 255;
	break;
    }
    case EntityList::EnemyEntity: {
	_body.setTexture(&_enemyTexture);
	break;
    }
    case EntityList::LaserEntity: {
	red = 0;
	blue = 255;
	green = 255;
	break;
    }
    case EntityList::PlayerBulletEntity: {
	red = 255;
	blue = 0;
	green = 0;
	break;
    }
    case EntityList::PlayerEntity: {

	_body.setTexture(&_playerTexture);
	switch(entity->getLives()) {
	case 0:
	    red = 255;
	    green = 0;
	    blue = 0;
	    break;
	case 1:
	    red = 255;
	    green = 0;
	    blue = 0;
	    break;
	case 2:
	    red = 255;
	    green = 120;
	    blue = 114;
	    break;
	case 3:
	    red = 255;
	    green = 154;
	    blue = 144;
	    break;
	case 4:
	    red = 255;
	    green = 182;
	    blue = 193;
	    break;
	case 5:
	    red = 255;
	    green = 255;
	    blue = 255;
	}
	break;
    }
    case EntityList::SatelliteEntity: {
	_body.setTexture(&_satelliteTexture);
	break;
    }
    }
    _body.setPosition(entity->getPosition()[0], entity->getPosition()[1]);
    _body.setRotation(entity->getAngle() * (180.0f / M_PI) + 90);
    _body.setFillColor(sf::Color(red, green, blue, 255));
    _window.draw(_body);
}

void Window::getGameState()
{
    switch(_state) {
    case gameState::lose: {
	reset = true;
	Enemy::ResetEnemies();
	sf::Sprite background(_loseTexture);
	DisplayGameState(background);
	break;
    }
    case gameState::win: {
	reset = true;
	Enemy::ResetEnemies();
	sf::Sprite background2(_winTexture);
	DisplayGameState(background2);
	break;
    }
    case gameState::playing:
	reset = false;
	break;
    }
}

void Window::setGameState(gameState state)
{
    _state = state;
}

void Window::setLivesRemaining(int lives)
{
    _playerLives = lives;
}

void Window::setMaximumEnemies(int maxEnemies)
{
    _enemies = maxEnemies;
}