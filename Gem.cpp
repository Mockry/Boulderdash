
//project includes
#include "Gem.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Player.h"

Gem::Gem()
	: GridObject()
	, m_timer(0.0f)
	, m_fallDelay(1.0f)

{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Gem.png"));
	m_blocksMovement = true;
	m_collectable = true;
}

bool Gem::AttemptFall(sf::Vector2i _direction, sf::Time _frametime)
{
	// Attempting to move in given direction

	//get current position
	//calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	//check if the space is empty
	//Get list of objects in target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	GridObject* blocker = nullptr;

	bool blocked = false;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		blocker = targetCellContents[i];

		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;			
			m_timer = (0.0f);
		}
	}

	//if empty start timer
	if (blocked == false)
	{
		m_timer += _frametime.asSeconds();
	}

	//move to space after 1 second
	if (m_timer > m_fallDelay)
	{
		Player* player = dynamic_cast<Player*>(blocker);
		if (player != nullptr)
		{
			m_level->SetReset();
		}

		return m_level->MoveObjectTo(this, targetPos);
	}

	//if movement is blocked return false
	else
		return false;
}

void Gem::Update(sf::Time _frametime)
{
	AttemptFall(sf::Vector2i(0, 1), _frametime);
}
