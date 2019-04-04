typedef struct GDcNV_st // GDc �� Non-volatile
{
	int HiSpeed;
	int X;
	int Y;
	int HP; // 0 == ����, 1�` �����p��HP

	__int64 Score;
	double ScoreDisp;
	int DeficitFrame; // 0 == ����, 1�` == �Ԏ����
}
GDcNV_t;

extern GDcNV_t GDcNV;

void GameInitNonvola(void);
void GameFnlzNonvola(void);

typedef struct GDc_st
{
	// Params {
	int StageIndex; // 0 �` GetStageCount() - 1
	// }

	// Return {
	int WillNextStage; // ? ���g�Ɍ������B
	// }

	struct
	{
		int BornFrame; // 0 == ����, 1�`
		double X;
		double Y;
		double RealX;
		double RealY;
		int HiSpeed;
		int HP;
		int DamagedFrame; // 0 == ����, 1�`
		int DeadFrame;    // 0 == ����, 1�`
	}
	Player;

	int BattleStarted;
	int LaserFrame; // 0 == ����, 1�` == �Ǝ˒�, -1 == �ƎˏI������
	int FlashFrame; // 0 == ����, 1�` == �Ǝ˒�

	autoList<PlayerTama_t *> *PlayerTamaList;
	autoList<PlayerMissile_t *> *PlayerMissileList;
	autoList<Enemy_t *> *EnemyList;
	autoList<EnemyTama_t *> *EnemyTamaList;

	int StageToStageFlag;
	int BattleNotStartedFrame;
	int NoEnemyFrame; // 0 == ����, 1�` == �G�������
	int GameOver;
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
