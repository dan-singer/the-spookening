#include "Player.h"

using namespace Simplex;

Player::Player(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{
}

void Simplex::Player::Update(float deltaTime)
{
	m_fCooldownTimer -= deltaTime;
}

void Simplex::Player::DropEgg()
{
	if (m_fCooldownTimer <= 0)
	{		
		// Spawn an egg
		std::cout << "Spawning an egg" << std::endl;
		EntityManager::GetInstance()->AddEntity("Minecraft\\Cube.obj", "ground");
		m_fCooldownTimer = m_fStartingTimer;
	}
}


Player::~Player()
{
}
