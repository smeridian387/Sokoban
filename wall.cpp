//project include
#include "wall.h"
#include "Framework/AssetManager.h"

Wall::Wall()
	:GridObject()
{

	m_sprite.setTexture(AssetManager::GetTexture("graphics/wall.png"));
}