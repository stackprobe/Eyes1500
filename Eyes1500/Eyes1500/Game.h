typedef struct GDc_st
{
	// Params {
	// }

	// Return {
	// }

	__int64 Score;

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
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
