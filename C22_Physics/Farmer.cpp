#include "Farmer.h"
#include "Player.h"
#include "MyEntityManager.h"
using namespace Simplex;

Farmer::Farmer(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{
	// timer = fDeltatime * FPS;
	// save to a variable
	// finalize the physics resolution
	SetScale(vector3(2.0f));

	//
	double angle = std::atan2(GetDir().x, GetDir().z);
	matrix4 rot = glm::rotate(angle, glm::tvec3<double>(0.0, 1.0, 0.0));

	// get the angle counter angle and create a rotation matrix around the Z axis
	double angleY = -std::asin(GetDir().y);
	matrix4 rotY = glm::rotate(angleY, glm::tvec3<double>(0.0, 0.0, 1.0));

	// calculate the final rotation matrix
	matrix4 rotation = rot * rotY;
	matrixRot4 = rotation;
}


void Simplex::Farmer::Update(float deltaTime)
{
	SetDir(matrixRot4[2]);

	// m_fCooldownTimer -= deltaTime;
	// update the position
	// position = vector3(position + (direction * 1 / 20.0f));
	SetPos(vector3(GetPos() + (GetDir() * 1 / 20.0f)));

	// create a new matrix with the postion, rotation, and scale
	matrix4 newMat4 = glm::translate(GetPos()) * matrixRot4 * glm::scale(GetScale());

	// set the model matrix to be the new matrix
	SetModelMatrix(newMat4);
}

Farmer::~Farmer()
{
}

void Simplex::Farmer::ResolveCollision(MyEntity* a_pOther)
{
	Player* temp = Player::GetInstance();

	if (a_pOther->GetUniqueID() != "ground" && temp->GetGameTime() < temp->GetGameTimeStart() - 0.0000000000000000001f)
	{
		double angle = std::atan2(a_pOther->GetDir().x, a_pOther->GetDir().z);
		matrix4 rot = glm::rotate((angle / 2), glm::tvec3<double>(0.0f, 1.0f, 0.0f));

		double angleY = -std::asin(a_pOther->GetDir().y);
		matrix4 rotY = glm::rotate((angleY / 2), glm::tvec3<double>(0.0f, 0.0f, 1.0f));

		matrix4 rotation = rot * rotY;
		matrixRot4 = rotation; 
	}
}

void Simplex::Farmer::calcRot()
{
	double angle = std::atan2(GetDir().x, GetDir().z);
	matrix4 rot = glm::rotate(angle, glm::tvec3<double>(0.0, 1.0, 0.0));

	// get the angle counter angle and create a rotation matrix around the Z axis
	double angleY = -std::asin(GetDir().y);
	matrix4 rotY = glm::rotate(angleY, glm::tvec3<double>(0.0, 0.0, 1.0));

	// calculate the final rotation matrix
	matrix4 rotation = rot * rotY;
	matrixRot4 = rotation;
}
