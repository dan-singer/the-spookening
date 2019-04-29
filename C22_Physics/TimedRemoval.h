#ifndef __TIMEDREMOVAL_H_
#define __TIMEDREMOVAL_H_

#include "MyEntity.h"

namespace Simplex {

	class TimedRemoval: public MyEntity {

	private:
		float timer = 3.0f;
	public:
		TimedRemoval(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime);
	};

}

#endif
