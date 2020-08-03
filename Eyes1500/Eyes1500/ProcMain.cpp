#include "all.h"

void ProcMain(void)
{
#if !LOG_ENABLED
	TitleMenu();
#elif 0 // test
	GameInit();
	GameMain();
	GameFnlz();
#elif 1 // test
	TitleMenu();
#elif 0 // test
	error(); // HACK
#else
	error(); // HACK
#endif
}
