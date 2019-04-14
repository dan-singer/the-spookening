#include "Player.h"
#include "MyEntityManager.h"
using namespace Simplex;

Player* Player::m_instance = nullptr;

Player::Player(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{
	m_instance = this;
}

Player* Simplex::Player::GetInstance()
{
	return m_instance;
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
		Egg* toDrop = new Egg("Egg\\egg.fbx", "");
		manager->AddEntity(toDrop);
		manager->SetModelMatrix(glm::translate(GetPosition() + vector3(0, -10, 0)));
		manager->UsePhysicsSolver(false);

		m_fCooldownTimer = m_fStartingTimer;
	}
}


void Simplex::Player::AddPoints(MyEntity* other)
{
	// TODO add points per thingy
	// Tree is 1 point, pig is 5 points, farmer is 10 points
	m_score++;
}

Player::~Player()
{
	std::cout << "Player destructor!\n";
}
