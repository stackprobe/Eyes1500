#include "all.h"

static autoList<char *> *Lines;

static autoList<StageInfo_t> *StageInfos;

static void INIT(void)
{
	{
		static int inited;

		if(inited)
			return;

		inited = 1;
	}

	Lines = readLines(GetEtcRes()->GetHandle(ETC_STAGE_INFO));

	GetEtcRes()->UnloadAllHandle(); // ëeëÂÉSÉ~äJï˙

	errorCase(Lines->GetCount() < 1); // 2bs

	StageInfos = new autoList<StageInfo_t>();

	for(int index = 0; index < Lines->GetCount(); index++)
	{
		StageInfo_t info;

		info.EnemyInfos = new autoList<StageEnemyInfo_t>();

		tokinit(Lines->GetElement(index), ",");

		for(; ; )
		{
			StageEnemyInfo_t enemyInfo;

			char *line = toknext(NULL, NULL);

			if(!line)
				break;

			int eyenum = atoi(line);
			EnemyKind_t kind;

			switch(eyenum)
			{
			case 1: kind = EK_EYE_1; break;
			case 2: kind = EK_EYE_2; break;
			case 3: kind = EK_EYE_3; break;
			case 4: kind = EK_EYE_4; break;
			case 5: kind = EK_EYE_5; break;
			case 6: kind = EK_EYE_6; break;
			case 7: kind = EK_EYE_7; break;
			case 8: kind = EK_EYE_8; break;
			case 9: kind = EK_EYE_9; break;
			case 10: kind = EK_EYE_10; break;
			case 20: kind = EK_EYE_20; break;
			case 50: kind = EK_EYE_50; break;
			case 100: kind = EK_EYE_100; break;

			default:
				error();
			}
			enemyInfo.Kind = kind;

			line = ne_toknext(NULL, NULL);
			errorCase(line[0] != 'X');
			enemyInfo.X = atof(line + 1);

			line = ne_toknext(NULL, NULL);
			errorCase(line[0] != 'Y');
			enemyInfo.Y = atof(line + 1);

			errorCase(!m_isRange(enemyInfo.X, 0.0, 1000.0)); // 2bs
			errorCase(!m_isRange(enemyInfo.Y, 0.0, 1000.0)); // 2bs
			info.EnemyInfos->AddElement(enemyInfo);
		}
		errorCase(info.EnemyInfos->GetCount() < 1); // 2bs
		StageInfos->AddElement(info);
	}
}
int GetStageCount(void)
{
	INIT();
	return Lines->GetCount();
}
void AddEnemyByStageIndex(int stageIndex) // GameMain()ì‡Ç©ÇÁåƒÇ‘Ç±Ç∆ÅB
{
	INIT();
	error(); // TODO
}
