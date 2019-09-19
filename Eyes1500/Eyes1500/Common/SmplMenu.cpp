/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_Color = -1;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_BorderColor = -1;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_WallColor = -1;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_WallPicId = -1;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double SmplMenu_WallCurtain = 0.0;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_X = 16;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_Y = 16;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu_YStep = 32;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int SmplMenu(char *menuTitle, char **menuItems, int selectMax, int selectIndex)
{
	SetCurtain();
	FreezeInput();

	for(; ; )
	{
		if(GetPound(INP_A))
		{
			break;
		}
		if(GetPound(INP_B))
		{
			if(selectIndex == selectMax - 1)
				break;

			selectIndex = selectMax - 1;
		}
		if(GetPound(INP_DIR_8))
		{
			selectIndex--;
		}
		if(GetPound(INP_DIR_2))
		{
			selectIndex++;
		}

		selectIndex += selectMax;
		selectIndex %= selectMax;

		DrawCurtain();

		if(SmplMenu_WallColor != -1)
			DrawBox(0, 0, SCREEN_W, SCREEN_H, SmplMenu_WallColor, 1);

		if(SmplMenu_WallPicId != -1)
		{
			DrawRect(SmplMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
//			DrawCenter(SmplMenu_WallPicId, SCREEN_W / 2.0, SCREEN_H / 2.0); // old
			DrawCurtain(SmplMenu_WallCurtain);
		}
		if(SmplMenu_Color != -1)
			PE.Color = SmplMenu_Color;

		if(SmplMenu_BorderColor != -1)
			PE_Border(SmplMenu_BorderColor);

		SetPrint(SmplMenu_X, SmplMenu_Y, SmplMenu_YStep);
//		SetPrint(16, 16, 32); // old
		Print(menuTitle);
		PrintRet();

		for(int c = 0; c < selectMax; c++)
		{
			Print_x(xcout("[%c]　%s\n", selectIndex == c ? '>' : ' ', menuItems[c]));
			PrintRet();
		}
		PE_Reset();

		EachFrame();
	}
	FreezeInput();

	return selectIndex;
}

// ---- ボタン設定 ----

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void *PadBtnIdBkup;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void RestorePadBtnId(void)
{
	memcpy(&Gnd.PadBtnId, PadBtnIdBkup, sizeof(Gnd.PadBtnId));
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000136 $$$$ //	void SmplPadConfig(void)
// #### DELETED ==== 0000136 $$$$ //	{
// #### DELETED ==== 0000136 $$$$ //		int *BtnPList[INP_MAX] =
// #### DELETED ==== 0000136 $$$$ //		{
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.Dir_2,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.Dir_4,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.Dir_6,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.Dir_8,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.A,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.B,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.C,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.D,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.E,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.F,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.L,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.R,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.Pause,
// #### DELETED ==== 0000136 $$$$ //			&Gnd.PadBtnId.Start,
// #### DELETED ==== 0000136 $$$$ //		};
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		/*
// #### DELETED ==== 0000136 $$$$ //			NULL == 使用していない。
// #### DELETED ==== 0000136 $$$$ //		＊/
// #### DELETED ==== 0000136 $$$$ //		char *BTN_LIST[INP_MAX] =
// #### DELETED ==== 0000136 $$$$ //		{
// #### DELETED ==== 0000136 $$$$ //			// app > @ BTN_LIST
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			"下", // INP_DIR_2
// #### DELETED ==== 0000136 $$$$ //			"左", // INP_DIR_4
// #### DELETED ==== 0000136 $$$$ //			"右", // INP_DIR_6
// #### DELETED ==== 0000136 $$$$ //			"上", // INP_DIR_8
// #### DELETED ==== 0000136 $$$$ //			"ショットボタン", // INP_A
// #### DELETED ==== 0000136 $$$$ //			"低速ボタン", // INP_B
// #### DELETED ==== 0000136 $$$$ //			"ボムボタン", // INP_C
// #### DELETED ==== 0000136 $$$$ //			NULL, // INP_D
// #### DELETED ==== 0000136 $$$$ //			NULL, // INP_E
// #### DELETED ==== 0000136 $$$$ //			NULL, // INP_F
// #### DELETED ==== 0000136 $$$$ //			NULL, // INP_L
// #### DELETED ==== 0000136 $$$$ //			NULL, // INP_R
// #### DELETED ==== 0000136 $$$$ //			"ポーズボタン", // INP_PAUSE
// #### DELETED ==== 0000136 $$$$ //			NULL, // INP_START
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			// < app
// #### DELETED ==== 0000136 $$$$ //		};
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		PadBtnIdBkup = memClone(&Gnd.PadBtnId, sizeof(Gnd.PadBtnId));
// #### DELETED ==== 0000136 $$$$ //		GetEndProcFinalizers()->AddFunc(RestorePadBtnId);
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		for(int c = 0; c < INP_MAX; c++)
// #### DELETED ==== 0000136 $$$$ //			*BtnPList[c] = -1;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		SetCurtain();
// #### DELETED ==== 0000136 $$$$ //		FreezeInput();
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		int currBtnIndex = 0;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		while(currBtnIndex < INP_MAX)
// #### DELETED ==== 0000136 $$$$ //		{
// #### DELETED ==== 0000136 $$$$ //			if(!BTN_LIST[currBtnIndex])
// #### DELETED ==== 0000136 $$$$ //			{
// #### DELETED ==== 0000136 $$$$ //				currBtnIndex++;
// #### DELETED ==== 0000136 $$$$ //				continue;
// #### DELETED ==== 0000136 $$$$ //			}
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			if(GetKeyInput(KEY_INPUT_SPACE) == 1)
// #### DELETED ==== 0000136 $$$$ //			{
// #### DELETED ==== 0000136 $$$$ //				RestorePadBtnId();
// #### DELETED ==== 0000136 $$$$ //				break;
// #### DELETED ==== 0000136 $$$$ //			}
// #### DELETED ==== 0000136 $$$$ //			if(GetKeyInput(KEY_INPUT_Z) == 1)
// #### DELETED ==== 0000136 $$$$ //			{
// #### DELETED ==== 0000136 $$$$ //				currBtnIndex++;
// #### DELETED ==== 0000136 $$$$ //				goto endInput;
// #### DELETED ==== 0000136 $$$$ //			}
// #### DELETED ==== 0000136 $$$$ //			int pressBtnId = -1;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			for(int padId = 0; padId < GetPadCount(); padId++)
// #### DELETED ==== 0000136 $$$$ //			for(int btnId = 0; btnId < PAD_BUTTON_MAX; btnId++)
// #### DELETED ==== 0000136 $$$$ //				if(GetPadInput(padId, btnId) == 1)
// #### DELETED ==== 0000136 $$$$ //					pressBtnId = btnId;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			for(int c = 0; c < currBtnIndex; c++)
// #### DELETED ==== 0000136 $$$$ //				if(*BtnPList[c] == pressBtnId)
// #### DELETED ==== 0000136 $$$$ //					pressBtnId = -1;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			if(pressBtnId != -1)
// #### DELETED ==== 0000136 $$$$ //			{
// #### DELETED ==== 0000136 $$$$ //				*BtnPList[currBtnIndex] = pressBtnId;
// #### DELETED ==== 0000136 $$$$ //				currBtnIndex++;
// #### DELETED ==== 0000136 $$$$ //			}
// #### DELETED ==== 0000136 $$$$ //	endInput:
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			DrawCurtain();
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			if(SmplMenu_WallPicId != -1)
// #### DELETED ==== 0000136 $$$$ //			{
// #### DELETED ==== 0000136 $$$$ //				DrawRect(SmplMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
// #### DELETED ==== 0000136 $$$$ //	//			DrawCenter(SmplMenu_WallPicId, SCREEN_W / 2.0, SCREEN_H / 2.0); // old
// #### DELETED ==== 0000136 $$$$ //				DrawCurtain(SmplMenu_WallCurtain);
// #### DELETED ==== 0000136 $$$$ //			}
// #### DELETED ==== 0000136 $$$$ //			if(SmplMenu_Color != -1)
// #### DELETED ==== 0000136 $$$$ //				PE.Color = SmplMenu_Color;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			if(SmplMenu_BorderColor != -1)
// #### DELETED ==== 0000136 $$$$ //				PE_Border(SmplMenu_BorderColor);
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			SetPrint(SmplMenu_X, SmplMenu_Y, SmplMenu_YStep);
// #### DELETED ==== 0000136 $$$$ //	//		SetPrint(16, 16, 32); // old
// #### DELETED ==== 0000136 $$$$ //			Print("ゲームパッドのボタン設定");
// #### DELETED ==== 0000136 $$$$ //			PrintRet();
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			for(int c = 0; c < INP_MAX; c++)
// #### DELETED ==== 0000136 $$$$ //			{
// #### DELETED ==== 0000136 $$$$ //				if(!BTN_LIST[c])
// #### DELETED ==== 0000136 $$$$ //					continue;
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //				Print_x(xcout("[%c]　%s", currBtnIndex == c ? '>' : ' ', BTN_LIST[c]));
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //				if(c < currBtnIndex)
// #### DELETED ==== 0000136 $$$$ //				{
// #### DELETED ==== 0000136 $$$$ //					int btnId = *BtnPList[c];
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //					Print("　->　");
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //					if(btnId == -1)
// #### DELETED ==== 0000136 $$$$ //						Print("割り当てナシ");
// #### DELETED ==== 0000136 $$$$ //					else
// #### DELETED ==== 0000136 $$$$ //						Print_x(xcout("%d", btnId));
// #### DELETED ==== 0000136 $$$$ //				}
// #### DELETED ==== 0000136 $$$$ //				PrintRet();
// #### DELETED ==== 0000136 $$$$ //			}
// #### DELETED ==== 0000136 $$$$ //			Print("★　カーソルの機能に割り当てるボタンを押して下さい。");
// #### DELETED ==== 0000136 $$$$ //			PrintRet();
// #### DELETED ==== 0000136 $$$$ //			Print("★　スペースを押すとキャンセルします。");
// #### DELETED ==== 0000136 $$$$ //			PrintRet();
// #### DELETED ==== 0000136 $$$$ //			Print("★　[Z]を押すとボタンの割り当てをスキップします。");
// #### DELETED ==== 0000136 $$$$ //			PrintRet();
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //			EachFrame();
// #### DELETED ==== 0000136 $$$$ //		}
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		GetEndProcFinalizers()->RemoveFunc(RestorePadBtnId);
// #### DELETED ==== 0000136 $$$$ //		memFree(PadBtnIdBkup);
// #### DELETED ==== 0000136 $$$$ //	
// #### DELETED ==== 0000136 $$$$ //		FreezeInput();
// #### DELETED ==== 0000136 $$$$ //	}

// ---- 画面サイズ ----

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000137 $$$$ //	void SmplWindowSizeConfig(void)
// #### DELETED ==== 0000137 $$$$ //	{
// #### DELETED ==== 0000137 $$$$ //		char *MENU_ITEMS[] =
// #### DELETED ==== 0000137 $$$$ //		{
// #### DELETED ==== 0000137 $$$$ //			"800 x 600 (デフォルト)",
// #### DELETED ==== 0000137 $$$$ //			"900 x 675",
// #### DELETED ==== 0000137 $$$$ //			"1000 x 750",
// #### DELETED ==== 0000137 $$$$ //			"1100 x 825",
// #### DELETED ==== 0000137 $$$$ //			"1200 x 900",
// #### DELETED ==== 0000137 $$$$ //			"1300 x 975",
// #### DELETED ==== 0000137 $$$$ //			"1400 x 1050",
// #### DELETED ==== 0000137 $$$$ //			"1500 x 1125",
// #### DELETED ==== 0000137 $$$$ //			"1600 x 1200",
// #### DELETED ==== 0000137 $$$$ //			"1700 x 1275",
// #### DELETED ==== 0000137 $$$$ //			"1800 x 1350",
// #### DELETED ==== 0000137 $$$$ //			"フルスクリーン",
// #### DELETED ==== 0000137 $$$$ //			"フルスクリーン (縦横比維持)",
// #### DELETED ==== 0000137 $$$$ //			"フルスクリーン (黒背景)",
// #### DELETED ==== 0000137 $$$$ //			"戻る",
// #### DELETED ==== 0000137 $$$$ //		};
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //		int selectIndex = 0;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //		for(; ; )
// #### DELETED ==== 0000137 $$$$ //		{
// #### DELETED ==== 0000137 $$$$ //			selectIndex = SmplMenu("ウィンドウサイズ設定", MENU_ITEMS, lengthof(MENU_ITEMS), selectIndex);
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //			switch(selectIndex)
// #### DELETED ==== 0000137 $$$$ //			{
// #### DELETED ==== 0000137 $$$$ //			case 0: SetScreenSize(800, 600); break;
// #### DELETED ==== 0000137 $$$$ //			case 1: SetScreenSize(900, 675); break;
// #### DELETED ==== 0000137 $$$$ //			case 2: SetScreenSize(1000, 750); break;
// #### DELETED ==== 0000137 $$$$ //			case 3: SetScreenSize(1100, 825); break;
// #### DELETED ==== 0000137 $$$$ //			case 4: SetScreenSize(1200, 900); break;
// #### DELETED ==== 0000137 $$$$ //			case 5: SetScreenSize(1300, 975); break;
// #### DELETED ==== 0000137 $$$$ //			case 6: SetScreenSize(1400, 1050); break;
// #### DELETED ==== 0000137 $$$$ //			case 7: SetScreenSize(1500, 1125); break;
// #### DELETED ==== 0000137 $$$$ //			case 8: SetScreenSize(1600, 1200); break;
// #### DELETED ==== 0000137 $$$$ //			case 9: SetScreenSize(1700, 1275); break;
// #### DELETED ==== 0000137 $$$$ //			case 10: SetScreenSize(1800, 1350); break;
// #### DELETED ==== 0000137 $$$$ //			case 11: SetScreenSize(Gnd.MonitorRect.W, Gnd.MonitorRect.H); break;
// #### DELETED ==== 0000137 $$$$ //			case 12:
// #### DELETED ==== 0000137 $$$$ //				{
// #### DELETED ==== 0000137 $$$$ //					int w = Gnd.MonitorRect.W;
// #### DELETED ==== 0000137 $$$$ //					int h = (SCREEN_H * Gnd.MonitorRect.W) / SCREEN_W;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //					if(Gnd.MonitorRect.H < h)
// #### DELETED ==== 0000137 $$$$ //					{
// #### DELETED ==== 0000137 $$$$ //						h = Gnd.MonitorRect.H;
// #### DELETED ==== 0000137 $$$$ //						w = (SCREEN_W * Gnd.MonitorRect.H) / SCREEN_H;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //						errorCase(Gnd.MonitorRect.W < w);
// #### DELETED ==== 0000137 $$$$ //					}
// #### DELETED ==== 0000137 $$$$ //					SetScreenSize(w, h);
// #### DELETED ==== 0000137 $$$$ //				}
// #### DELETED ==== 0000137 $$$$ //				break;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //			case 13:
// #### DELETED ==== 0000137 $$$$ //				{
// #### DELETED ==== 0000137 $$$$ //					int w = Gnd.MonitorRect.W;
// #### DELETED ==== 0000137 $$$$ //					int h = (SCREEN_H * Gnd.MonitorRect.W) / SCREEN_W;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //					if(Gnd.MonitorRect.H < h)
// #### DELETED ==== 0000137 $$$$ //					{
// #### DELETED ==== 0000137 $$$$ //						h = Gnd.MonitorRect.H;
// #### DELETED ==== 0000137 $$$$ //						w = (SCREEN_W * Gnd.MonitorRect.H) / SCREEN_H;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //						errorCase(Gnd.MonitorRect.W < w);
// #### DELETED ==== 0000137 $$$$ //					}
// #### DELETED ==== 0000137 $$$$ //					SetScreenSize(Gnd.MonitorRect.W, Gnd.MonitorRect.H);
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //					Gnd.RealScreenDraw_L = (Gnd.MonitorRect.W - w) / 2;
// #### DELETED ==== 0000137 $$$$ //					Gnd.RealScreenDraw_T = (Gnd.MonitorRect.H - h) / 2;
// #### DELETED ==== 0000137 $$$$ //					Gnd.RealScreenDraw_W = w;
// #### DELETED ==== 0000137 $$$$ //					Gnd.RealScreenDraw_H = h;
// #### DELETED ==== 0000137 $$$$ //				}
// #### DELETED ==== 0000137 $$$$ //				break;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //			case 14:
// #### DELETED ==== 0000137 $$$$ //				goto endLoop;
// #### DELETED ==== 0000137 $$$$ //	
// #### DELETED ==== 0000137 $$$$ //			default:
// #### DELETED ==== 0000137 $$$$ //				error();
// #### DELETED ==== 0000137 $$$$ //			}
// #### DELETED ==== 0000137 $$$$ //		}
// #### DELETED ==== 0000137 $$$$ //	/*
// #### DELETED ==== 0000137 $$$$ //		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
// #### DELETED ==== 0000137 $$$$ //	＊/
// #### DELETED ==== 0000137 $$$$ //	endLoop:;
// #### DELETED ==== 0000137 $$$$ //	}

// ---- ボリューム ----
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	-- e.g.

	static void XXX_BGMVolumeChanged(double volume)
	{
		Gnd.MusicVolume = volume;
		UpdateMusicVolume();
	}
	static void XXX_SEVolumeChanged(double volume)
	{
		Gnd.SEVolume = volume;
		UpdateSEVolume();
	}
	static void XXX_SEVolumePulse(void)
	{
		SEPlay(rndPct(50) ? SE_PAUSE_IN : SE_PAUSE_OUT);
	}

	SmplVolumeConfig("ＢＧＭ音量", Gnd.MusicVolume, 0, 100, 1, 10, XXX_BGMVolumeChanged);

	SmplVolumeConfig("ＳＥ音量", Gnd.SEVolume, 0, 100, 1, 10, XXX_SEVolumeChanged, XXX_SEVolumePulse);
*/

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static double SVC_ValueToRate(double value, double minval, double valRange)
{
	return (double)(value - minval) / valRange;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	(ret, rate): 0.0 - 1.0
	pulse: NULL == 無効
*/
// #### DELETED ==== 0000138 $$$$ //	double SmplVolumeConfig(char *menuTitle, double rate, int minval, int maxval, int valStep, int valFastStep, void (*valChanged)(double), void (*pulse)(void))
// #### DELETED ==== 0000138 $$$$ //	{
// #### DELETED ==== 0000138 $$$$ //		const int PULSE_FRM = 60;
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //		int valRange = maxval - minval;
// #### DELETED ==== 0000138 $$$$ //		int value = minval + d2i(rate * valRange);
// #### DELETED ==== 0000138 $$$$ //		int origval = value;
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //		SetCurtain();
// #### DELETED ==== 0000138 $$$$ //		FreezeInput();
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //		for(; ; )
// #### DELETED ==== 0000138 $$$$ //		{
// #### DELETED ==== 0000138 $$$$ //			int chgval = 0;
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			if(GetPound(INP_A))
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				break;
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(GetPound(INP_B))
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				if(value == origval)
// #### DELETED ==== 0000138 $$$$ //					break;
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //				value = origval;
// #### DELETED ==== 0000138 $$$$ //				chgval = 1;
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(GetPound(INP_DIR_8))
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				value += valFastStep;
// #### DELETED ==== 0000138 $$$$ //				chgval = 1;
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(GetPound(INP_DIR_6))
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				value += valStep;
// #### DELETED ==== 0000138 $$$$ //				chgval = 1;
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(GetPound(INP_DIR_4))
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				value -= valStep;
// #### DELETED ==== 0000138 $$$$ //				chgval = 1;
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(GetPound(INP_DIR_2))
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				value -= valFastStep;
// #### DELETED ==== 0000138 $$$$ //				chgval = 1;
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(chgval)
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				m_range(value, minval, maxval);
// #### DELETED ==== 0000138 $$$$ //				valChanged(SVC_ValueToRate(value, minval, valRange));
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(pulse && ProcFrame % PULSE_FRM == 0)
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				pulse();
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			DrawCurtain();
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			if(SmplMenu_WallPicId != -1)
// #### DELETED ==== 0000138 $$$$ //			{
// #### DELETED ==== 0000138 $$$$ //				DrawRect(SmplMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
// #### DELETED ==== 0000138 $$$$ //				DrawCurtain(SmplMenu_WallCurtain);
// #### DELETED ==== 0000138 $$$$ //			}
// #### DELETED ==== 0000138 $$$$ //			if(SmplMenu_Color != -1)
// #### DELETED ==== 0000138 $$$$ //				PE.Color = SmplMenu_Color;
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			if(SmplMenu_BorderColor != -1)
// #### DELETED ==== 0000138 $$$$ //				PE_Border(SmplMenu_BorderColor);
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			SetPrint(SmplMenu_X, SmplMenu_Y, SmplMenu_YStep);
// #### DELETED ==== 0000138 $$$$ //			Print(menuTitle);
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			Print_x(xcout("[ %d ]　最小=%d　最大=%d", value, minval, maxval));
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			Print("★　左＝下げる");
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //			Print("★　右＝上げる");
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //			Print("★　下＝速く下げる");
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //			Print("★　上＝速く上げる");
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //			Print("★　調整が終わったら決定ボタンを押して下さい。");
// #### DELETED ==== 0000138 $$$$ //			PrintRet();
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //			EachFrame();
// #### DELETED ==== 0000138 $$$$ //		}
// #### DELETED ==== 0000138 $$$$ //		FreezeInput();
// #### DELETED ==== 0000138 $$$$ //	
// #### DELETED ==== 0000138 $$$$ //		return SVC_ValueToRate(value, minval, valRange);
// #### DELETED ==== 0000138 $$$$ //	}
