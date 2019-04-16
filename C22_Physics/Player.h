#ifndef _PLAYER_H
#define _PLAYER_H

#include "Definitions.h"
#include "MyEntity.h"
#include "Egg.h"

namespace Simplex
{
	class Player : public MyEntity
	{
	private:
		float m_fCooldownTimer = 0.0f;
		float m_fStartingTimer = 1.0f;
		float m_fgameTimeStart = 60.0f;
		float m_fgameTimer = m_fgameTimeStart;
		int m_score = 0;
		static Player* m_instance;
	public:
		Player(String a_sFileName, string type, String a_sUniqueID = "NA");
		static Player* GetInstance();
		virtual void Update(float deltaTime) override;
		virtual void DropEgg();
		// Adds points to score based on with what it is colliding
		void AddPoints(MyEntity* other);
		int GetScore() { return m_score; }
		float GetGameTime() { return m_fgameTimer; } // game timer accessor
		float GetGameTimeStart() { return m_fgameTimeStart; }
		virtual ~Player();
	};
}


#endif // !_PLAYER_H



