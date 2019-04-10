#include "Egg.h"

using namespace Simplex;

Egg::Egg(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{

}

void Simplex::Egg::Update(float deltaTime)
{
	SetModelMatrix(glm::translate(GetModelMatrix(), vector3(0, -m_speed * deltaTime, 0)));
}


Egg::~Egg()
{
}
