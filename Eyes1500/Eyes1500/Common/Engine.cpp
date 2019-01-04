/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int IgnoreEscapeKey;

// 他のファイルからは read only {
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 FrameStartTime;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int ProcFrame;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int FreezeInputFrame;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int WindowIsActive;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int FrameRateDropCount;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int NoFrameRateDropCount;
// }

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void CheckHz(void)
{
	__int64 currTime = GetCurrTime();
	__int64 diffTime = currTime - FrameStartTime;

	if(diffTime < 15 || 18 < diffTime) // ? frame rate drop
		FrameRateDropCount++;
	else
		NoFrameRateDropCount++;

	FrameStartTime = currTime;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int InnerDrawScrHdl = -1;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void EachFrame(void)
{
	if(!SEEachFrame())
	{
		MusicEachFrame();
	}
	Gnd.EL->ExecuteAllTask();
	CurtainEachFrame();

	if(Gnd.MainScreen && CurrDrawScreenHandle == GetHandle(Gnd.MainScreen))
	{
		ChangeDrawScreen(DX_SCREEN_BACK);

		// app > @ draw screen

		SetDrawBright(0, 0, 0);
		DrawExtendGraph(0, 0, Gnd.RealScreen_W, Gnd.RealScreen_H, Pic(P_WHITEBOX), 0);
		SetDrawBright(255, 255, 255);

		int w = Gnd.RealScreen_W;
		int h = d2i(SCREEN_H * (double)w / SCREEN_W);

		if(Gnd.RealScreen_H < h)
		{
			h = Gnd.RealScreen_H;
			w = d2i(SCREEN_W * (double)h / SCREEN_H);

			errorCase(Gnd.RealScreen_W < w);
		}
		int l = (Gnd.RealScreen_W - w) / 2;
		int t = (Gnd.RealScreen_H - h) / 2;

		DrawExtendGraph(l, t, l + w, t + h, GetHandle(Gnd.MainScreen), 0);

		// < app
	}

	// app > @ post draw screen

	// zantei zantei zantei zantei zantei
	{
#if !LOG_ENABLED
		clsDx();
		printfDx("開発中");
#endif
	}

	// < app

	// DxLib >

	ScreenFlip();

	if(!IgnoreEscapeKey && CheckHitKey(KEY_INPUT_ESCAPE) == 1 || ProcessMessage() == -1)
	{
		EndProc();
	}

	// < DxLib

	CheckHz();

	ProcFrame++;
	errorCase(IMAX < ProcFrame); // 192.9日程度でカンスト
	m_countDown(FreezeInputFrame);
	WindowIsActive = IsWindowActive();

	PadEachFrame();
	KeyEachFrame();
	InputEachFrame();
	MouseEachFrame();

	if(Gnd.RealScreen_W != SCREEN_W || Gnd.RealScreen_H != SCREEN_H)
	{
		if(!Gnd.MainScreen)
			Gnd.MainScreen = CreateSubScreen(SCREEN_W, SCREEN_H);

		ChangeDrawScreen(Gnd.MainScreen);
	}
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void FreezeInput(int frame) // frame: 1 == このフレームのみ, 2 == このフレームと次のフレーム ...
{
	errorCase(frame < 1 || IMAX < frame);
	FreezeInputFrame = frame;
}
