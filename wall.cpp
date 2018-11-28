//project include
#include "wall.h"
#include "Framework/AssetManager.h"

Wall::Wall()
	:GridObject()
{

	m_Sprite.setTexture(AssetManager::GetTexture("graphics/wall.png"));
}