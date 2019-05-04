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
__int64 LangolierTime;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double EatenByLangolierEval = 0.5;
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
// }

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void CheckHz(void)
{
	__int64 currTime = GetCurrTime();

	if(!ProcFrame)
		LangolierTime = currTime;
	else
		LangolierTime += 16; // 16.666 より小さいので、60Hzならどんどん引き離されるはず。
//		LangolierTime += 17; // test -- EBLE 0.20 あたり
//		LangolierTime += 18; // test -- EBLE 0.45 あたり
//		LangolierTime += 19; // test -- EBLE 0.59 あたり
//		LangolierTime += 20; // test -- EBLE 0.67 あたり

	while(currTime < LangolierTime)
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
	EatenByLangolierEval *= 0.99;

	FrameStartTime = currTime;
}

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

	if(900 < ProcFrame && 0.1 < EatenByLangolierEval) // 暫定 暫定 暫定 暫定 暫定
	{
		static int passedCount = 900;

		if(m_countDown(passedCount))
		{
			DPE_SetBright(GetColor(128, 0, 0));
			DPE_SetAlpha(0.5);
			DrawRect(P_WHITEBOX, 0, 0, SCREEN_W, 16);
			DPE_Reset();

			SetPrint();
			PE.Color = GetColor(255, 255, 0);
			Print_x(xcout("V-SYNC ALERT / EBLE=%.3f FST=%I64d LT=%I64d (%d) %d", EatenByLangolierEval, FrameStartTime, LangolierTime, passedCount, ProcFrame));
			PE_Reset();
		}
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
