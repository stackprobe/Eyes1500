#include "all.h"

int SimpleMenu_Color = -1;
int SimpleMenu_BorderColor = -1;
int SimpleMenu_WallColor = -1;
int SimpleMenu_WallPicId = -1;
double SimpleMenu_WallCurtain = 0.0;
int SimpleMenu_X = 16;
int SimpleMenu_Y = 16;
int SimpleMenu_YStep = 32;

int SimpleMenu(char *menuTitle, char **menuItems, int selectMax, int selectIndex)
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

		if(SimpleMenu_WallColor != -1)
			DrawBox(0, 0, SCREEN_W, SCREEN_H, SimpleMenu_WallColor, 1);

		if(SimpleMenu_WallPicId != -1)
		{
			DrawRect(SimpleMenu_WallPicId, 0, 0, SCREEN_W, SCREEN_H);
//			DrawCenter(SimpleMenu_WallPicId, SCREEN_W / 2.0, SCREEN_H / 2.0); // old
			DrawCurtain(SimpleMenu_WallCurtain);
		}
		if(SimpleMenu_Color != -1)
			PE.Color = SimpleMenu_Color;

		if(SimpleMenu_BorderColor != -1)
			PE_Border(SimpleMenu_BorderColor);

		SetPrint(SimpleMenu_X, SimpleMenu_Y, SimpleMenu_YStep);
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

static void *PadBtnIdBkup;

static void RestorePadBtnId(void)
{
	memcpy(&Gnd.PadBtnId, PadBtnIdBkup, sizeof(Gnd.PadBtnId));
}

// ---- âÊñ ÉTÉCÉY ----

// ---- É{ÉäÉÖÅ[ÉÄ ----
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

	SimpleVolumeConfig("ÇaÇfÇlâπó ", Gnd.MusicVolume, 0, 100, 1, 10, XXX_BGMVolumeChanged);

	SimpleVolumeConfig("ÇrÇdâπó ", Gnd.SEVolume, 0, 100, 1, 10, XXX_SEVolumeChanged, XXX_SEVolumePulse);
*/

static double SVC_ValueToRate(double value, double minval, double valRange)
{
	return (double)(value - minval) / valRange;
}

/*
	(ret, rate): 0.0 - 1.0
	pulse: NULL == ñ≥å¯
*/
