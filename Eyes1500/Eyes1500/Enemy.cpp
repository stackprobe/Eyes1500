#include "all.h"

Enemy_t *CreateEnemy(EnemyKind_t kind, double x, double y)
{
	Enemy_t *i = nb(Enemy_t);

	i->Kind = kind;
	i->X = x;
	i->Y = y;

	i->HP = 100; // zantei

	return i;
}
void ReleaseEnemy(Enemy_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

int EnemyEachFrame(Enemy_t *i) // ret: ? Á–Å
{
	int frm = i->Frame++; // frm == 0`


	// zantei

	if(i->DamagedFrame == 0 && GDc.FlashFrame == 0)
	{
		i->Y += 2.0;
	}

	if(dRnd() < 0.003)
	{
		Enemy_Shot(i);
	}


	m_countDown(i->DamagedFrame);

	return SCREEN_H + 10.0 < i->Y;
}
void DrawEnemy(Enemy_t *i)
{
	// zantei

	if(!GDc.BattleStarted)
	{
		// i->Frame == 0 ŒÅ’è

		DPE_SetAlpha(0.5);
		DrawCenter(D_EYE_1_00 + ProcFrame / 6 % 2 | DTP, d2i(i->X), d2i(i->Y));
		DPE_Reset();
	}
	else
	{
		int frm = i->Frame - 1; // frm == 0`

		if(i->DamagedFrame)
		{
			DrawCenter(D_EYE_1_00 + 2 + frm / 3 % 2 | DTP, d2i(i->X), d2i(i->Y));
		}
		else
		{
			DrawCenter(D_EYE_1_00 + frm / 6 % 2 | DTP, d2i(i->X), d2i(i->Y));
		}
	}
}

// <-- accessor

Enemy_t *GetNearestEnemy(double x, double y)
{
	Enemy_t *ret = NULL;
	double ret_distance = -1.0;

	for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *i = GDc.EnemyList->GetElement(index);
		double distance = GetDistance(x, y, i->X, i->Y);

		if(!ret || distance < ret_distance)
		{
			ret = i;
			ret_distance = distance;
		}
	}
	return ret;
}
