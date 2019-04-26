#ifndef _MY_ENTITY_H
#define _MY_ENTITY_H

#include "Definitions.h"
#include "MyEntity.h"

namespace Simplex {

	class StaticEntity : public MyEntity
	{
	public:
		StaticEntity(String a_sFileName, string type, String a_sUniqueID = "NA");

		virtual void Update(float deltaTime) override;

		virtual void ResolveCollision(MyEntity* other) override;

		~StaticEntity();
	};
}
#endif
