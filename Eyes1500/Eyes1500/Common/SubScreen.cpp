#include "all.h"

static oneObject(autoList<SubScreen_t *>, new autoList<SubScreen_t *>(), GetSubScreenList);

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

// <-- cdtor

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

int CurrDrawScreenHandle = DX_SCREEN_BACK;

void ChangeDrawScreen(int handle)
{
	errorCase(SetDrawScreen(handle)); // ? Ž¸”s
	CurrDrawScreenHandle = handle;
}
void ChangeDrawScreen(SubScreen_t *screen)
{
	ChangeDrawScreen(GetHandle(screen));
}

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
