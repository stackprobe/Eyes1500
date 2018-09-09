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
static void ControllerMenu(void)
{
	const int FRAME_XS[] =
	{
		16,
		208,
		336,
	};
	const int FRAME_YS[] =
	{
		144,
		176,
		208,
		240,
		272,
		304,
		336,
		368,
		400,
		432,
		464,
		496,
	};

	double a = 0.0;

	int *varTable[2][11] = // [KEY, PAD][]
	{
		{
			&Gnd.KbdKeyId.Dir_2,
			&Gnd.KbdKeyId.Dir_4,
			&Gnd.KbdKeyId.Dir_6,
			&Gnd.KbdKeyId.Dir_8,
			&Gnd.KbdKeyId.A,
			&Gnd.KbdKeyId.B,
			&Gnd.KbdKeyId.C,
			&Gnd.KbdKeyId.D,
			&Gnd.KbdKeyId.E,
			&Gnd.KbdKeyId.F,
			&Gnd.KbdKeyId.Pause,
		},
		{
			&Gnd.PadBtnId.Dir_2,
			&Gnd.PadBtnId.Dir_4,
			&Gnd.PadBtnId.Dir_6,
			&Gnd.PadBtnId.Dir_8,
			&Gnd.PadBtnId.A,
			&Gnd.PadBtnId.B,
			&Gnd.PadBtnId.C,
			&Gnd.PadBtnId.D,
			&Gnd.PadBtnId.E,
			&Gnd.PadBtnId.F,
			&Gnd.PadBtnId.Pause,
		},
	};

	FreezeInput();

	StartZ = 0.9;

	const int SELECT_MAX = 12;
	int selectIndex = 0;

	for(; ; )
	{
		if(!FreezeInputFrame)
		{
			if(GetPound(INP_A))
			{
				/*
					0	UP
					1	DOWN
					2	RIGHT
					3	LEFT
					4	HIGH SPEED
					5	SHOT
					6	LASER BEAM
					7	BLIND LASER LIGHT
					8	GUIDED MISSILE
					9	SUICIDE
					10	DECISION PAUSE
				*/
				if(m_isRange(selectIndex, 0, 10))
				{
					// TODO
				}
				else if(selectIndex == 11)
				{
					goto endLoop;
				}
				else
				{
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

		// ここから描画

		DrawWall();

		DrawBegin(P_CG_CONTROLLER, SCREEN_W / 2, SCREEN_H / 2);
		DrawRotate(StartR);
		DrawZoom(StartZ);
		DrawEnd();

		int kbCodeIro = d2i(a * 255.0);
		double va = 1.0 - a;
		int kbCodeFar = d2i(va * va * 20.0);

		for(int x = 0; x < 2; x++)
		for(int y = 0; y < 11; y++)
		{
			char *str = xcout("%03d", *varTable[x][y]);

			DrawStringByFont(
				FRAME_XS[x + 1] + 47 + kbCodeFar, FRAME_YS[y] + 7 + kbCodeFar,
				str,
				GetFontHandle(APP_COMMON_FONT, 18, 6),
				0,
				GetColor(kbCodeIro, kbCodeIro, kbCodeIro)
				);

			memFree(str);
		}

		if(!FreezeInputFrame)
		{
			DrawSimple(P_CG_FRAME, FRAME_XS[0], FRAME_YS[selectIndex]);
		}

		// EachFrame

		EachFrame();

		m_approach(a, 1.0, 0.9);
	}
endLoop:
	FreezeInput();
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
				FreezeInput(20); // スクリーンサイズを連続して変更出来ないように、少し待つ。
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

		// ここから描画

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
						MusicFade();

						forscene(40)
						{
							m_approach(WallZ, 1.0, 0.85);

							DrawWall();
							EachFrame();
						}
						sceneLeave();

						// TODO ゲームスタート

						SetCurtain();
						FreezeInput();
						MusicPlay(MUS_MAIN);
#if 0
						StartZ = 2.0;
						StartR = 10.0;
#else
						StartZ = 0.9;
#endif
					}
					break;

				case 1:
					{
						ControllerMenu();
						StartZ = 0.9;
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

		// ここから描画

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
