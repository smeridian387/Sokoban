#pragma once

//project includes
#include "Framework/SpriteObject.h"

//forward decleration
//only works with pointers and references

class GridObject
{

public:

	GridObject();

	void SetGridPosition(sf::Vector2i _newPostion);
	void SetGridPosition(int _x, int _y);

	void SetLevel(Level* _newLevel);

private:

	sf::Vector2i m_gridPosition;
	Level* m_level;

};