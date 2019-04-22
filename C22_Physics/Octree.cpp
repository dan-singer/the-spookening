#include "Octree.h"
#include "MyEntityManager.h"
#include <queue>
using namespace Simplex;

Octree::Octree(BoundingBox region, std::vector<uint> entities)
{
	m_region = region;
	m_entities = entities;
}

void Octree::BuildTree(int depth, int maxDepth)
{
	// Terminate if we're too deep
	if (depth > maxDepth)
	{
		return;
	}

	// Terminate if we're a leaf node
	if (m_entities.size() <= 1)
	{
		return;
	}

	vector3 dimensions = m_region.max - m_region.min;

	if (dimensions.x <= MIN_SIZE && dimensions.y <= MIN_SIZE && dimensions.z <= MIN_SIZE)
	{
		return;
	}

	vector3 half = dimensions / 2.0f;
	vector3 center = m_region.min + half;

	// Create the subdivided regions 
	BoundingBox octants[8];
	octants[0] = BoundingBox(m_region.min, center);
	octants[1] = BoundingBox(vector3(center.x, m_region.min.y, m_region.min.z), vector3(m_region.max.x, center.y, center.z));
	octants[2] = BoundingBox(vector3(center.x, m_region.min.y, center.z), vector3(m_region.max.x, center.y, m_region.max.z));
	octants[3] = BoundingBox(vector3(m_region.min.x, m_region.min.y, center.z), vector3(center.x, center.y, m_region.max.z));
	octants[4] = BoundingBox(vector3(m_region.min.x, center.y, m_region.min.z), vector3(center.x, m_region.max.y, center.z));
	octants[5] = BoundingBox(vector3(center.x, center.y, m_region.min.z), vector3(m_region.max.x, m_region.max.y, center.z));
	octants[6] = BoundingBox(center, m_region.max);
	octants[7] = BoundingBox(vector3(m_region.min.x, center.y, center.z), vector3(center.x, m_region.max.y, m_region.max.z));

	// This will contain each of the objects which fit within each octant
	std::vector<std::vector<uint>> octList;
	for (int i = 0; i < 8; ++i)
	{
		octList.push_back(std::vector<uint>());
	}

	// This will contain all of the objects which got moved down the tree and can be deslisted from this node
	std::vector<uint> delist;

	MyEntityManager* manager = MyEntityManager::GetInstance();
	for (int i = 0; i < m_entities.size(); ++i)
	{
		MyEntity* entity = manager->GetEntity(m_entities[i]);
		for (int a = 0; a < 8; ++a)
		{
			BoundingBox entityBox(entity->GetRigidBody()->GetMinGlobal(), entity->GetRigidBody()->GetMaxGlobal());

			if (octants[a].CompletelyContains(entityBox))
			{
				octList[a].push_back(m_entities[i]);
				delist.push_back(m_entities[i]);
				break;
			}
		}
	}

	// Remove objects that fit cleanly in one of the octants. Everything else remains part of this node because it must be intersecting
	for (uint id : delist)
	{
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), id));
	}


	// Make child nodes where there are items in the bounding region
	for (int a = 0; a < 8; ++a)
	{
		if (octList[a].size() != 0)
		{
			m_childNodes[a] = CreateNode(octants[a], octList[a]);
			m_activeNodes |= (1 << a);
			m_childNodes[a]->BuildTree(depth + 1, maxDepth);
		}
	}
}

void Octree::Display()
{
	DisplayOctantOnly();
	for (int flags = m_activeNodes, index = 0; flags > 0; flags >>= 1, index++)
	{
		if ((flags & 1) == 1)
		{
			if (m_childNodes[index] != nullptr)
			{
				m_childNodes[index]->Display();
			}
		}
	}
}

void Octree::Display(uint targetIndex)
{
	// Do a breadth first traversal to determine which id cooresponds to which octant
	std::queue<Octree*> breadthQueue;
	breadthQueue.push(this);
	int counter = 0;
	while (!breadthQueue.empty())
	{
		Octree* current = breadthQueue.front();
		breadthQueue.pop();
		if (counter == targetIndex)
		{
			current->DisplayOctantOnly();
			return;
		}
		counter++;
		for (int flags = current->m_activeNodes, index = 0; flags > 0; flags >>= 1, index++)
		{
			if ((flags & 1) == 1)
			{
				if (current->m_childNodes[index] != nullptr)
				{
					breadthQueue.push(current->m_childNodes[index]);
				}
			}
		}
	}


}

void Octree::DisplayOctantOnly()
{
	vector3 dimensions = m_region.max - m_region.min;
	vector3 half = dimensions / 2.0f;
	vector3 center = m_region.min + half;
	matrix4 modelMatrix = glm::translate(center) * glm::scale(dimensions);
	MeshManager::GetInstance()->AddWireCubeToRenderList(modelMatrix, vector3(0, 0, 1));
}

uint Octree::GetOctantCount()
{
	int octants = 1;
	for (int i = 0; i < 8; ++i)
	{
		if (m_childNodes[i])
		{
			octants += m_childNodes[i]->GetOctantCount();
		}
	}
	return octants;
}

Octree* Octree::CreateNode(BoundingBox region, std::vector<uint> entities)
{
	if (entities.size() == 0)
		return nullptr;
	Octree* ret = new Octree(region, entities);
	ret->m_parent = this;
	return ret;
}

Octree::Octree()
{

}

Octree::Octree(BoundingBox region)
{
	m_region = region;
}


Octree::~Octree()
{
	for (int i = 0; i < 8; ++i) {
		if (m_childNodes[i] != nullptr)
			delete m_childNodes[i];
	}
	delete[] m_childNodes;
}

void Octree::CheckCollisions(std::vector<uint> parentObjs)
{
	MyEntityManager* manager = MyEntityManager::GetInstance();

	// Check all parent parent objects against all objects in the local node. Currently unused unless code below is uncommented
	for (uint i = 0; i < parentObjs.size(); ++i)
	{
		MyEntity* parentObj = manager->GetEntity(parentObjs[i]);
		for (uint j = 0; j < m_entities.size(); ++j)
		{
			MyEntity* mEntity = manager->GetEntity(m_entities[j]);
			if (mEntity->IsColliding(parentObj)) {
				mEntity->ResolveCollision(parentObj);
				parentObj->ResolveCollision(mEntity);
			}
		}
	}


	// Check local objects against all other local objects
	if (m_entities.size() > 1)
	{
		for (int i = 0; i < m_entities.size() - 1; ++i)
		{
			MyEntity* objA = manager->GetEntity(m_entities[i]);
			for (int j = i + 1; j < m_entities.size(); ++j)
			{
				MyEntity* objB = manager->GetEntity(m_entities[j]);
				if (objA->IsColliding(objB)) {
					objA->ResolveCollision(objB);
					objB->ResolveCollision(objA);
				}
			}
		}
	}

	// Uncomment this to detect all collisions. This causes a major performance hit
	
	for (uint i = 0; i < m_entities.size(); ++i)
	{
		parentObjs.push_back(m_entities[i]);
	}
	

	//each child node will give us a list of intersection records, which we then merge with our own intersection records.
	for (int flags = m_activeNodes, index = 0; flags > 0; flags >>= 1, index++)
	{
		if ((flags & 1) == 1)
		{
			if (m_childNodes[index] != nullptr)
			{
				m_childNodes[index]->CheckCollisions(parentObjs);
			}
		}
	}
}