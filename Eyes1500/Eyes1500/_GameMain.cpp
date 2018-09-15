#include "all.h"

static void DrawWall(void)
{
	DrawRect(P_CG_STAGE, 0, 0, SCREEN_W, SCREEN_H);
}
static void PauseMain(void)
{
	FreezeInput();

	for(; ; )
	{
		if(GetInput(INP_PAUSE) == 1)
			break;

		// ��������`��

		DrawCenter(P_CG_PAUSE, SCREEN_W / 2, SCREEN_H / 2);

		// EachFrame

		EachFrame();
	}
	FreezeInput();
}
void GameMain(void)
{
	SetCurtain();
	FreezeInput();

	for(; ; )
	{
		if(GetInput(INP_PAUSE) == 1)
			break;

		// ��������`��

		DrawWall();
		DrawCenter(D_CG_MESSAGE_00 | DTP, SCREEN_W / 2, SCREEN_H / 2);

		// EachFrame

		EachFrame();
	}

	MusicPlay(MUS_BATTLE_1);
	FreezeInput();

	for(; ; )
	{
		if(GetInput(INP_PAUSE) == 1)
		{
			PauseMain();
		}

		// TODO

		// ��������`��

		DrawWall();

		// EachFrame

		EachFrame();
	}
	FreezeInput();
//	MusicFade(); // �����ȂȂ̂�

	forscene(20)
//	forscene(40)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	FreezeInput();
}
