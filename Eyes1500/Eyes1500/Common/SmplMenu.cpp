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
			Print_x(xcout("[%c]Å@%s\n", selectIndex == c ? '>' : ' ', menuItems[c]));
			PrintRet();
		}
		PE_Reset();

		EachFrame();
	}
	FreezeInput();

	return selectIndex;
}

// ---- É{É^Éìê›íË ----

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

// ---- âÊñ ÉTÉCÉY ----

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/

// ---- É{ÉäÉÖÅ[ÉÄ ----
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

	SmplVolumeConfig("ÇaÇfÇlâπó ", Gnd.MusicVolume, 0, 100, 1, 10, XXX_BGMVolumeChanged);

	SmplVolumeConfig("ÇrÇdâπó ", Gnd.SEVolume, 0, 100, 1, 10, XXX_SEVolumeChanged, XXX_SEVolumePulse);
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
	pulse: NULL == ñ≥å¯
*/
