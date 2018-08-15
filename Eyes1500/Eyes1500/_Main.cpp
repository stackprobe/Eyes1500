#include "all.h"

void ProcMain(void)
{
#if !LOG_ENABLED
TitleMenu(); // test
	//error(); // TODO
#elif 0 // test
	GameInit();
	GameMain();
	GameFnlz();
#elif 1 // test
	TitleMenu();
#elif 0 // test
	error(); // todo
#else
	error(); // todo
#endif
}
