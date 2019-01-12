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
static void SetOrSwapKbId(int kbIdIndex, int kbIdMax, int *pKbIds[], int id_new)
{
	int id_old = *pKbIds[kbIdIndex];

	for(int index = 0; index < kbIdMax; index++)
		if(*pKbIds[index] == id_new)
			*pKbIds[index] = id_old;

	*pKbIds[kbIdIndex] = id_new;
}
static void WaitInputMain(int kbIdIndex, int kbIdMax, int *pKbdKeyIds[], int *pPadBtnIds[])
{
	FreezeInput(20);
	SetCurtain(20, -0.8);

	for(; ; )
	{
		for(int keyId = 0; keyId < KEY_MAX; keyId++)
		{
			if(GetKeyInput(keyId) == 1)
			{
				SetOrSwapKbId(kbIdIndex, kbIdMax, pKbdKeyIds, keyId);
				goto endLoop;
			}
		}
		for(int btnId = 0; btnId < PAD_BUTTON_MAX; btnId++)
		{
			if(GetPadInput(Gnd.PrimaryPadId, btnId) == 1)
			{
				SetOrSwapKbId(kbIdIndex, kbIdMax, pPadBtnIds, btnId);
				goto endLoop;
			}
		}

		CommonApproach();

		// ここから描画

		DrawWall();

		DrawBegin(P_CG_CONTROLLER, SCREEN_W / 2, SCREEN_H / 2);
		DrawRotate(StartR);
		DrawZoom(StartZ);
		DrawEnd();

		CurtainEachFrame();

		if(!FreezeInputFrame)
		{
			DrawStringByFont(
				SCREEN_W / 2 - 150, SCREEN_H / 2 - 16,
				"キーボードのキー又は\nゲームパッドのボタンを押して下さい。",
				APP_COMMON_FONT_HANDLE
				);
		}

		// EachFrame

		EachFrame();
	}
endLoop:
	FreezeInput(20);
	SetCurtain();
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
			&Gnd.KbdKeyId.Dir_8,
			&Gnd.KbdKeyId.Dir_2,
			&Gnd.KbdKeyId.Dir_6,
			&Gnd.KbdKeyId.Dir_4,
			&Gnd.KbdKeyId.A,
			&Gnd.KbdKeyId.B,
			&Gnd.KbdKeyId.C,
			&Gnd.KbdKeyId.D,
			&Gnd.KbdKeyId.E,
			&Gnd.KbdKeyId.F,
			&Gnd.KbdKeyId.Pause,
		},
		{
			&Gnd.PadBtnId.Dir_8,
			&Gnd.PadBtnId.Dir_2,
			&Gnd.PadBtnId.Dir_6,
			&Gnd.PadBtnId.Dir_4,
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
		if(GetInput(INP_A) == 1 || GetInput(INP_PAUSE) == 1) // ? 決定 <--- INP_A と INP_PAUSE
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
				WaitInputMain(selectIndex, lengthof(varTable[0]), varTable[0], varTable[1]);
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
				APP_COMMON_FONT_HANDLE,
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
#if 0 // old
	int monitor_w = GetSystemMetrics(SM_CXSCREEN);
	int monitor_h = GetSystemMetrics(SM_CYSCREEN);
#else
	int monitor_w;
	int monitor_h;
	int monitor_l;
	int monitor_t;

	{
		int dummy;

		GetDefaultState(&monitor_w, &monitor_h, &dummy, NULL, &monitor_l, &monitor_t);
	}

	LOG("monitor_wh(lt): %d, %d, (%d, %d)\n", monitor_w, monitor_h, monitor_l, monitor_t);

	errorCase(!m_isRange(monitor_w, 1, IMAX));
	errorCase(!m_isRange(monitor_h, 1, IMAX));
	errorCase(!m_isRange(monitor_l, -IMAX, IMAX));
	errorCase(!m_isRange(monitor_t, -IMAX, IMAX));
#endif

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
		if(GetInput(INP_A) == 1 || GetInput(INP_PAUSE) == 1) // ? 決定 <--- INP_A と INP_PAUSE
		{
			switch(selectIndex)
			{
			case 0:
				if(Gnd.RealScreen_W == monitor_w && Gnd.RealScreen_H == monitor_h)
				{
					SetScreenSize(480, 640);
				}
				else
				{
					SetScreenSize(monitor_w, monitor_h);
					SetScreenPosition(monitor_l, monitor_t);
				}
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
void TitleMenu(void)
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
	int hideHiScoreFrame = 40;
	double hiScoreA = 0.0;

	for(; ; )
	{
		if(GetInput(INP_A) == 1 || GetInput(INP_PAUSE) == 1) // ? 決定 <--- INP_A と INP_PAUSE
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

					// ゲームここから

					GameInit();
					GameMain();
					GameFnlz();

					// ゲームここまで

					SetCurtain();
					FreezeInput();
					MusicPlay(MUS_MAIN);
#if 0
					StartZ = 2.0;
					StartR = 10.0;
#else
					StartZ = 0.9;
#endif
					hideHiScoreFrame = 20;
					hiScoreA = 0.0;
				}
				break;

			case 1:
				{
					ControllerMenu();
					StartZ = 0.9;
					hideHiScoreFrame = 20;
					hiScoreA = 0.0;
				}
				break;

			case 2:
				{
					ResolutionMenu();
					StartZ = 0.9;
					hideHiScoreFrame = 20;
					hiScoreA = 0.0;
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

		if(!hideHiScoreFrame)
		{
			int hiScoreIro = d2i(hiScoreA * 255.0);
			char *str = xcout("%09I64d", Gnd.HiScore);

			str = thousandComma(str);
			str = insertChar(str, 0, '\\');

			DrawStringByFont_XCenter(
				SCREEN_W / 2,
				163,
				str,
				APP_COMMON_FONT_HANDLE,
				0,
				GetColor(hiScoreIro, hiScoreIro, hiScoreIro)
				);

			memFree(str);

			m_approach(hiScoreA, 1.0, 0.9);
		}

		// EachFrame

		EachFrame();

		frameCnt++;
		m_countDown(hideHiScoreFrame);
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
