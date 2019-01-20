#pragma once

//Project includes
#include "GridObject.h"

class Gem : public GridObject
{
public:
	Gem();

	bool AttemptFall(sf::Vector2i _direction, sf::Time _frametime);
	void Update(sf::Time _frameTime);
	

private:

	float m_timer;
	float m_fallDelay;
};