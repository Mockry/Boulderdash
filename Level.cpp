//Library Includes
#include <iostream>
#include <fstream>

// Project Includes
#include "Level.h"
#include "Framework/AssetManager.h"
#include "Wall.h"
#include "Player.h"
#include "Boulder.h"
#include "Dirt.h"
#include "Gem.h"
#include "Exit.h"

Level::Level()
	: m_cellSize(64.0f)
	, m_currentLevel(1)
	, m_background()
	, m_pendingReset(false)
	, m_open(false)

{
	LoadLevel(1);
}

void Level::Draw(sf::RenderTarget& _target)
{
	sf::View camera = _target.getDefaultView();

	//adjust camera as needed
	camera.setCenter(m_background[0].size() * m_cellSize / 2
		, m_background.size() * m_cellSize / 2);



	// Draw game world to the window
	_target.setView(camera);
	for (int y = 0; y < m_background.size(); ++y)
	{
		for (int x = 0; x < m_background[y].size(); ++x)
		{
			_target.draw(m_background[y][x]);
		}
	}


	// TODO
	//draw game objects

	for (int y = 0; y < m_contents.size(); ++y)
	{
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				m_contents[y][x][z]->Draw(_target);
			}
		}
	}

	// Reset view
	_target.setView(_target.getDefaultView());


}


void Level::Update(sf::Time _frameTime)
{
	
	for (int y = 0; y < m_contents.size(); ++y)
	{
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				m_contents[y][x][z]->Update(_frameTime);
			}
		}
	}

	// calls Reload or Loadnext at the end of the update if they are pending
	if (m_pendingReset == true)
	{
		m_pendingReset = false;
		ReloadLevel();
	}

	if (m_readyToLoad == true)
	{
		m_readyToLoad = false;
		LoadNextLevel();
	}
	
}

void Level::Input(sf::Event _gameEvent)
{
	for (int y = 0; y < m_contents.size(); ++y)
	{
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				m_contents[y][x][z]->Input(_gameEvent);
			}
		}
	}
	
	
}

void Level::SetReset()
{
	m_pendingReset = true;
}

bool Level::CheckGems()
{
	// rows
	for (int y = 0; y < m_contents.size(); ++y)
	{
		// cells
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			// sticky outies (grid objects)
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				// The current object we are examining
				GridObject* thisObject = m_contents[y][x][z];

				// Check if it is a box via dynamic cast
				Gem* gemObject = dynamic_cast<Gem*>(thisObject);
				if (gemObject != nullptr)
				{
					// return false if any gems are on the map
					
					return false;
				}
				
			}
		}
	}
	return true;
}

void Level::SetReadyToLoad()
{
	m_readyToLoad = true;
}


void Level::LoadLevel(int _levelToLoad)
{
	
	// Clean up the old level

	//Delete any data already in the level
	for (int y = 0; y < m_contents.size(); ++y)
	{
		for (int x = 0; x < m_contents[y].size(); ++x)
		{
			for (int z = 0; z < m_contents[y][x].size(); ++z)
			{
				delete m_contents[y][x][z];
			}
		}
	}
	

	//Clear out our lists
	m_background.clear();
	m_contents.clear();

	// set the current level
	m_currentLevel = _levelToLoad;


	// Create new level

	// Open our file for reading
	std::ifstream inFile;
	std::string fileName = "levels/Level " + std::to_string(m_currentLevel) + ".txt";
	inFile.open(fileName);

	// Make sure the file was opened

	if (!inFile)
	{
		std::cerr << "Unable to open file " + fileName;
		exit(1);
	}

	// set the starting x and y coordinates used to position level objects
	int x = 0.0f;
	int y = 0.0f;

	//Create the first row in our grid
	m_background.push_back(std::vector<sf::Sprite>());
	m_contents.push_back(std::vector<std::vector<GridObject*> > ());


	//Reading each character one by one from the file...
	char ch;

	// Each time, try to read the next character
	//if successfule execute the loop
	while (inFile >> std::noskipws >> ch)
	{
		// Perform actions based on what character was read

		if (ch == ' ')
		{
			++x;
		}
		else if (ch == '\n')
		{
			++y;
			x = 0;

			//Create a new row in our grid
			m_background.push_back(std::vector<sf::Sprite>());
			m_contents.push_back(std::vector<std::vector<GridObject*> >());

		}

		else
		{
			// This is going to be some object (or empty space, so we need a background
			//Create background sprite
			m_background[y].push_back(sf::Sprite(AssetManager::GetTexture("graphics/ground.png")));
			m_background[y][x].setPosition(x*m_cellSize, y*m_cellSize);

			//create an empty vector for our grid contents in this cell
			m_contents[y].push_back(std::vector<GridObject*>());

		if (ch == '-')
		{
			// empty space
		}
		else if (ch == 'W')
		{
			Wall* wall = new Wall();
			wall->SetLevel(this);
			wall->SetGridPosition(x, y);
			m_contents[y][x].push_back(wall);
		}

		else if (ch == 'D')
		{
			Dirt* dirt = new Dirt();
			dirt->SetLevel(this);
			dirt->SetGridPosition(x, y);
			m_contents[y][x].push_back(dirt);
		}

		else if (ch == 'R')
		{
			Boulder* boulder = new Boulder();
			boulder->SetLevel(this);
			boulder->SetGridPosition(x, y);
			m_contents[y][x].push_back(boulder);
		}

		else if (ch == 'G')
		{
			Gem* gem = new Gem();
			gem->SetLevel(this);
			gem->SetGridPosition(x, y);
			m_contents[y][x].push_back(gem);
		}

		else if (ch == 'P')
		{
			Player* player = new Player();
			player->SetLevel(this);
			player->SetGridPosition(x, y);
			m_contents[y][x].push_back(player);
		}
		else if (ch == 'E')
		{
			Exit* exit = new Exit();
			exit->SetLevel(this);
			exit->SetGridPosition(x, y);
			m_contents[y][x].push_back(exit);
		}
		else
		{
			std::cerr << "Unrecognised character in level file;" << ch;
		}

	}
		
	}

	//close the file now that we are done with it
	inFile.close();
	


}

void Level::ReloadLevel()
{
	LoadLevel(m_currentLevel);
}

void Level::LoadNextLevel()
{
	LoadLevel(m_currentLevel + 1);
}

float Level::GetCellSize()
{
	return m_cellSize;
}

bool Level::MoveObjectTo(GridObject* _toMove, sf::Vector2i _targetPos)
{
	// don't trust other code. make sure _toMove is a valid pointer
	if (_toMove != nullptr
		//check if target position is on the grid
		&& _targetPos.y >= 0 && _targetPos.y < m_contents.size()
		&& _targetPos.x >= 0 && _targetPos.x < m_contents[_targetPos.y].size())
	{
		// get the current position of the grid object
		sf::Vector2i oldPos = _toMove -> GetGridPosition();

		// Find the object in the list using an iterator
		//and find method
		auto it = std::find(m_contents[oldPos.y][oldPos.x].begin(),
							m_contents[oldPos.y][oldPos.x].end(),
							_toMove);
		// if we found the object at this location it will not
		// equal the the end of the vector
		if (it != m_contents[oldPos.y][oldPos.x].end())
		{
			// we found the object
			m_contents[oldPos.y][oldPos.x].erase(it);

			m_contents[_targetPos.y][_targetPos.x].push_back(_toMove);
			_toMove->SetGridPosition(_targetPos);

			return true;
		}
	}

	return false;
}

bool Level::AttemptDelete(GridObject* _toMove)
{
	// don't trust other code. make sure _toMove is a valid pointer
	if (_toMove != nullptr)
	{
		// get the current position of the grid object
		sf::Vector2i oldPos = _toMove->GetGridPosition();

		// Find the object in the list using an iterator
		//and find method
		auto it = std::find(m_contents[oldPos.y][oldPos.x].begin(),
			m_contents[oldPos.y][oldPos.x].end(),
			_toMove);
		// if we found the object at this location it will not
		// equal the the end of the vector
		if (it != m_contents[oldPos.y][oldPos.x].end())
		{
			// we found the object
			delete *it;
			m_contents[oldPos.y][oldPos.x].erase(it);

			return true;
		}
	}

	return false;
}

std::vector< GridObject* > Level::GetObjectAt(sf::Vector2i _targetPos)
{
	// don't trust the data!
	// make sure the coordinates are within the vector size
	if (		//check if target position is on the grid
		   _targetPos.y >= 0 && _targetPos.y < m_contents.size()
		&& _targetPos.x >= 0 && _targetPos.x < m_contents[_targetPos.y].size())
	{
		// get the contents
		//return them
		return m_contents[_targetPos.y][_targetPos.x];
	}

	//default return
	//empty vector with nothing in it
	return std::vector<GridObject*>();
}
