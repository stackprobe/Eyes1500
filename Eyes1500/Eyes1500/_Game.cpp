#include "all.h"

GDc_t GDc;

void GameInit(void)
{
	memset(&GDc, 0x00, sizeof(GDc));

	GDc.PlayerTamaList = new autoList<PlayerTama_t *>();
	GDc.PlayerMissileList = new autoList<PlayerMissile_t *>();
	GDc.EnemyList = new autoList<Enemy_t *>();
	GDc.EnemyTamaList = new autoList<EnemyTama_t *>();
}
void GameFnlz(void)
{
#if 0 // old same
	while(GDc.PlayerTamaList->GetCount())
	{
		ReleasePlayerTama(GDc.PlayerTamaList->UnaddElement());
	}
#elif 0 // old same
	GDc.PlayerTamaList->CallAllElement(ReleasePlayerTama);
	delete GDc.PlayerTamaList;
#else
	releaseList(GDc.PlayerTamaList, ReleasePlayerTama);
#endif
	releaseList(GDc.PlayerMissileList, ReleasePlayerMissile);
	releaseList(GDc.EnemyList, ReleaseEnemy);
	releaseList(GDc.EnemyTamaList, ReleaseEnemyTama);

	memset(&GDc, 0x00, sizeof(GDc));
}
