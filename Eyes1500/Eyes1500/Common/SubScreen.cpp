/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static oneObject(autoList<SubScreen_t *>, new autoList<SubScreen_t *>(), GetSubScreenList);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
SubScreen_t *CreateSubScreen(int w, int h, int aFlag)
{
	errorCase(w < 1 || IMAX < w);
	errorCase(h < 1 || IMAX < h);

	SubScreen_t *i = nb(SubScreen_t);

	i->W = w;
	i->H = h;
	i->AFlag = aFlag;
	i->Handle = -1;

	GetSubScreenList()->AddElement(i);
	return i;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/

// <-- cdtor

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int GetHandle(SubScreen_t *i)
{
	errorCase(i == NULL);

	if(i->Handle == -1)
	{
		i->Handle = MakeScreen(i->W, i->H, i->AFlag ? TRUE : FALSE);
		errorCase(i->Handle == -1); // ? Ž¸”s
	}
	return i->Handle;
}

// <-- accessor

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int CurrDrawScreenHandle = DX_SCREEN_BACK;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void ChangeDrawScreen(int handle)
{
	errorCase(SetDrawScreen(handle)); // ? Ž¸”s
	CurrDrawScreenHandle = handle;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void ChangeDrawScreen(SubScreen_t *screen)
{
	ChangeDrawScreen(GetHandle(screen));
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void UnloadAllSubScreenHandle(void)
{
	ChangeDrawScreen(DX_SCREEN_BACK); // ‚±‚ê‚©‚çŠJ•ú‚·‚éƒnƒ“ƒhƒ‹‚Å‚ ‚é‚Æƒ}ƒY‚¢‚Ì‚Å...

	for(int index = 0; index < GetSubScreenList()->GetCount(); index++)
	{
		SubScreen_t *i = GetSubScreenList()->GetElement(index);

		if(i->Handle != -1)
		{
			errorCase(DeleteGraph(i->Handle)); // ? Ž¸”s
			i->Handle = -1;
		}
	}
}
