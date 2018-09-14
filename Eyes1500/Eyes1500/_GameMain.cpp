#include "all.h"

static void DrawWall(void)
{
	DrawRect(P_CG_STAGE, 0, 0, SCREEN_W, SCREEN_H);
}
void GameMain(void)
{
	SetCurtain();
	FreezeInput();

	for(; ; )
	{
		if(GetInput(INP_A) | GetInput(INP_PAUSE))
			break;

		DrawWall();
		DrawCenter(D_CG_MESSAGE_00 | DTP, SCREEN_W / 2, SCREEN_H / 2);
		EachFrame();
	}

	MusicPlay(MUS_BATTLE_1);

	for(; ; )
	{
		if(GetPound(INP_PAUSE))
		{
			break;
		}

		// TODO

		DrawWall();
		EachFrame();
	}
	FreezeInput();
//	MusicFade(); // “¯‚¶‹È‚È‚Ì‚Å

	forscene(20)
//	forscene(40)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	FreezeInput();
}
