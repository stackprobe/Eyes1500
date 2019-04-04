#include "all.h"

static void DrawWall(void)
{
	DrawRect(P_CG_STAGE, 0, 0, SCREEN_W, SCREEN_H);
}
static void Ending(int endingIndex)
{
	Gnd.HiScore = m_max(Gnd.HiScore, GDcNV.Score);

	// ----

	MusicFade();

	forscene(60)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	MusicPlay(MUS_END);

	// TODO cg effect

	forscene(300)
	{
		DrawWall();
		DrawCenter(D_CG_END_00 + endingIndex | DTP, SCREEN_CENTER_X, SCREEN_CENTER_Y);
		EachFrame();
	}
	sceneLeave();

	FreezeInput(90);

	// TODO cg effect

	for(; ; )
	{
		if(
			GetInput(INP_PAUSE) == 1 ||
//			GetInput(INP_A) == 1 || // çÇë¨à⁄ìÆÇÕîΩâûÇ≥ÇπÇ»Ç¢ÅB
			GetInput(INP_B) == 1 ||
			GetInput(INP_C) == 1 ||
			GetInput(INP_D) == 1 ||
			GetInput(INP_E) == 1 ||
			GetInput(INP_F) == 1
			)
			break;

		DrawWall();
		DrawCenter(P_CG_CREDIT, SCREEN_CENTER_X, SCREEN_CENTER_Y);
		EachFrame();
	}
	MusicFade(60);

	forscene(90)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	FreezeInput();
}
void GameMgrMain(void)
{
	int stgIndex = 0;

	GameInitNonvola();

	for(stgIndex = 0; stgIndex < GetStageCount(); stgIndex++)
	{
		GameInit();
		GDc.StageIndex = stgIndex;
		GameMain();
		int wns = GDc.WillNextStage;
		GameFnlz();

		//break; // test

		if(!wns)
			return;
	}
	Ending(END_NORMAL);

	GameFnlzNonvola();
}
