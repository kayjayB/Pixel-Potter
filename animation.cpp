#include "animation.h"

animation::animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	_imageCount=imageCount;
	_switchTime=switchTime;
	 _totalTime=0.0f;
	 _currentImage.x=0;
	 
	 textureRect.width= 128.0f/4.0f;
	 //texture->getSize().x/float(imageCount.x);
	 textureRect.height=192.0f/4.0f;
	 //=texture->getSize().y/float(imageCount.y);
}

animation::~animation()
{
}

void animation::Update(int row, float deltaTime, bool faceRight)
{
	_currentImage.y=row;
	_totalTime+=deltaTime;
	
	if( _totalTime >= _switchTime)
	{
		_totalTime -= _switchTime;
		_currentImage.x++;
		
		if (_currentImage.x >= _imageCount.x)
		{
			_currentImage.x=0;
		}
		
	}
	
	textureRect.top= _currentImage.y * textureRect.height;
	
	if (faceRight)
	{
	textureRect.left= _currentImage.x * textureRect.width;
	textureRect.width=abs(textureRect.width);
	}
	else
	{
		textureRect.left= (_currentImage.x+1) * abs(textureRect.width);
		textureRect.width=-abs(textureRect.width);
	}
}
