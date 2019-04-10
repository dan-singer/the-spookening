#include "AppClass.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace Simplex;
void Application::InitVariables(void)
{
	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_pEntityMngr->AddEntity("Chicken\\gallina.fbx", "Player");
	
	m_pEntityMngr->UsePhysicsSolver(false);

	m_player = m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("Player"));
	float playerScale = 0.01f;
	m_player->SetModelMatrix(glm::translate(vector3(-7.5f, 100, -7.5f)) * glm::scale(vector3(playerScale,playerScale,playerScale)) * glm::rotate(IDENTITY_M4, glm::radians(180.0f), AXIS_Y));
	m_cameraOffset = vector3(0, 6, 0);
	

	m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "ground");
	vector3 v3Position = vector3(-5,0,-5);
	v3Position.y = 0.0f;
	matrix4 m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(100, 1, 100)));
	m_pEntityMngr->UsePhysicsSolver(false);

	// seed random
	srand(time(NULL));

	// code for spawning multiple pigs
	for (int i = 0; i < 5; i++) {
		// create a pig
		MyEntity* temp = m_pEntityMngr->AddEntity("Minecraft\\Pig.obj", "Pig_" + std::to_string(i));
		temp->SetType("Pig");

		// create a random position
		vector3 v3Position = vector3(rand() % 50, 0, rand() % 50);
		temp->SetPos(v3Position);

		// create a random direction
		vector3 v3Direction = vector3(rand() % 2, 0, rand() % 2);

		// check that both values are not zero
		if (v3Direction.x == 0 && v3Direction.z == 0)
		{
			// if so, set one of the values to 1
			if (rand() % 2 > 0) { v3Direction.x = 1; }
			else { v3Direction.z = 1; }
		}

		// set the direction
		temp->SetDir(v3Direction);
	}
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the ArcBall active?
	//ArcBall();


	vector3 camPosition = m_player->GetPosition() + m_cameraOffset;

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(
		camPosition, //Position
		m_player->GetPosition(),	//Target
		-AXIS_Z);					//Up

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Set the model matrix for the main object
	//m_pEntityMngr->SetModelMatrix(m_m4Steve, "Steve");

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
	//m_pEntityMngr->AddEntityToRenderList(-1, true);




}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}