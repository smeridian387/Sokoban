//project include
#include "Storage.h"
#include "Framework/AssetManager.h"

Storage::Storage()
	:GridObject()
{

	m_Sprite.setTexture(AssetManager::GetTexture("graphics/storage.png"));
}