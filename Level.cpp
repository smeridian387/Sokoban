//project includes
#include "Level.h"

//library includes
#include <iostream>
#include <fstream>

Level::Level()
	:m_CurrentLevel(0)

{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _Target)
{
	//create and update camera
	sf::View Camera = _Target.getDefaultView();

	// Draw game world to the window
	_Target.setView(Camera);

	// TODO Draw game objects

	//TODO Adjust camera as needed

	// Reset view
	_Target.setView(_Target.getDefaultView());

}

void Level::Update(sf::Time _FrameTime)
{
	//TODO
}

void Level::LoadLevel(int _LevelToLoad)
{
	//Clean up the old level

	//Delete any data already in the level
	//TODO
	
	//clear out our lists
	//TODO
	   	  
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
	float X = 0.0f;
	float Y = 0.0f;

	//Define the spacing we will use for our grid
	const float X_SPACE = 100.0f;
	const float Y_SPACE = 100.0f;

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
			X += X_SPACE;
		}
		else if (ch == '\n')
		{
			Y += Y_SPACE;
			X = 0;
		}
		else if (ch == '-')
		{
			// do nothing - empty space
		}
		else
		{
			std::cerr << "unrecognised character in level file: " << ch;
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