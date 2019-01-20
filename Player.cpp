
//project includes
#include "Player.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "Boulder.h"

Player::Player()
	: GridObject()
	, m_pendingMove(0,0)
	, m_moveSound()
	, m_blockSound()
	, m_boxMoveSound()
{
	m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandRight.png"));
	m_moveSound.setBuffer(AssetManager::GetSoundBuffer("audio/footstep1.ogg"));
	m_blockSound.setBuffer(AssetManager::GetSoundBuffer("audio/footstep3.ogg"));
	m_boxMoveSound.setBuffer(AssetManager::GetSoundBuffer("audio/push.wav"));

}


void Player::Input(sf::Event _gameEvent)
{
	//Read the input from the keyboard and convert it to a direction
	// to move in (and then move)

	// Was the event a keypress?
	if (_gameEvent.type == sf::Event::KeyPressed)
	{
		//Yes it was a key press!

		//what key was pressed?
		if (_gameEvent.key.code == sf::Keyboard::W)
		{
			// it was W!
			//Move Up
			m_pendingMove = sf::Vector2i(0, -1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandUp.png"));

		}
		else if (_gameEvent.key.code == sf::Keyboard::A)
		{
			// it was A!
			//Move left
			m_pendingMove = sf::Vector2i(-1, 0);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandLeft.png"));

		}
		else if (_gameEvent.key.code == sf::Keyboard::S)
		{
			// it was S!
			//Move down
			m_pendingMove = sf::Vector2i(0, 1);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandDown.png"));

		}
		else if (_gameEvent.key.code == sf::Keyboard::D)
		{
			// it was D!
			//Move right
			m_pendingMove = sf::Vector2i(1, 0);
			m_sprite.setTexture(AssetManager::GetTexture("graphics/player/playerStandRight.png"));

		}
	}
}

void Player::Update(sf::Time _frameTime)
{
	//If we have movement waiting to be processed
	if (m_pendingMove.x != 0 || m_pendingMove.y != 0)
	{
		//move in that direction
		bool moveSuccessful = AttemptMove(m_pendingMove);

		if (moveSuccessful == true)
		{
			m_moveSound.play();
		}

		if (moveSuccessful == false)
		{
			m_blockSound.play();
		}
		// and clear the pending movement
		m_pendingMove = sf::Vector2i(0, 0);
	}
}

bool Player::GetPendingLoad()
{
	return m_pendingLoad;
}

bool Player::AttemptMove(sf::Vector2i _direction)
{
	// Attempting to move in given direction

	//get current position
	//calculate target position
	sf::Vector2i targetPos = m_gridPosition + _direction;

	//check if the space is empty
	//Get list of objects in target position
	std::vector<GridObject*> targetCellContents = m_level->GetObjectAt(targetPos);

	//check if any objects block movement and if it is collectable

	bool collectable = false;
	bool blocked = false;
	GridObject* blocker = nullptr;
	for (int i = 0; i < targetCellContents.size(); ++i)
	{
		if (targetCellContents[i]->GetOpen() == true)
		{
			m_level->SetReadyToLoad();
		}

		if (targetCellContents[i]->GetCollectable() == true)
		{
			collectable = true;
		}

		if (targetCellContents[i]->GetBlocksMovement() == true)
		{
			blocked = true;
			blocker = targetCellContents[i];
		}		
		

	}

	//if empty, move there
	if (blocked == false)
	{
		return m_level->MoveObjectTo(this, targetPos);
	}
	if (collectable == true)
	{
		m_level->AttemptDelete(blocker);
		return m_level->MoveObjectTo(this, targetPos);
	}
	Boulder* pushableBoulder = dynamic_cast<Boulder*>(blocker);
	if (pushableBoulder != nullptr)
	{
		// Attempt to push!
		bool pushSucceeded = pushableBoulder->AttemptPush(_direction);

		// If push succeeded
		if (pushSucceeded == true)
		{
			// Move to new spot (where blocker was)
			return m_level->MoveObjectTo(this, targetPos);
		}
	}
	

	//if movement is blocked,return false
	return false;
}
