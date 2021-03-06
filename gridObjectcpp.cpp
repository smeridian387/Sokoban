//project includes
#include "gridObject.h"
#include "Level.h"

GridObject::GridObject()
	:SpriteObject()
	, m_gridPosition(0, 0)
	,m_level(nullptr)
{


}

void GridObject::SetGridPosition(sf::Vector2i _newPostion)
{
	m_gridPosition = _newPostion;
	m_Sprite.setPosition(m_gridPosition.x * m_level->GetCellSize(),
		m_gridPosition.y * m_level->GetCellSize());
}

void GridObject::SetGridPosition(int _x, int _y)
{
	SetGridPosition(sf::Vector2i(_x, _y));
}

void GridObject::SetLevel(Level* _newLevel)
{
	m_level = _newLevel;

}

sf::Vector2i GridObject::GetGridPosition()
{
	return m_gridPosition;

}
