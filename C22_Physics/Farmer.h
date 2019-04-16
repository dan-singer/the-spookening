#ifndef _FARMER_H
#define _FARMER_H

#include "Definitions.h"
#include "MyEntity.h"

namespace Simplex
{
	class Farmer : public MyEntity
	{
	private:
		float m_fCooldownTimer = 0.0f;
		float m_fStartingTimer = 1.0f;
	public:
		Farmer(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime);
		virtual ~Farmer();
		// void ResolveCollision();
	};
}


#endif // !_FARMER_H


