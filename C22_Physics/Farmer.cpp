#include "Farmer.h"
#include "Player.h"
#include "MyEntityManager.h"
using namespace Simplex;

Farmer::Farmer(String a_sFileName, string type, String a_sUniqueID) : MyEntity(a_sFileName, type, a_sUniqueID) {
	SetScale(vector3(2.0f));

	// angle stuffs idk
	double angle = std::atan2(GetDir().x, GetDir().z);
	matrix4 rot = glm::rotate(angle, glm::tvec3<double>(0.0, 1.0, 0.0));

	// get the angle counter angle and create a rotation matrix around the Z axis
	double angleY = -std::asin(GetDir().y);
	matrix4 rotY = glm::rotate(angleY, glm::tvec3<double>(0.0, 0.0, 1.0));

	// calculate the final rotation matrix
	matrix4 rotation = rot * rotY;
	matrixRot4 = rotation;
}

void Simplex::Farmer::Update(float deltaTime) {
	SetPos(vector3(GetPos() + (GetDir() * 1 / 20.0f)));

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

Farmer::~Farmer() {
	cout << "Farmer destructor!\n";
}

void Simplex::Farmer::ResolveCollision(MyEntity* a_pOther) {
	Player* temp = Player::GetInstance();

	if (a_pOther->GetType() == "FenceLeft") {
		vector3 warpPos = this->GetPos();

		warpPos.x = this->GetMapSize() - 10;
		this->SetPos(warpPos);
	}
	else if (a_pOther->GetType() == "FenceRight") {
		vector3 warpPos = this->GetPos();

		warpPos.x = 0;
		this->SetPos(warpPos);
	}
	else if (a_pOther->GetType() == "FenceTop") {
		vector3 warpPos = this->GetPos();

		warpPos.z = this->GetMapSize() - 10;
		this->SetPos(warpPos);
	}
	else if (a_pOther->GetType() == "FenceBottom") {
		vector3 warpPos = this->GetPos();

		warpPos.z = 0;
		this->SetPos(warpPos);
	}
	else if (a_pOther->GetType() != "Ground" && temp->GetGameTime() < temp->GetGameTimeStart() - 0.0000000000000000001f) 
    {    
        float angle = std::atan2(a_pOther->GetDir().x, a_pOther->GetDir().z);

        // fixes it so that they will move out enough to not multi-check
        if (angle < 90)
        {
            angle = 90;
        }
        
        matrix4 rot = glm::rotate((angle / 2.0f), glm::tvec3<float>(0.0, 1.0, 0.0));

        // get the angle counter angle and create a rotation matrix around the Z axis
        float angleY = -std::asin(a_pOther->GetDir().y);

        matrix4 rotY = glm::rotate((angleY / 2.0f), glm::tvec3<float>(0.0, 0.0, 1.0));

        // calculate the final rotation matrix
        matrix4 rotation = rot * rotY;

		// Get the center of the two entities
		vector3 center = (GetPos() + a_pOther->GetPos()) / 2.0f;
		// Add to position based on this
		vector3 offset = (GetPos() - center);
		offset /= offset.length();
		SetPos(GetPos() + offset);

        // create a new matrix with the postion, rotation, and scale
        matrix4 newMat4 = glm::translate(this->GetPos()) * rotation * glm::scale(vector3(2.0f));

        // rotates the direction
        glm::vec3 newDirection = glm::vec4(this->GetDir(), 1) * rot;

        // sets the direction
        this->SetDir(newDirection);

        // set the model matrix to be the new matrix
        this->SetModelMatrix(newMat4); // collision resolution between pigs
    }
}

void Simplex::Farmer::calcRot() {
	double angle = std::atan2(GetDir().x, GetDir().z);
	matrix4 rot = glm::rotate(angle, glm::tvec3<double>(0.0, 1.0, 0.0));

	// get the angle counter angle and create a rotation matrix around the Z axis
	double angleY = -std::asin(GetDir().y);
	matrix4 rotY = glm::rotate(angleY, glm::tvec3<double>(0.0, 0.0, 1.0));

	// calculate the final rotation matrix
	matrix4 rotation = rot * rotY;
	matrixRot4 = rotation;
}