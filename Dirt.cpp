
//project includes
#include "Dirt.h"
#include "Framework/AssetManager.h"

Dirt::Dirt()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Dirt.jpg"));
	m_blocksMovement = true;
	m_collectable = true;
}

