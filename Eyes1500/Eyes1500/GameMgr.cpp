#include "all.h"

void GameMgrMain(void)
{
	int stgIndex = 0;

	for(stgIndex = 0; stgIndex < GetStageCount(); stgIndex++)
	{
		GameInit();
		GDc.StageIndex = stgIndex;
		GameMain();
		int wnw = GDc.WillNextWave;
		GameFnlz();

		if(!wnw)
			return;
	}
	// TODO ending
}
