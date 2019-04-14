#include "Egg.h"

using namespace Simplex;

Egg::Egg(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{

}

void Simplex::Egg::Update(float deltaTime)
{
	if (m_isMoving) {
		SetModelMatrix(glm::translate(GetModelMatrix(), vector3(0, -m_speed * deltaTime, 0)));
	}
}


Egg::~Egg()
{
}

void Simplex::Egg::ResolveCollision(MyEntity * a_pOther)
{
	Egg* otherEgg = dynamic_cast<Egg*>(a_pOther);

	if (a_pOther->GetUniqueID() == "ground") {
		m_isMoving = false;
	}
	else if(!otherEgg){
		//TODO squish squash enemies yay
		a_pOther->SetModelMatrix(glm::scale(a_pOther->GetModelMatrix(), vector3(1.0f, 0.7f, 1.0f)));
	}
}


