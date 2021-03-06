#include "all.h"

int IgnoreEscapeKey;

// 他のファイルからは read only {
__int64 FrameStartTime;
__int64 HzChaserTime;
__int64 LowHzTime;
double EatenByLangolierEval = 0.5;
double LowHzErrorRate = 0.0;
int ProcFrame;
int FreezeInputFrame;
int WindowIsActive;
// }

static void CheckHz(void)
{
	__int64 currTime = GetCurrTime();

	if(!ProcFrame)
	{
		HzChaserTime = currTime;
		LowHzTime = currTime;
	}
	else
	{
		HzChaserTime += 16; // 16.666 より小さいので、60Hzならどんどん引き離されるはず。
		LowHzTime += 17;
	}

	while(currTime < HzChaserTime)
	{
		Sleep(1);

		// DxLib >

		ScreenFlip();

		if(ProcessMessage() == -1)
		{
			EndProc();
		}

		// < DxLib

		currTime = GetCurrTime();
		m_approach(EatenByLangolierEval, 1.0, 0.9);
	}
	m_maxim(HzChaserTime, currTime - 30);
	EatenByLangolierEval *= 0.99;

	if(LowHzTime < currTime)
	{
		m_maxim(LowHzTime, currTime - 10);
		m_approach(LowHzErrorRate, 1.0, 0.999);
	}
	else
	{
		m_minim(LowHzTime, currTime + 20);
		LowHzErrorRate *= 0.99;
	}

//	LOG("%I64d\n", currTime - FrameStartTime); // test

	FrameStartTime = currTime;
}

void EachFrame(void)
{
	if(!SEEachFrame())
	{
		MusicEachFrame();
	}
	Gnd.EL->ExecuteAllTask();
	CurtainEachFrame();

	if(600 < ProcFrame && (0.1 < EatenByLangolierEval || 0.1 < LowHzErrorRate)) // FPS 警告
	{
		SetPrint();
		PE.Color = GetColor(255, 255, 255);
		PE_Border(GetColor(0, 0, 255));
		Print_x(xcout("FPS TUNING EBLE=%.3f LHzER=%.3f", EatenByLangolierEval, LowHzErrorRate));
		PE_Reset();
	}

	// app > @ before draw screen

	// < app

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

#if 1 // debug debug debug debug debug
	clsDx();
	printfDx("\n開発中ver.");
#endif

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
