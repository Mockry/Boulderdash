
//project includes
#include "Gem.h"
#include "Framework/AssetManager.h"

Gem::Gem()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Gem.jpg"));
	m_blocksMovement = true;
	m_collectable = true;
}

