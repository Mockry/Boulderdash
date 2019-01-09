
//project includes
#include "Exit.h"
#include "Framework/AssetManager.h"

Exit::Exit()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/DoorClosed.png"));
	m_blocksMovement = true;
}

