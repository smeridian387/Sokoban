//project includes
#include "Level.h"
#include "Wall.h"
#include "Exit.h"
#include "Player.h"
#include "Baddy.h"
#include "Score.h"
#include "Coin.h"
#include "Key.h"
#include "Hazard.h"

//library includes
#include <iostream>
#include <fstream>

Level::Level()
	:m_CurrentLevel(0)
	, m_Player(nullptr)
	, m_UpdateList()
	, m_DrawListWorld()
	, m_DrawListUI()
	, m_CollisionList()

{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _Target)
{
	//create and update camera
	sf::View Camera = _Target.getDefaultView();
	//ToDo: Follow player with camera
	Camera.setCenter(m_Player->GetPosition());
	// Draw game world to the window
	_Target.setView(Camera);

	// Draw game objects
	//only draw when active
	for (int i = 0; i < m_DrawListWorld.size(); ++i)
	{
		if (m_DrawListWorld[i]->IsActive())
			m_DrawListWorld[i]->Draw(_Target);
	}

	// Draw UI to the window
	_Target.setView(_Target.getDefaultView());

	//Draw UI objects
	for (int i = 0; i < m_DrawListUI.size(); ++i)
	{
		if (m_DrawListUI[i]->IsActive())
			m_DrawListUI[i]->Draw(_Target);
	}
}

void Level::Update(sf::Time _FrameTime)
{
	// Update all game objects
		// Only draw if the game object is active
	for (int i = 0; i < m_UpdateList.size(); ++i)
	{
		if (m_UpdateList[i]->IsActive())
			m_UpdateList[i]->Update(_FrameTime);
	}



	// Collision detection

	for (int i = 0; i < m_CollisionList.size(); ++i)
	{
		GameObject* Handler = m_CollisionList[i].first;
		GameObject* Collider = m_CollisionList[i].second;

		if (Handler->IsActive() && Collider->IsActive())
		{
			if (Handler->GetBounds().intersects(Collider->GetBounds()))
			{
				Handler->Collide(*Collider);
			}
		}
	}

}

void Level::LoadLevel(int _LevelToLoad)
{
	//Clean up the old level

	//Delete any data already in the level
	for (int i = 0; i < m_UpdateList.size(); ++i)
	{
		delete m_UpdateList[i];
	}

	//clear out our lists
	m_UpdateList.clear();
	m_DrawListWorld.clear();
	m_DrawListUI.clear();
	m_CollisionList.clear();
	   	  
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

	//create the player first as other objects will need to reference it
	Player* OurPlayer = new Player();
	m_Player = OurPlayer;

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
		else if (ch == 'P')
		{
			//create the player
			OurPlayer->SetPosition(X, Y);
			OurPlayer->SetLevel(this);
			m_UpdateList.push_back(OurPlayer);
			m_DrawListWorld.push_back(OurPlayer);
		}
		else if (ch == 'W')
		{
			//create a wall
			Wall* aWall = new Wall();
			aWall->SetPosition(X, Y);
			m_UpdateList.push_back(aWall);
			m_DrawListWorld.push_back(aWall);
			m_CollisionList.push_back(std::make_pair(OurPlayer, aWall));
		}
		else if (ch == 'C')
		{
			//create a Coin
			Coin* aCoin = new Coin();
			aCoin->SetPosition(X, Y);
			m_UpdateList.push_back(aCoin);
			m_DrawListWorld.push_back(aCoin);
			m_CollisionList.push_back(std::make_pair(aCoin, OurPlayer));
		}
		else if (ch == 'B')
		{
			//create the Baddy
			Baddy* aBaddy = new Baddy();
			aBaddy->SetPosition(X, Y);
			m_UpdateList.push_back(aBaddy);
			m_DrawListWorld.push_back(aBaddy);
		}
		else if (ch == 'K')
		{
			//create a key
			Key* aKey = new Key();
			aKey->SetPosition(X, Y);
			m_UpdateList.push_back(aKey);
			m_DrawListWorld.push_back(aKey);
			m_CollisionList.push_back(std::make_pair(aKey, OurPlayer));
		}
		else if (ch == 'E')
		{
			//create the exit
			Exit* aExit = new Exit;
			aExit->SetPosition(X, Y);
			aExit->SetPlayer(OurPlayer);
			m_UpdateList.push_back(aExit);
			m_DrawListWorld.push_back(aExit);
			m_CollisionList.push_back(std::make_pair(aExit, OurPlayer));
		}
		else if (ch == 'H')
		{
			//create a hazard
			Hazard* aHazard = new Hazard;
			aHazard->SetPosition(X, Y);
			m_UpdateList.push_back(aHazard);
			m_DrawListWorld.push_back(aHazard);
			m_CollisionList.push_back(std::make_pair(aHazard, OurPlayer));
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

	//create the score item indepentantly as it isn't dependant on the level
	Score* aScore = new Score();
	aScore->SetPosition(550.0f, 50.0f);
	m_UpdateList.push_back(aScore);
	m_DrawListUI.push_back(aScore);

	//set the address for player in Score
	aScore->SetPlayer(OurPlayer);
	}

void Level::ReloadLevel()
{
	LoadLevel(m_CurrentLevel);
}

void Level::LoadNextLevel()
{
	LoadLevel(m_CurrentLevel + 1);
}