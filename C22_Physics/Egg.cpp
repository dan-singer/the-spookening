#include "Egg.h"
#include "Player.h"
#include "MyEntityManager.h"
using namespace Simplex;

Egg::Egg(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{

}

void Simplex::Egg::Update(float deltaTime)
{
	if (m_isMoving) {
		SetModelMatrix(glm::translate(GetModelMatrix(), vector3(0, -m_speed * deltaTime, 0)));
	}
	if (m_isBeingDestroyed) {
		m_destroyCounter += deltaTime;
		if (m_destroyCounter > m_destroyTimer)
		{
			MyEntityManager::GetInstance()->RemoveEntity(GetUniqueID());
			m_isBeingDestroyed = false;
		}
	}
}


Egg::~Egg()
{
}

void Simplex::Egg::ResolveCollision(MyEntity* a_pOther)
{
	Egg* otherEgg = dynamic_cast<Egg*>(a_pOther);

	if (a_pOther->GetUniqueID() == "ground") {
		m_isMoving = false;
		m_isBeingDestroyed = true;
	}
	else if(!otherEgg){
		MyEntityManager::GetInstance()->RemoveEntity(a_pOther->GetUniqueID());
		MyEntity* bacon = new MyEntity("Bacon\\Bacon Slice.obj", "test");
		MyEntityManager::GetInstance()->AddEntity(bacon);
		bacon->SetModelMatrix(glm::translate(GetPosition()) * glm::scale(bacon->GetModelMatrix(), vector3(0.001f)));

		Player::GetInstance()->AddPoints(a_pOther);
	}
}


