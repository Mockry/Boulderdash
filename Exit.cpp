
//project includes
#include "Exit.h"
#include "Framework/AssetManager.h"
#include"Level.h"

Exit::Exit()
	: GridObject()
	
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
	m_blocksMovement = true;
	m_open = false;
}


void Exit::SetOpen()
{
	m_open = m_level->CheckGems();
}



void Exit::Update(sf::Time _frameTime)
{
	SetOpen();

	if (m_open == false)
	{
		m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
	}
	if (m_open == true)
	{
		m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorOpen.png"));
	}
}

