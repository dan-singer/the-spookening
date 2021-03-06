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
		// timer for launching eggs
		float m_fCooldownTimer = 0.0f;
		float m_fStartingTimer = 1.0f;

		// game timer
		float m_fgameTimeStart = 60.0f; // 4:45 
		float m_fgameTimer = m_fgameTimeStart;
		int m_score = 0;
		float m_targetAngle;
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
		void SetGameTime(float time) { m_fgameTimer = time; }
		float GetGameTimeStart() { return m_fgameTimeStart; }

		float GetTargetAngle() { return m_targetAngle; }
		void SetTargetAngle(float angle) { m_targetAngle = angle; }
		virtual ~Player();
	};
}


#endif // !_PLAYER_H



