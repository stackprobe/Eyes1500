/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int MouseRot;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int MouseStatus[MOUBTN_MAX];

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void MouseEachFrame(void)
{
	uint status;

	if(WindowIsActive)
	{
		MouseRot = GetMouseWheelRotVol();
		status = (uint)GetMouseInput();
	}
	else // ? 非アクティブ -> 無入力
	{
		MouseRot = 0;
		status = 0u;
	}
	m_range(MouseRot, -IMAX, IMAX);

	updateInput(MouseStatus[MOUBTN_L], status & MOUSE_INPUT_LEFT);
	updateInput(MouseStatus[MOUBTN_M], status & MOUSE_INPUT_MIDDLE);
	updateInput(MouseStatus[MOUBTN_R], status & MOUSE_INPUT_RIGHT);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int GetMouInput(int mouBtnId)
{
	errorCase(mouBtnId < 0 || MOUBTN_MAX <= mouBtnId);

	return FreezeInputFrame ? 0 : MouseStatus[mouBtnId];
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000109 $$$$ //	int GetMouPound(int mouBtnId)
// #### DELETED ==== 0000109 $$$$ //	{
// #### DELETED ==== 0000109 $$$$ //		return isPound(GetMouInput(mouBtnId));
// #### DELETED ==== 0000109 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int MouseX = SCREEN_CENTER_X;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int MouseY = SCREEN_CENTER_Y;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void UpdateMousePos(void)
{
	errorCase(GetMousePoint(&MouseX, &MouseY)); // ? 失敗

	MouseX *= SCREEN_W;
	MouseX /= Gnd.RealScreen_W;
	MouseY *= SCREEN_H;
	MouseY /= Gnd.RealScreen_H;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void ApplyMousePos(void)
{
	int mx = MouseX;
	int my = MouseY;

	mx *= Gnd.RealScreen_W;
	mx /= SCREEN_W;
	my *= Gnd.RealScreen_H;
	my /= SCREEN_H;

	errorCase(SetMousePoint(mx, my)); // ? 失敗
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int MouseMoveX;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int MouseMoveY;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000110 $$$$ //	void UpdateMouseMove(void)
// #### DELETED ==== 0000110 $$$$ //	{
// #### DELETED ==== 0000110 $$$$ //		static int lastFrame = -IMAX;
// #### DELETED ==== 0000110 $$$$ //		static int centerX = SCREEN_CENTER_X;
// #### DELETED ==== 0000110 $$$$ //		static int centerY = SCREEN_CENTER_Y;
// #### DELETED ==== 0000110 $$$$ //	
// #### DELETED ==== 0000110 $$$$ //		errorCase(ProcFrame <= lastFrame); // ? 2回以上更新した。
// #### DELETED ==== 0000110 $$$$ //	
// #### DELETED ==== 0000110 $$$$ //		UpdateMousePos();
// #### DELETED ==== 0000110 $$$$ //	
// #### DELETED ==== 0000110 $$$$ //		MouseMoveX = MouseX - centerX;
// #### DELETED ==== 0000110 $$$$ //		MouseMoveY = MouseY - centerY;
// #### DELETED ==== 0000110 $$$$ //	
// #### DELETED ==== 0000110 $$$$ //		MouseX = centerX;
// #### DELETED ==== 0000110 $$$$ //		MouseY = centerY;
// #### DELETED ==== 0000110 $$$$ //	
// #### DELETED ==== 0000110 $$$$ //		ApplyMousePos();
// #### DELETED ==== 0000110 $$$$ //	
// #### DELETED ==== 0000110 $$$$ //		if(lastFrame + 1 < ProcFrame) // ? 1フレーム以上更新しなかった。
// #### DELETED ==== 0000110 $$$$ //		{
// #### DELETED ==== 0000110 $$$$ //			MouseMoveX = 0;
// #### DELETED ==== 0000110 $$$$ //			MouseMoveY = 0;
// #### DELETED ==== 0000110 $$$$ //		}
// #### DELETED ==== 0000110 $$$$ //		lastFrame = ProcFrame;
// #### DELETED ==== 0000110 $$$$ //	}
