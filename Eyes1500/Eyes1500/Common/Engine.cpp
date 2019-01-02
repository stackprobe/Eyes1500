#include "all.h"

int IgnoreEscapeKey;

// 他のファイルからは read only {
__int64 FrameStartTime;
int ProcFrame;
int FreezeInputFrame;
int WindowIsActive;
int FrameRateDropCount;
int NoFrameRateDropCount;
// }

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

int InnerDrawScrHdl = -1;

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

		// app >

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

	// app >

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
void FreezeInput(int frame) // frame: 1 == このフレームのみ, 2 == このフレームと次のフレーム ...
{
	errorCase(frame < 1 || IMAX < frame);
	FreezeInputFrame = frame;
}
