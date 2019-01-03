//
// copied the source file by CopyLib.exe
//
enum
{
	MOUBTN_L,
	MOUBTN_M,
	MOUBTN_R,

	MOUBTN_MAX, // num of member
};

//
// copied the source file by CopyLib.exe
//
extern int MouseRot;
//
// copied the source file by CopyLib.exe
//
extern int MouseX;
//
// copied the source file by CopyLib.exe
//
extern int MouseY;
//
// copied the source file by CopyLib.exe
//
extern int MouseMoveX;
//
// copied the source file by CopyLib.exe
//
extern int MouseMoveY;

//
// copied the source file by CopyLib.exe
//
void MouseEachFrame(void);
//
// copied the source file by CopyLib.exe
//
int GetMouInput(int mouBtnId);
//
// copied the source file by CopyLib.exe
//
int GetMouPound(int mouBtnId);
//
// copied the source file by CopyLib.exe
//
void UpdateMousePos(void);
//
// copied the source file by CopyLib.exe
//
void ApplyMousePos(void);
//
// copied the source file by CopyLib.exe
//
void UpdateMouseMove(void);
