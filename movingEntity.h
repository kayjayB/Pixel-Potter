#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using floatVector =std::vector<float>;
using string =std::string;
class movingEntity
{
public:

movingEntity(float entityWidth, float entityHeight, string texture);

virtual float getAngle()=0;

virtual floatVector getPosition();

virtual float getRadius()=0;

//virtual void Update(bool direction, float timeElapsed)=0;
virtual void Update(int direction, float timeElapsed) =0;	

void setTexture(string texture);

sf::RectangleShape getBody() const;

void setPosition(floatVector position);

protected:

sf::RectangleShape _body;

virtual floatVector calculatePosition(const bool& direction, float factor)=0;

private:

sf::Texture _Texture;


};

#endif // MOVINGENTITY_H
