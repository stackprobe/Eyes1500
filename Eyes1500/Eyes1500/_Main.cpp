#include "all.h"

void ProcMain(void)
{
#if !LOG_ENABLED
	E15TitleMenu(); // test
	//error(); // TODO
#elif 0 // test
	GameInit();
	GameMain();
	GameFnlz();
#elif 1 // test
	E15TitleMenu();
#elif 0 // test
	error(); // todo
#else
	error(); // todo
#endif
}
