// memory leak detection stuff
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// Include standard headers
#include "Main.h"


void wrapperFunction() {
	using namespace Simplex;
	Application* pApp = new Application();
	pApp->Init("", RES_C_1280x720_16x9_HD, false, false);
	pApp->Run();
	SafeDelete(pApp);
}

int main(void)
{
	// wrapper function that removes false positives
	wrapperFunction();

	// memory leak dump call
	_CrtDumpMemoryLeaks();
	return 0;
	
}

