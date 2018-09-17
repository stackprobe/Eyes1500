#include "all.h"

GDc_t GDc;

void GameInit(void)
{
	memset(&GDc, 0x00, sizeof(GDc));

	GDc.PlayerTamaList = new autoList<PlayerTama_t *>();
	GDc.PlayerMissileList = new autoList<PlayerMissile_t *>();
	GDc.EnemyList = new autoList<Enemy_t *>();
}
void GameFnlz(void)
{
	/*
	while(GDc.PlayerTamaList->GetCount())
	{
		ReleasePlayerTama(GDc.PlayerTamaList->UnaddElement());
	}
	*/
	GDc.PlayerTamaList->CallAllElement(ReleasePlayerTama);
	delete GDc.PlayerTamaList;

	GDc.PlayerMissileList->CallAllElement(ReleasePlayerMissile);
	delete GDc.PlayerMissileList;

	GDc.EnemyList->CallAllElement(ReleaseEnemy);
	delete GDc.EnemyList;

	memset(&GDc, 0x00, sizeof(GDc));
}
