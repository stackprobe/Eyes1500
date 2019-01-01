typedef struct StageEnemyInfo_st
{
	EnemyKind_t Kind;
	double X;
	double Y;
}
StageEnemyInfo_t;

typedef struct StageInfo_st
{
	autoList<StageEnemyInfo_t> *EnemyInfos;
}
StageInfo_t;

int GetStageCount(void);
void AddEnemyByStageIndex(int stageIndex);
