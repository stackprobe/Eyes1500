#include "all.h"

static double WallZ;
static double StartZ;
static double StartR;

static void DrawWall(void)
{
//	DrawCurtain();

	DrawBegin(P_CG_STAGE, SCREEN_W / 2, SCREEN_H / 2);
	DrawZoom(WallZ);
	DrawEnd();
}
static void XXXSubMain(void)
{
	FreezeInput();

	for(; ; )
	{
		// 1. 入力受付・処理 -- ループを抜ける場合はここから

		if(GetPound(INP_PAUSE))
		{
			break;
		}

		// 2. 描画

		DrawWall();

		// 3. EachFrame

		EachFrame();
	}
	FreezeInput();
}
void E15TitleMenu(void)
{
	const int FRAME_X = 144;
	const int FRAME_YS[] =
	{
		376,
		408,
		440,
	};

	SetCurtain();
	FreezeInput();

	MusicPlay(MUS_MAIN);

	WallZ = 1.2;
	StartZ = 2.0;
	StartR = 10.0;

	const int SELECT_MAX = 3;
	int selectIndex = 0;

	int frameCnt = 0;
	const int SELECTABLE_FRAME = 25;

	for(; ; )
	{
		if(SELECTABLE_FRAME <= frameCnt)
		{
			if(GetPound(INP_A))
			{
				XXXSubMain(); // ？？？
			}
			if(GetPound(INP_DIR_8))
			{
				selectIndex--;
			}
			if(GetPound(INP_DIR_2))
			{
				selectIndex++;
			}
		}

		m_range(selectIndex, 0, SELECT_MAX - 1);

		m_approach(WallZ, 1.0, 0.999);
		m_approach(StartZ, 1.0, 0.86);
		m_approach(StartR, 0.0, 0.7);

		// ここから描画

		DrawWall();

		DrawBegin(P_CG_START, SCREEN_W / 2, SCREEN_H / 2);
		DrawRotate(StartR);
		DrawZoom(StartZ);
		DrawEnd();

		if(SELECTABLE_FRAME <= frameCnt)
		{
			DrawSimple(P_CG_FRAME, FRAME_X, FRAME_YS[selectIndex]);
		}

		// EachFrame

		EachFrame();

		frameCnt++;
	}
	FreezeInput();
	MusicFade();
	SetCurtain(30, -1.0);

	forscene(40)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();
}
