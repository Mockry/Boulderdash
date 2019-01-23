#pragma once
//library includes
#include <SFML/Audio.hpp>

//Project includes
#include "GridObject.h"

class Player : public GridObject
{
public:
	Player();

	//ovverriding methods
	virtual void Input(sf::Event _gameEvent);
	virtual void Update(sf::Time _frameTime);

private:
	
	bool AttemptMove(sf::Vector2i _direction);

	//data
private:

	sf::Vector2i m_pendingMove;
	sf::Sound m_moveSound;
	sf::Sound m_blockSound;
	sf::Sound m_boxMoveSound;

};