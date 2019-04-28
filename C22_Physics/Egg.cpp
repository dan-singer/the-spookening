#include "Egg.h"
#include "Player.h"
#include "MyEntityManager.h"
#include "Farmer.h"
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

	Farmer* farmer = dynamic_cast<Farmer*>(a_pOther);
	if (a_pOther->GetUniqueID() == "ground") {
		m_isMoving = false;
		m_isBeingDestroyed = true;
	}
	else if(farmer){

		if (a_pOther->GetType() == "Pig")
		{
			MyEntity* bacon = new MyEntity("Breakfast\\model.obj", "");
			MyEntityManager::GetInstance()->AddEntity(bacon);
			bacon->SetModelMatrix(glm::translate(GetPosition() + vector3(0, -1.0f, 0)) * glm::scale(bacon->GetModelMatrix(), vector3(5.0f)));
		}
		else if (a_pOther->GetType() == "Farmer")
		{
			MyEntity* grave = new MyEntity("Grave\\grave.obj", "");
			MyEntityManager::GetInstance()->AddEntity(grave);
			grave->SetModelMatrix(glm::translate(GetPosition() + vector3(0,-7.5f,0)) * glm::scale(grave->GetModelMatrix(), vector3(0.3f)));
		}

		// Remove this entity immediately if collided with pig or farmer
		MyEntityManager::GetInstance()->RemoveEntity(GetUniqueID());

		MyEntityManager::GetInstance()->RemoveEntity(a_pOther->GetUniqueID());
		Player::GetInstance()->AddPoints(a_pOther);
	}
}


