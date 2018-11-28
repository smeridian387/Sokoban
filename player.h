#pragma once
//project includes
#include "gridObject.h"

class Player : public GridObject
{
public:

	Player();

	// overriding method
	virtual void Input(sf::Event _gameEvent);

private:

	bool AttempMove(sf::Vector2i _direction);

};