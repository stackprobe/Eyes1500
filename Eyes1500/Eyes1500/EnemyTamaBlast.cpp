#include "all.h"

EnemyTamaBlast_t *CreateEnemyTamaBlast(int x, int y)
{
	EnemyTamaBlast_t *i = nb(EnemyTamaBlast_t);

	i->X = x;
	i->Y = y;

	return i;
}
void ReleaseEnemyTamaBlast(EnemyTamaBlast_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

int EnemyTamaBlastEachFrame(EnemyTamaBlast_t *i) // ret: ? Á–Å
{
	int frm = i->Frame++; // 0`

	return frm == ENEMY_TAMA_BLAST_FRAME_MAX;
}
void DrawEnemyTamaBlast(EnemyTamaBlast_t *i)
{
	int frm = i->Frame - 1; // 0`

	double a = (ENEMY_TAMA_BLAST_FRAME_MAX - frm) * 1.0 / ENEMY_TAMA_BLAST_FRAME_MAX;
	m_range(a, 0.0, 1.0);
	a = a * 0.7 + 0.3;

	if(frm / 3 % 2 == 1)
		a /= 2.0;

	DPE_SetAlpha(a);
	DrawCenter(P_ENEMY_BOMB, i->X, i->Y);
	DPE_Reset();
}

// <-- accessor
