typedef struct EnemyTama_st
{
	int Frame;
	int BombFrame; // -1 == –³Œø, 0` == ”š”­‚·‚éfrm(0`)
	int Homing; // BOOL
	double X;
	double Y;
	double Dir; // 0.0 ` PI * 2
	double Speed; // dot per frame
}
EnemyTama_t;

EnemyTama_t *CreateEnemyTama(double x, double y, double dir, double speed, int bombFrame, int homing);
void ReleaseEnemyTama(EnemyTama_t *i);

// <-- cdtor

int EnemyTamaEachFrame(EnemyTama_t *i);
void DrawEnemyTama(EnemyTama_t *i);

// <-- accessor

void Enemy_Shot(Enemy_t *enemy, int bombFlag, int homing);
