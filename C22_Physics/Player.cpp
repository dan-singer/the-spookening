#include "Player.h"
#include "MyEntityManager.h"
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
		MyEntityManager* manager = MyEntityManager::GetInstance();
		Egg* toDrop = new Egg("Minecraft\\Cube.obj", "");
		manager->AddEntity(toDrop);
		manager->SetModelMatrix(glm::translate(GetPosition() + vector3(0, -2, 0)));
		manager->UsePhysicsSolver(false);

		m_fCooldownTimer = m_fStartingTimer;
	}
}


Player::~Player()
{
	std::cout << "Player destructor!\n";
}
