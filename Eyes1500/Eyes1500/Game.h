typedef struct GDc_st
{
	// Params {
	int StageIndex; // 0 ` GetStageCount() - 1
	// }

	// Return {
	// }

	__int64 Score;

	struct
	{
		int BornFrame; // 0 == –³Œø, 1`
		double X;
		double Y;
		double RealX;
		double RealY;
		int HiSpeed;
		int HP;
		int DamagedFrame; // 0 == –³Œø, 1`
		int DeadFrame;    // 0 == –³Œø, 1`
	}
	Player;

	int BattleStarted;
	int LaserFrame; // 0 == –³Œø, 1` == ÆË’†, -1 == ÆËI—¹’¼Œã
	int FlashFrame; // 0 == –³Œø, 1` == ÆË’†

	autoList<PlayerTama_t *> *PlayerTamaList;
	autoList<PlayerMissile_t *> *PlayerMissileList;
	autoList<Enemy_t *> *EnemyList;
	autoList<EnemyTama_t *> *EnemyTamaList;

	int BattleNotStartedFrame;
	int NoEnemyFrame; // 0 == –³Œø, 1` == “G–³‚µó‘Ô
	int WillNextWave; // ? Ÿ”g‚ÉŒü‚©‚¤B
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
