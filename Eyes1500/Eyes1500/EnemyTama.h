typedef struct EnemyTama_st
{
	int Frame;
	double X;
	double Y;
	double Dir; // 0.0 Å` PI * 2
	double Speed; // dot per frame
}
EnemyTama_t;

EnemyTama_t *CreateEnemyTama(double x, double y, double dir, double speed);
void ReleaseEnemyTama(EnemyTama_t *i);

// <-- cdtor

int EnemyTamaEachFrame(EnemyTama_t *i);
void DrawEnemyTama(EnemyTama_t *i);

// <-- accessor

void Enemy_Shot(Enemy_t *enemy);
