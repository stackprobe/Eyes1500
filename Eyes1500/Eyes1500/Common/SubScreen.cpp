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
// #### DELETED ==== 0000145 $$$$ //	void ReleaseSubScreen(SubScreen_t *i)
// #### DELETED ==== 0000145 $$$$ //	{
// #### DELETED ==== 0000145 $$$$ //		if(i == NULL)
// #### DELETED ==== 0000145 $$$$ //			return;
// #### DELETED ==== 0000145 $$$$ //	
// #### DELETED ==== 0000145 $$$$ //		for(int index = 0; index < GetSubScreenList()->GetCount(); index++)
// #### DELETED ==== 0000145 $$$$ //		{
// #### DELETED ==== 0000145 $$$$ //			if(GetSubScreenList()->GetElement(index) == i)
// #### DELETED ==== 0000145 $$$$ //			{
// #### DELETED ==== 0000145 $$$$ //				GetSubScreenList()->FastDesertElement(index);
// #### DELETED ==== 0000145 $$$$ //				goto endDesert;
// #### DELETED ==== 0000145 $$$$ //			}
// #### DELETED ==== 0000145 $$$$ //		}
// #### DELETED ==== 0000145 $$$$ //		error(); // not found
// #### DELETED ==== 0000145 $$$$ //	endDesert:
// #### DELETED ==== 0000145 $$$$ //	
// #### DELETED ==== 0000145 $$$$ //		if(i->Handle != -1)
// #### DELETED ==== 0000145 $$$$ //			errorCase(DeleteGraph(i->Handle)); // ? é∏îs
// #### DELETED ==== 0000145 $$$$ //	
// #### DELETED ==== 0000145 $$$$ //		memFree(i);
// #### DELETED ==== 0000145 $$$$ //	}

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
		errorCase(i->Handle == -1); // ? é∏îs
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
	errorCase(SetDrawScreen(handle)); // ? é∏îs
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
// #### DELETED ==== 0000146 $$$$ //	void RestoreDrawScreen(void)
// #### DELETED ==== 0000146 $$$$ //	{
// #### DELETED ==== 0000146 $$$$ //		ChangeDrawScreen(Gnd.MainScreen ? GetHandle(Gnd.MainScreen) : DX_SCREEN_BACK);
// #### DELETED ==== 0000146 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000147 $$$$ //	i2D_t GetSubScreenSize(SubScreen_t *screen)
// #### DELETED ==== 0000147 $$$$ //	{
// #### DELETED ==== 0000147 $$$$ //		i2D_t size;
// #### DELETED ==== 0000147 $$$$ //	
// #### DELETED ==== 0000147 $$$$ //		size.X = screen->W;
// #### DELETED ==== 0000147 $$$$ //		size.Y = screen->H;
// #### DELETED ==== 0000147 $$$$ //	
// #### DELETED ==== 0000147 $$$$ //		return size;
// #### DELETED ==== 0000147 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000148 $$$$ //	i2D_t GetDrawScreenSize(void) // ï`âÊóÃàÊÇÃÉTÉCÉYÅH
// #### DELETED ==== 0000148 $$$$ //	{
// #### DELETED ==== 0000148 $$$$ //		int w;
// #### DELETED ==== 0000148 $$$$ //		int h;
// #### DELETED ==== 0000148 $$$$ //		int cbd;
// #### DELETED ==== 0000148 $$$$ //	
// #### DELETED ==== 0000148 $$$$ //		errorCase(GetScreenState(&w, &h, &cbd));
// #### DELETED ==== 0000148 $$$$ //		errorCase(!m_isRange(w, 1, IMAX));
// #### DELETED ==== 0000148 $$$$ //		errorCase(!m_isRange(h, 1, IMAX));
// #### DELETED ==== 0000148 $$$$ //	
// #### DELETED ==== 0000148 $$$$ //		i2D_t size;
// #### DELETED ==== 0000148 $$$$ //	
// #### DELETED ==== 0000148 $$$$ //		size.X = w;
// #### DELETED ==== 0000148 $$$$ //		size.Y = h;
// #### DELETED ==== 0000148 $$$$ //	
// #### DELETED ==== 0000148 $$$$ //		return size;
// #### DELETED ==== 0000148 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void UnloadAllSubScreenHandle(void)
{
	ChangeDrawScreen(DX_SCREEN_BACK); // Ç±ÇÍÇ©ÇÁäJï˙Ç∑ÇÈÉnÉìÉhÉãÇ≈Ç†ÇÈÇ∆É}ÉYÇ¢ÇÃÇ≈...

	for(int index = 0; index < GetSubScreenList()->GetCount(); index++)
	{
		SubScreen_t *i = GetSubScreenList()->GetElement(index);

		if(i->Handle != -1)
		{
			errorCase(DeleteGraph(i->Handle)); // ? é∏îs
			i->Handle = -1;
		}
	}
}
