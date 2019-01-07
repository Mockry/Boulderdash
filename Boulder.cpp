
//project includes
#include "Boulder.h"
#include "Framework/AssetManager.h"
#include "Level.h"

Boulder::Boulder()
	: GridObject()

{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Box.png"));
	m_blocksMovement = true;
}

bool Boulder::AttemptFall(sf::Vector2i _direction)
{
	// Attempting to move in given direction

	//get current position
	//calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	//check if the space is empty
	//Get list of objects in target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	bool blocked = false;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
		}
	}

	//if empty, move there
	if (blocked == false)
	{
		return m_level->MoveObjectTo(this, targetPos);
	}
	//if movement is blocked,return false
	else
		return false;

}

void Boulder::Update(sf::Time _frametime)
{
	AttemptFall(sf::Vector2i(0,1));
}
