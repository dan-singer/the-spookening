#include "Farmer.h"
#include "MyEntityManager.h"
using namespace Simplex;

Farmer::Farmer(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID)
{
	// timer = fDeltatime * FPS;
	// save to a variable
	// finalize the physics resolution
}


void Simplex::Farmer::Update(float deltaTime)
{
	// m_fCooldownTimer -= deltaTime;
	// update the position
	// position = vector3(position + (direction * 1 / 20.0f));
	SetPos(vector3(GetPos() + (GetDir() * 1 / 20.0f)));

	// HAHAHAHAHAAH IT ROTATES CORRECTLY

	// get the angle between the x and z and create a rotation matrix around the Y axis
	double angle = std::atan2(GetDir().x, GetDir().z);
	matrix4 rot = glm::rotate(angle, glm::tvec3<double>(0.0, 1.0, 0.0));

	// get the angle counter angle and create a rotation matrix around the Z axis
	double angleY = -std::asin(GetDir().y);
	matrix4 rotY = glm::rotate(angleY, glm::tvec3<double>(0.0, 0.0, 1.0));

	// calculate the final rotation matrix
	matrix4 rotation = rot * rotY;

	// create a new matrix with the postion, rotation, and scale
	matrix4 newMat4 = glm::translate(GetPos()) * rotation * glm::scale(vector3(2.0f));

	// set the model matrix to be the new matrix
	SetModelMatrix(newMat4);
}

Farmer::~Farmer()
{
}
