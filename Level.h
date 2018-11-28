#pragma once

//library includes
#include <SFML/Graphics.hpp>
#include "gridObject.h"

class Level
{

public:
	Level();

	void Draw(sf::RenderTarget& _Target);
	void Update(sf::Time _FrameTime);
	void Input(sf::Event _gameEvent);

	void LoadLevel(int _LevelToLoad);
	void ReloadLevel();
	void LoadNextLevel();

	float GetCellSize();
	bool MoveObjectTo(GridObject* _toMove, sf::Vector2i targetPos);

private:

	const float m_cellSize;
	int m_CurrentLevel;
	std::vector<std::vector < sf::Sprite > > m_background;
	std::vector<std::vector<std::vector<GridObject*>  >  > m_contents;
};