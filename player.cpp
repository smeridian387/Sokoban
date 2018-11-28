//project include
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Level.h"

Player::Player()
	:GridObject()
{

	m_Sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));
}

void Player::Input(sf::Event _gameEvent)
{
	//Read the in put from the keyboard and convert it to a direction to move in

	//was the event a key press?
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		//yes it was a key press!

		//what key was pressed?
		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			//it was W 
			//move up
			AttempMove(sf::Vector2i(0, -1));

		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			//it was A 
			//move left
			AttempMove(sf::Vector2i(-1,0));

		}
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			//it was S 
			//move down
			AttempMove(sf::Vector2i(0, 1));

		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			//it was D 
			//move Right
			AttempMove(sf::Vector2i(1,0));

		}

	}

}

bool Player::AttempMove(sf::Vector2i _direction)
{
	//attempting to move in the given direction

	// get current position 
	//calculate target position 
	sf::Vector2i targetPos = m_gridPosition + _direction;

	//TODO: check if the sace in empty

	//if empty, move there
	return m_level->MoveObjectTo(this, targetPos);
}