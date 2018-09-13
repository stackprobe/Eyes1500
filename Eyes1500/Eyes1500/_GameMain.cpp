#include "all.h"

static void DrawWall(void)
{
	DrawRect(P_CG_STAGE, 0, 0, SCREEN_W, SCREEN_H);
}
void GameMain(void)
{
	SetCurtain();
	FreezeInput();

	MusicPlay(MUS_BATTLE_1);

	for(; ; )
	{
		if(GetPound(INP_PAUSE))
		{
			break;
		}

		if(ProcFrame % 10 == 0)
			AddCommonEffect(Gnd.EL, 0, P_DUMMY, 400.0, 300.0, 0.0, 0.5, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, cos(ProcFrame / 100.0) * 0.1, sin(ProcFrame / 100.0) * 0.1);

		DrawWall();
		EachFrame();
	}
	FreezeInput();
	MusicFade();

	forscene(40)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	FreezeInput();
}
