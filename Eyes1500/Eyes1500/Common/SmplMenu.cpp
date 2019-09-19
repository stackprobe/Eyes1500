#include "all.h"

int SmplMenu_Color = -1;
int SmplMenu_BorderColor = -1;
int SmplMenu_WallColor = -1;
int SmplMenu_WallPicId = -1;
double SmplMenu_WallCurtain = 0.0;
int SmplMenu_X = 16;
int SmplMenu_Y = 16;
int SmplMenu_YStep = 32;

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
			Print_x(xcout("[%c]�@%s\n", selectIndex == c ? '>' : ' ', menuItems[c]));
			PrintRet();
		}
		PE_Reset();

		EachFrame();
	}
	FreezeInput();

	return selectIndex;
}

// ---- �{�^���ݒ� ----

static void *PadBtnIdBkup;

static void RestorePadBtnId(void)
{
	memcpy(&Gnd.PadBtnId, PadBtnIdBkup, sizeof(Gnd.PadBtnId));
}

// ---- ��ʃT�C�Y ----

// ---- �{�����[�� ----
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

	SmplVolumeConfig("�a�f�l����", Gnd.MusicVolume, 0, 100, 1, 10, XXX_BGMVolumeChanged);

	SmplVolumeConfig("�r�d����", Gnd.SEVolume, 0, 100, 1, 10, XXX_SEVolumeChanged, XXX_SEVolumePulse);
*/

static double SVC_ValueToRate(double value, double minval, double valRange)
{
	return (double)(value - minval) / valRange;
}

/*
	(ret, rate): 0.0 - 1.0
	pulse: NULL == ����
*/
