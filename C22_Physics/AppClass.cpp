#include "AppClass.h"
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <iostream>
//#include <nanogui/nanogui.h>

#include "StaticEntity.h"
using namespace std;
using namespace Simplex;



void Application::InitVariables(void) {
	// Preload egg, bacon
	Egg* toDrop = new Egg("Egg\\egg.fbx", "");
	MyEntity entity("Breakfast\\model.obj", "");
	MyEntity* grave = new MyEntity("Grave\\grave.obj", "");


	m_pLightMngr->SetPosition(vector3(0.0f, 3.0f, 13.0f), 1); //set the position of first light (0 is reserved for ambient light)

	m_player = new Player("Chicken\\chicken.obj", "", "Player");
	m_pEntityMngr->AddEntity(m_player);

	m_pEntityMngr->UsePhysicsSolver(false);

	float playerScale = 0.05f;
	m_player->SetModelMatrix(glm::translate(vector3(MAP_SIZE/2, 80, MAP_SIZE/2)) * glm::scale(vector3(playerScale,playerScale,playerScale)) * glm::rotate(IDENTITY_M4, glm::radians(180.0f), AXIS_Y));
	m_cameraOffset = vector3(0, 6, 0); // this was set to 6

	// ground
	MyEntity* temp = m_pEntityMngr->AddEntity("Minecraft\\Cube.obj", "", "ground");
	temp->SetType("Ground");

	vector3 v3Position = vector3(-5, -10, -5);
	v3Position.y = 0.0f;
	matrix4 m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(m4Position * glm::scale(vector3(MAP_SIZE, 1, MAP_SIZE)));
	m_pEntityMngr->UsePhysicsSolver(false);

	// endscreen object
	MyEntity* endScreen = m_pEntityMngr->AddEntity("GameScreens\\GameStates.obj", "EndScreen", "EndScreen");
	v3Position = vector3(MAP_SIZE/2, 200, MAP_SIZE/2 - 20);
	m4Position = glm::translate(v3Position);
	endScreen->SetModelMatrix((glm::translate(v3Position) * glm::scale(vector3(1)) * glm::rotate(IDENTITY_M4, glm::radians(90.0f), AXIS_X)));
	//m_pEntityMngr->SetModelMatrix(glm::translate(v3Position) * glm::scale(vector3(1)) * glm::rotate(IDENTITY_M4, glm::radians(90.0f), AXIS_X)); // this is the rotation needed for the title screen

	temp = m_pEntityMngr->AddEntity("GameScreens\\black.obj", "", "BlackBox");
	v3Position = vector3(MAP_SIZE/2, 300, MAP_SIZE/2);
	//m4Position = glm::translate(v3Position);
	m_pEntityMngr->SetModelMatrix(glm::translate(v3Position) * glm::scale(vector3(10)));

	// left wall of "fences"
	for (int i = 0; i < PIPES_PER_SIDE; i++) {
		MyEntity* otherTemp = m_pEntityMngr->AddEntity("Mario\\WarpPipe.obj", "FenceLeft", "FenceLeft");
		m_pEntityMngr->SetModelMatrix(glm::translate(vector3(-5, 0, i * 10)) * glm::scale(vector3(2.5)) * glm::rotate(IDENTITY_M4, glm::radians(90.0f), AXIS_Z));
	}

	// right wall of fences
	for (int i = 0; i < PIPES_PER_SIDE; i++) {
		MyEntity* otherTemp = m_pEntityMngr->AddEntity("Mario\\WarpPipe.obj", "FenceRight", "FenceRight");
		m_pEntityMngr->SetModelMatrix(glm::translate(vector3(MAP_SIZE - 5, 0, i * 10)) * glm::scale(vector3(2.5)) * glm::rotate(IDENTITY_M4, glm::radians(-90.0f), AXIS_Z));
	}

	// top wall of fences
	for (int i = 0; i < PIPES_PER_SIDE; i++) {
		MyEntity* otherTemp = m_pEntityMngr->AddEntity("Mario\\WarpPipe.obj", "FenceTop", "FenceTop");
		m_pEntityMngr->SetModelMatrix(glm::translate(vector3(i * 10, 0, - 5)) * glm::scale(vector3(2.5)) * glm::rotate(IDENTITY_M4, glm::radians(-90.0f), AXIS_X));
	}

	// bottom wall of fences
	for (int i = 0; i < PIPES_PER_SIDE; i++) {
		MyEntity* otherTemp = m_pEntityMngr->AddEntity("Mario\\WarpPipe.obj", "FenceBottom", "FenceBottom");
		m_pEntityMngr->SetModelMatrix(glm::translate(vector3(i * 10, 0, MAP_SIZE - 5)) * glm::scale(vector3(2.5)) * glm::rotate(IDENTITY_M4, glm::radians(90.0f), AXIS_X));
	}

	// seed random
	srand(time(NULL));

	// code for spawning multiple pigs
	for (int i = 0; i < ENEMY_COUNT; i++) {
		// create an enemy
		SpawnType spawnType = static_cast<SpawnType>(rand() % (int)SpawnType::NUM_TYPES);

		MyEntity* temp = nullptr;
		if (spawnType == SpawnType::Farmer) {
			temp = new Farmer("Minecraft\\Steve.obj", "Farmer", "Farmer_" + std::to_string(numFarmers));
			numFarmers++;
		}
		else if (spawnType == SpawnType::Pig) {
			temp = new Farmer("Minecraft\\Pig.obj", "Pig", "Pig_" + std::to_string(numPigs));
			numPigs++;
		}

		// create a random position
		vector3 v3Position = vector3(rand() % (int)MAP_SIZE, 1.1, rand() % (int)MAP_SIZE);
		temp->SetPos(v3Position);
		
		// create a random direction
		vector3 v3Direction = vector3(rand() % 2, 0, rand() % 2);

		// check that both values are not zero
		if (v3Direction.x == 0 && v3Direction.z == 0) {
			// if so, set one of the values to 1
			if (rand() % 2 > 0) { v3Direction.x = 1; }
			else { v3Direction.z = 1; }
		}

		// set the direction
		temp->SetDir(v3Direction);
		temp->SetMapSize(MAP_SIZE);

		Farmer* farmer = dynamic_cast<Farmer*>(temp);
		if (farmer) {
			farmer->calcRot();
		}
		m_pEntityMngr->AddEntity(temp);
	}

	

	// spawning loop for the static objects
	for (int i = 0; i < STATIC_COUNT; i++) {

		MyEntity* spawnedStaticObject = nullptr;
		// spawn rock object
		spawnedStaticObject = new StaticEntity("StaticObjects\\rock.obj", "Static", "Rock_" + std::to_string(numRocks));
		spawnedStaticObject->SetScale(vector3(0.05f, 0.05f, 0.05f));
		numRocks++;

		// do this within a check for octree collisions stuff
		// set positions

		vector3 v3Position = vector3(rand() % (int)(MAP_SIZE - MARGIN * 2) + MARGIN, 1.1, rand() % (int)(MAP_SIZE - MARGIN * 2));
		spawnedStaticObject->SetPos(v3Position);
		m_pEntityMngr->AddEntity(spawnedStaticObject);
	}
	
	m_pEntityMngr->Update();
	m_pRoot = new MyOctant(m_uOctantLevels,5); // also please dont touch this, begging you yadda yadda
	
	//nanogui::Button* b;
	//nanogui::Button* b = new nanogui::Button(m_pWindow->getSystemHandle());
}

void Application::Update(void) {
	if (m_bStartGame) {

		//Update the system so it knows how much time has passed since the last call
		m_pSystem->Update();

		m_pCameraMngr->SetFOV(45);

		vector3 camPosition = m_player->GetPosition() + m_cameraOffset;

		//Set the position and target of the camera
		m_pCameraMngr->SetPositionTargetAndUpward(
			camPosition,				// Position
			m_player->GetPosition(),	// Target
			-AXIS_Z);					// Up

		// set endgame state
		if (m_player->GetGameTime() <= 0.0) {
			m_pCameraMngr->SetFOV(101);
			vector3 v3Position = vector3(MAP_SIZE / 2, 200, MAP_SIZE / 2);
			matrix4 m4Position = glm::translate(v3Position);

			m_pEntityMngr->GetEntity(m_pEntityMngr->GetEntityIndex("EndScreen"))->SetModelMatrix(glm::translate(v3Position) * glm::scale(vector3(1)) * glm::rotate(IDENTITY_M4, glm::radians(180.0f), AXIS_X) * glm::rotate(IDENTITY_M4, glm::radians(180.0f), AXIS_Y)); // This is for the end state screen
			camPosition = vector3(MAP_SIZE / 2, 80, MAP_SIZE / 2) + m_cameraOffset;

			m_pCameraMngr->SetPositionTargetAndUpward(
				camPosition,			// Position
				vector3(MAP_SIZE / 2, 200, MAP_SIZE / 2),
				AXIS_Z);
			m_player->SetGameTime(0.0);
		}

		//Update Entity Manager
		m_pEntityMngr->Update();

		//Add objects to render list
		m_pEntityMngr->AddEntityToRenderList(-1, true);
	}
	else {
		m_player->SetGameTime(m_player->GetGameTimeStart()); // resets the timer to show the correct starting time amount on game start

		//Add objects to render list
		m_pEntityMngr->AddEntityToRenderList(2, true);
		m_pEntityMngr->AddEntityToRenderList(3, true);

		m_pCameraMngr->SetFOV(101);
		vector3 camPosition = vector3(MAP_SIZE / 2, 80, MAP_SIZE / 2) + m_cameraOffset;

		m_pCameraMngr->SetPositionTargetAndUpward(
			camPosition,			// Position
			vector3(MAP_SIZE / 2, 200, MAP_SIZE / 2),
			AXIS_Z);
	}
}
void Application::Display(void) {
	// Clear the screen
	ClearScreen();

	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList("SpookySky.png");

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	if (m_displayOctree)
		m_pRoot->Display();

	m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();

	//draw gui,
	DrawGUI();

	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void) {
	//Release MyEntityManager
	MyEntityManager::ReleaseInstance();

	//release GUI
	ShutdownGUI();
}