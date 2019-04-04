#include "all.h"

EnemyTama_t *CreateEnemyTama(double x, double y, double dir, double speed)
{
	EnemyTama_t *i = nb(EnemyTama_t);

	i->X = x;
	i->Y = y;
	i->Dir = dir;
	i->Speed = speed;

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
	
	angleMoveXY(i->Dir, i->Speed, i->X, i->Y);

	return IsOutOfScreen(i->X, i->Y, 100.0); // ‰æ–Êã•”‚©‚ç‚Í‚Ýo‚µ‚½ó‘Ô‚ÅŒ‚‚Â‚±‚Æ‚à‚ ‚é‚½‚ßAmargin
}
void DrawEnemyTama(EnemyTama_t *i)
{
	int frm = i->Frame - 1; // frm == 0`

	DrawCenter(D_ENEMY_SHOT_00 + frm / 6 % 4 | DTP, i->X, i->Y);
}

// <-- accessor

void Enemy_Shot(Enemy_t *enemy)
{
	EnemyInfo_t *ei = GetEnemyInfo(enemy->Kind);

	for(int index = 0; index < ei->ShotInfos->GetCount(); index++)
	{
		EnemyShotInfo_t esi = ei->ShotInfos->GetElement(index);

		double eye_x = enemy->X - GetEnemy_W(enemy->Kind) / 2.0 + esi.X;
		double eye_y = enemy->Y - GetEnemy_H(enemy->Kind) / 2.0 + esi.Y;

		GDc.EnemyTamaList->AddElement(CreateEnemyTama(
			eye_x,
			eye_y,
			getAngle(GDc.Player.X, GDc.Player.Y, enemy->X, enemy->Y),
			ENEMY_TAMA_SPEED_CONV(GetEnemyInfo(enemy->Kind)->TamaSpeed)
			));
	}
}
