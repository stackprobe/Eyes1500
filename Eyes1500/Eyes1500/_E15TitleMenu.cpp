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
static void CommonApproach(void)
{
	m_approach(WallZ, 1.0, 0.999);
	m_approach(StartZ, 1.0, 0.86);
	m_approach(StartR, 0.0, 0.7);
}
static void ResolutionMenu(void)
{
	int monitor_w = GetSystemMetrics(SM_CXSCREEN);
	int monitor_h = GetSystemMetrics(SM_CYSCREEN);

	const int FRAME_X = 216;
	const int FRAME_YS[] =
	{
		208,
		272,
		304,
		336,
		400,
	};

	FreezeInput();

	StartZ = 0.9;

	const int SELECT_MAX = 5;
	int selectIndex = 0;

	for(; ; )
	{
		if(!FreezeInputFrame)
		{
			if(GetPound(INP_A))
			{
				switch(selectIndex)
				{
				case 0:
					if(Gnd.RealScreen_W == monitor_w && Gnd.RealScreen_H == monitor_h)
						SetScreenSize(480, 640);
					else
						SetScreenSize(monitor_w, monitor_h);

					break;

				case 1: SetScreenSize(480, 640); break;
				case 2: SetScreenSize(600, 800); break;
				case 3: SetScreenSize(768, 1024); break;

				case 4:
					goto endLoop;

				default:
					error(); // never
				}
				FreezeInput(20);
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

		CommonApproach();

		// ‚±‚±‚©‚ç•`‰æ

		DrawWall();

		DrawBegin(P_CG_SCREEN, SCREEN_W / 2, SCREEN_H / 2);
		DrawRotate(StartR);
		DrawZoom(StartZ);
		DrawEnd();

		if(!FreezeInputFrame)
		{
			DrawSimple(P_CG_FRAME, FRAME_X, FRAME_YS[selectIndex]);
		}

		// EachFrame

		EachFrame();
	}
endLoop:
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
	FreezeInput(25);

	MusicPlay(MUS_MAIN);

	WallZ = 1.2;
	StartZ = 2.0;
	StartR = 10.0;

	const int SELECT_MAX = 3;
	int selectIndex = 0;

	int frameCnt = 0;
//	const int SELECTABLE_FRAME = 25;

	for(; ; )
	{
		if(!FreezeInputFrame)
		{
			if(GetPound(INP_A))
			{
				switch(selectIndex)
				{
				case 0:
					{
						// TODO
					}
					break;

				case 1:
					{
						// TODO
					}
					break;

				case 2:
					{
						ResolutionMenu();
						StartZ = 0.9;
					}
					break;

				case 3:
					goto endLoop;

				default:
					error(); // never
				}
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

		CommonApproach();

		// ‚±‚±‚©‚ç•`‰æ

		DrawWall();

		DrawBegin(P_CG_START, SCREEN_W / 2, SCREEN_H / 2);
		DrawRotate(StartR);
		DrawZoom(StartZ);
		DrawEnd();

		if(!FreezeInputFrame)
		{
			DrawSimple(P_CG_FRAME, FRAME_X, FRAME_YS[selectIndex]);
		}

		// EachFrame

		EachFrame();

		frameCnt++;
	}
endLoop:
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
