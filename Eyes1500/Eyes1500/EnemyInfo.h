typedef struct EnemyShotInfo_st
{
	double X;
	double Y;
}
EnemyShotInfo_t;

typedef struct
{
	int HP;
	int Score;
	double MoveSpeed;
	double TamaSpeed;
	autoList<EnemyShotInfo_t> *ShotInfos;
}
EnemyInfo_t;

EnemyInfo_t *GetEnemyInfo(EnemyKind_t kind);
