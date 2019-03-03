#include "all.h"

EnemyTama_t *CreateEnemyTama(double x, double y, double dir)
{
	EnemyTama_t *i = nb(EnemyTama_t);

	i->X = x;
	i->Y = y;
	i->Dir = dir;

	return i;
}
void ReleaseEnemyTama(EnemyTama_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

int EnemyTamaEachFrame(EnemyTama_t *i) // ret: ? Á–Å
{
	int frm = i->Frame++; // frm == 0`
	

	// zantei

	angleMoveXY(i->Dir, 3.0, i->X, i->Y);


	return IsOutOfScreen(i->X, i->Y);
}
void DrawEnemyTama(EnemyTama_t *i)
{
	int frm = i->Frame - 1; // frm == 0`

	DrawCenter(D_ENEMY_SHOT_00 + frm / 6 % 4 | DTP, i->X, i->Y);
}

// <-- accessor

void Enemy_Shot(Enemy_t *enemy)
{
	GDc.EnemyTamaList->AddElement(CreateEnemyTama(
		enemy->X,
		enemy->Y,
		getAngle(GDc.Player.X, GDc.Player.Y, enemy->X, enemy->Y)
		));
}
