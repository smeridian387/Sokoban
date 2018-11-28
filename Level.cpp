//project includes
#include "Level.h"
#include "Framework/AssetManager.h"
#include "wall.h"
#include "storage.h"
#include "player.h"

//library includes
#include <iostream>
#include <fstream>

Level::Level()
	:m_cellSize(64.0f)
	,m_CurrentLevel(0)
	,m_background()
	,m_contents()

{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _Target)
{
	//create and update camera
	sf::View camera = _Target.getDefaultView();

	//adjust camera as needed
	camera.setCenter(m_background[0].size() * m_cellSize /2 ,m_background.size() * m_cellSize/2);

	// Draw game world to the window
	_Target.setView(camera);
	for (int y = 0; y < m_background.size(); ++y)
	{
		for (int x = 0; x < m_background[y].size(); ++x)
		{
			_Target.draw(m_background[y][x]);

		}

	}

	//rows
	for (int y = 0; y < m_contents.size(); y++)
	{
		//coloumbs
		for (int x = 0; x < m_contents[y].size(); x++)
		{
			//grid object
			for (int z = 0; z < m_contents[y][x].size(); z++)
			{
				m_contents[y][x][z]->Draw(_Target);

			}

		}

	}

	// TODO Draw game objects

	//TODO Adjust camera as needed

	// Reset view
	_Target.setView(_Target.getDefaultView());

}

void Level::Update(sf::Time _FrameTime)
{
	//TODO
}

void Level::Input(sf::Event _gameEvent)
{
	//rows
	for (int y = 0; y < m_contents.size(); y++)
	{
		//coloumbs
		for (int x = 0; x < m_contents[y].size(); x++)
		{
			//grid object
			for (int z = 0; z < m_contents[y][x].size(); z++)
			{
				m_contents[y][x][z]->Input(_gameEvent);

			}

		}

	}

}

void Level::LoadLevel(int _LevelToLoad)
{
	//Clean up the old level

	//Delete any data already in the level
	//rows
	for (int y = 0; y < m_contents.size(); y++)
	{
		//coloumbs
		for (int x = 0; x < m_contents[y].size(); x++)
		{
			//grid object
			for (int z = 0; z < m_contents[y][x].size(); z++)
			{
				delete m_contents[y][x][z];

			}

		}

	}
	
	//clear out our lists
	m_background.clear();
	m_contents.clear();
	   	  
	//set the current level
	m_CurrentLevel = _LevelToLoad;

	//-=Set up the new level=-

	// Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level" + std::to_string(m_CurrentLevel) + ".txt";
	inFile.open(fileName);

	// make sure the file was opened
	if (!inFile)
	{
		std::cerr << "Unable to open file " + fileName;
		exit(1); // call system to stop program with error

	}

	// set the starting X and Y coordinates used to position level objects
	int x = 0.0f;
	int y = 0.0f;

	m_background.push_back(std::vector<sf::Sprite>());
	m_contents.push_back(std::vector<std::vector<GridObject*>>());

	// read each character one by one from the file...
	char ch;
	//each time try to read the next character
	//if successful, execute body of loop
	//the "noskipws" means our input from the fill will include
	// the white space(spaces and new lines)
	while (inFile>> std::noskipws >> ch)
	{
		//perform actions based on what character was read in
		if (ch == ' ')
		{
			x += 1;
		}
		else if (ch == '\n')
		{
			y += 1;
			x = 0;

			//create a new row on out grid
			m_background.push_back(std::vector<sf::Sprite>());
			m_contents.push_back(std::vector<std::vector<GridObject*> >());
		}
		else
		{
			//this is going to be some object (or epty space), so we need a background

			m_background[y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_background[y][x].setPosition(x*m_cellSize, y*m_cellSize);

			//create an empty vector for our grid contents in this cell
			m_contents[y].push_back(std::vector<GridObject*>());

			if (ch == '-')
			{
				// do nothing - empty space
			}
			else if (ch == 'W')
			{
				Wall* wall = new Wall();
				wall->SetLevel(this);
				wall->SetGridPosition(x, y);
				m_contents[y][x].push_back(wall);

			}
			else if (ch == 'P')
			{
				Player* player = new Player();
				player->SetLevel(this);
				player->SetGridPosition(x, y);
				m_contents[y][x].push_back(player);

			}
			else if (ch == 'S')
			{
				Storage* storage = new Storage();
				storage->SetLevel(this);
				storage->SetGridPosition(x, y);
				m_contents[y][x].push_back(storage);

			}
			else
			{
				std::cerr << "unrecognised character in level file: " << ch << std::endl;
			}
		}
		

	}

	//close the file now that were done with it
	inFile.close();

	}

void Level::ReloadLevel()
{
	LoadLevel(m_CurrentLevel);
}

void Level::LoadNextLevel()
{
	LoadLevel(m_CurrentLevel + 1);
}

float Level::GetCellSize()
{
	return m_cellSize;


}

bool Level::MoveObjectTo(GridObject* _toMove, sf::Vector2i targetPos)
{
	//dont trust other code
	//make sure _toMove is a valid pointer
	if (_toMove != nullptr && targetPos.y >=0 && targetPos.y < m_contents.size() && targetPos.x >=0 && targetPos.x < m_contents[targetPos.y].size())
	{
		//get the current position of the grid object 
		sf::Vector2i oldPos = _toMove->GetGridPosition();

		//find the object in the list using an iterator
		//and the find method
		auto it = std::find(m_contents[oldPos.y][oldPos.x].begin(),
							m_contents[oldPos.y][oldPos.x].end(), _toMove);
		// if we found the object at this location,
		//it will NOT equal the end of the vector
		if (it != m_contents[oldPos.y][oldPos.x].end())
		{
			//we found the object

			//remove it from the old position 
			m_contents[oldPos.y][oldPos.x].erase(it);

			//add it to its new position
			m_contents[targetPos.y][targetPos.x].push_back(_toMove);

			//tell the object its new position
			_toMove->SetGridPosition(targetPos);

			//return 
			return true;

		}
	}

}
