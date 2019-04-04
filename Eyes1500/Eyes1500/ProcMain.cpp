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
	error(); // todo
#else
	error(); // todo
#endif
}

/*
	デフォルトの操作

	INP_DIR_2,
	INP_DIR_4,
	INP_DIR_6,
	INP_DIR_8,
	INP_A, // HIGH SPEED (高速移動)
	INP_B, // SHOT (弾丸)
	INP_C, // LASER BEAM (レーザー光線)
	INP_D, // BLAND LASER LIGHT (目潰しレーザー)
	INP_E, // GUIDED MISSILE (誘導ミサイル)
	INP_F, // SUICIDE (自爆)
	INP_L,
	INP_R,
	INP_PAUSE, // DECISION / PAUSE (決定 / 一時停止)
	INP_START,

	INP_MAX, // num of member
*/
