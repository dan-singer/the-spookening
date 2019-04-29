#include "TimedRemoval.h"
#include "MyEntityManager.h"

Simplex::TimedRemoval::TimedRemoval(String a_sFileName, string type, String a_sUniqueID):MyEntity(a_sFileName, type, a_sUniqueID)
{
}

void Simplex::TimedRemoval::Update(float deltaTime)
{
	timer -= deltaTime;
	if (timer <= 0.0) {

		MyEntityManager::GetInstance()->RemoveEntity(GetUniqueID());

	}
}
