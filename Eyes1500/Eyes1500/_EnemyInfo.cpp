#include "all.h"

static autoList<char *> *Lines;
static autoList<char *> *ShotLines;

static autoList<EnemyInfo_t > *EnemyInfos;

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

	errorCase(Lines->GetCount() != EK_MAX); // 2bs
	errorCase(Lines->GetCount() != ShotLines->GetCount()); // 2bs

	EnemyInfos = new autoList<EnemyInfo_t>();

	for(int index = 0; index < Lines->GetCount(); index++)
	{
		EnemyInfo_t info;

		tokinit(Lines->GetElement(index), ",");

		info.HP = atoi(ne_toknext(NULL, NULL));
		info.Score = atoi(ne_toknext(NULL, NULL));
		info.MoveSpeed = atof(ne_toknext(NULL, NULL));
		info.TamaSpeed = atof(ne_toknext(NULL, NULL));

		info.ShotInfos = new autoList<EnemyShotInfo_t>();

		tokinit(ShotLines->GetElement(index), ",");

		for(; ; )
		{
			EnemyShotInfo_t shotInfo;

			char *line = toknext(NULL, NULL);

			if(!line)
				break;

			errorCase(line[0] != 'X');
			shotInfo.X = atof(line + 1);

			line = ne_toknext(NULL, NULL);
			errorCase(line[0] != 'Y');
			shotInfo.Y = atof(line + 1);

			errorCase(!m_isRange(shotInfo.X, 0.0, 1000.0)); // 2bs
			errorCase(!m_isRange(shotInfo.Y, 0.0, 1000.0)); // 2bs
			info.ShotInfos->AddElement(shotInfo);
		}
		errorCase(info.ShotInfos->GetCount() < 1); // 2bs
		EnemyInfos->AddElement(info);
	}
}
EnemyInfo_t *GetEnemyInfo(EnemyKind_t kind)
{
	INIT();

	errorCase(!m_isRange((int)kind, 0, EK_MAX - 1)); // 2bs

	return EnemyInfos->ElementAt((int)kind);
}
