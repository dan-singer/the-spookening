#ifndef _PLAYER_H
#define _PLAYER_H

#include "Definitions.h"
#include "MyEntity.h"

namespace Simplex
{
	class Player : public MyEntity
	{
	private:
		float m_fCooldownTimer = 0.0f;
		float m_fStartingTimer = 1.0f;
	public:
		Player(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime);
		virtual void DropEgg();
		virtual ~Player();
	};
}


#endif // !_PLAYER_H



