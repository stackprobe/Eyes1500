#include "all.h"

static autoList<char *> *Lines;

static void INIT(void)
{
	{
		static int inited;

		if(inited)
			return;

		inited = 1;
	}

	Lines = readLines(GetEtcRes()->GetHandle(ETC_STAGE_INFO));

	GetEtcRes()->UnloadAllHandle(); // ‘e‘åƒSƒ~ŠJ•ú
}
int GetStageCount(void)
{
	INIT();
	return Lines->GetCount();
}
void AddEnemyByStageIndex(int stageIndex)
{
	INIT();
	error(); // TODO
}
