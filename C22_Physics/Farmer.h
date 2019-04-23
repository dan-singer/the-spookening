#ifndef _FARMER_H
#define _FARMER_H

#include "Definitions.h"
#include "MyEntity.h"

namespace Simplex
{
	class Farmer : public MyEntity
	{
	private:
		float m_fStartingTimer = 60.0f;
		float MapSize = 200;
	public:
		Farmer(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime);
		virtual ~Farmer();
		void ResolveCollision(MyEntity* a_pOther);
	};
}


#endif // !_FARMER_H



