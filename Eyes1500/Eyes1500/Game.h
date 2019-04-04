typedef struct GDcNV_st // GDc Ì Non-volatile
{
	int HiSpeed;
	int X;
	int Y;
	int HP; // 0 == ³ø, 1` ø«p®HP

	__int64 Score;
	double ScoreDisp;
	int DeficitFrame; // 0 == ³ø, 1` == ÔóÔ
}
GDcNV_t;

extern GDcNV_t GDcNV;

void GameInitNonvola(void);
void GameFnlzNonvola(void);

typedef struct GDc_st
{
	// Params {
	int StageIndex; // 0 ` GetStageCount() - 1
	// }

	// Return {
	int WillNextStage; // ? gÉü©¤B
	// }

	struct
	{
		int BornFrame; // 0 == ³ø, 1`
		double X;
		double Y;
		double RealX;
		double RealY;
		int HiSpeed;
		int HP;
		int DamagedFrame; // 0 == ³ø, 1`
		int DeadFrame;    // 0 == ³ø, 1`
	}
	Player;

	int BattleStarted;
	int LaserFrame; // 0 == ³ø, 1` == ÆË, -1 == ÆËI¹¼ã
	int FlashFrame; // 0 == ³ø, 1` == ÆË

	autoList<PlayerTama_t *> *PlayerTamaList;
	autoList<PlayerMissile_t *> *PlayerMissileList;
	autoList<Enemy_t *> *EnemyList;
	autoList<EnemyTama_t *> *EnemyTamaList;

	int StageToStageFlag;
	int BattleNotStartedFrame;
	int NoEnemyFrame; // 0 == ³ø, 1` == G³µóÔ
	int GameOver;
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
