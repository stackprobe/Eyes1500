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
