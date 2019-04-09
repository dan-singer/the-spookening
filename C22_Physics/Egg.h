#ifndef _EGG_H
#define _EGG_H

#include "Definitions.h"
#include "MyEntity.h"

namespace Simplex
{
	class Egg : public MyEntity
	{
	private:
		float m_speed = 10.0f;
	public:
		Egg(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime) override;
		~Egg();
	};
}

#endif // !_EGG_H

