#pragma once
//project includes
#include "Framework/SpriteObject.h"

//Forward Declaration
//Only works with pointers/references
class Level;


class GridObject : public SpriteObject
{



public:

	GridObject();

	void SetGridPosition(sf::Vector2i _newPosition);
	void SetGridPosition(int _x, int _y);
	
	void SetLevel(Level* _newLevel);

	sf::Vector2i GetGridPosition();
	bool GetBlocksMovement();
	bool GetCollectable();

protected :

	sf::Vector2i m_gridPosition;
	Level* m_level;
	bool m_blocksMovement;
	bool m_collectable;
};