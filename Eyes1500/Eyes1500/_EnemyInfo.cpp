#include "all.h"

static autoList<char *> *Lines;
static autoList<char *> *ShotLines;

static void INIT(void)
{
	{
		static int inited;

		if(inited)
			return;

		inited = 1;
	}

	Lines     = readLines(GetEtcRes()->GetHandle(ETC_ENEMY_INFO));
	ShotLines = readLines(GetEtcRes()->GetHandle(ETC_ENEMY_SHOT_INFO));

	GetEtcRes()->UnloadAllHandle(); // ‘e‘åƒSƒ~ŠJ•ú
}
EnemyInfo_t *GetEnemyInfo(EnemyKind_t kind)
{
	INIT();

	errorCase(!m_isRange((int)kind, 0, Lines->GetCount() - 1)); // 2bs

	error(); // TODO
	return NULL;
}
