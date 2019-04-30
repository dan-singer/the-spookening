#include "Egg.h"
#include "Player.h"
#include "MyEntityManager.h"
#include "Farmer.h"
#include "TimedRemoval.h"
using namespace Simplex;

Egg::Egg(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{

}

void Simplex::Egg::Update(float deltaTime)
{
	// if moving, move the egg down
	if (m_isMoving) {
		SetModelMatrix(glm::translate(GetModelMatrix(), vector3(0, -m_speed * deltaTime, 0)));
	}
	// if being destoryed, increase timer and check if timer done
	if (m_isBeingDestroyed) {
		m_destroyCounter += deltaTime;
		if (m_destroyCounter > m_destroyTimer)
		{
			MyEntityManager::GetInstance()->RemoveEntity(GetUniqueID());
			m_isBeingDestroyed = false;
		}
	}
}


Egg::~Egg() {
	cout << "Egg destructor!\n";
}

void Simplex::Egg::ResolveCollision(MyEntity* a_pOther)
{
	// hit the ground, stop moving and start being destoryed
	Farmer* farmer = dynamic_cast<Farmer*>(a_pOther);
	if (a_pOther->GetUniqueID() == "ground") {
		m_isMoving = false;
		m_isBeingDestroyed = true;

		delete farmer;
		farmer = nullptr;
	}
	else if(farmer){
		// hit a pig, destroy it and self, and create breakfast object at its position
		if (a_pOther->GetType() == "Pig")
		{
			TimedRemoval* bacon = new TimedRemoval("Breakfast\\model.obj", "");
			MyEntityManager::GetInstance()->AddEntity(bacon);
			bacon->SetModelMatrix(glm::translate(GetPosition() + vector3(0, -1.0f, 0)) * glm::scale(bacon->GetModelMatrix(), vector3(5.0f)));
		}
		// hit a farmer, destroy it and self, and create grave object at its position
		else if (a_pOther->GetType() == "Farmer")
		{
			TimedRemoval* grave = new TimedRemoval("Grave\\grave.obj", "");
			MyEntityManager::GetInstance()->AddEntity(grave);
			grave->SetModelMatrix(glm::translate(GetPosition() + vector3(0,-7.5f,0)) * glm::scale(grave->GetModelMatrix(), vector3(0.3f)));
		}

		// Remove this entity immediately if collided with pig or farmer
		MyEntityManager::GetInstance()->RemoveEntity(GetUniqueID());

		MyEntityManager::GetInstance()->RemoveEntity(a_pOther->GetUniqueID());
		Player::GetInstance()->AddPoints(a_pOther);
	}
}


