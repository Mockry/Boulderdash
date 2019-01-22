
//project includes
#include "Wall.h"
#include "Framework/AssetManager.h"

Wall::Wall()
	: GridObject()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/Wall.JPG"));
	m_blocksMovement = true;
}

