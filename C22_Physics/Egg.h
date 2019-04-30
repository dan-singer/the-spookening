#ifndef _EGG_H
#define _EGG_H

#include "Definitions.h"
#include "MyEntity.h"

namespace Simplex
{
	// egg to be dropped by chicken/player
	class Egg : public MyEntity
	{
	private:
		float m_speed = 30.0f;

		// states to use in Update()
		bool m_isMoving = true;
		bool m_isBeingDestroyed = false;

		// timer to destory its self
		float m_destroyTimer = 0.75f;
		float m_destroyCounter = 0;
	public:
		Egg(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime) override;
		~Egg();
		void ResolveCollision(MyEntity* a_pOther) override;
	};
}

#endif // !_EGG_H

