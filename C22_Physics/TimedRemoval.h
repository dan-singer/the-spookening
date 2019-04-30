#ifndef __TIMEDREMOVAL_H_
#define __TIMEDREMOVAL_H_

#include "MyEntity.h"

namespace Simplex {
	// class for grave and breakfast objects that get destroyed after timer is finished
	class TimedRemoval: public MyEntity {

	private:
		float timer = 3.0f;
	public:
		TimedRemoval(String a_sFileName, string type, String a_sUniqueID = "NA");
		virtual void Update(float deltaTime);
	};

}

#endif
