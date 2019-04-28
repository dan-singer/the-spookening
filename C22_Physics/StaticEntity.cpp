#include "StaticEntity.h"

using namespace Simplex;

StaticEntity::StaticEntity(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{
}

void Simplex::StaticEntity::Update(float deltaTime)
{
	SetModelMatrix(glm::translate(GetPos()) * glm::scale(GetScale()));
}

void Simplex::StaticEntity::ResolveCollision(MyEntity* other)
{
	StaticEntity* staticOther = dynamic_cast<StaticEntity*>(other);
	if (staticOther) 
	{
		// Get the center of the two entities
		vector3 center = (GetPos() + staticOther->GetPos()) / 2.0f;
		// Add to position based on this
		vector3 offset = (GetPos() - center);
		offset /= offset.length();
		SetPos(GetPos() + offset);
	}
}


StaticEntity::~StaticEntity()
{
}
