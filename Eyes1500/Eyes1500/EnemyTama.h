typedef struct EnemyTama_st
{
	int Frame;
	double X;
	double Y;
	double Dir; // 0.0 Å` PI * 2
}
EnemyTama_t;

EnemyTama_t *CreateEnemyTama(void);
void ReleaseEnemyTama(EnemyTama_t *i);

// <-- cdtor

int EnemyTamaEachFrame(EnemyTama_t *i);
void DrawEnemyTama(EnemyTama_t *i);

// <-- accessor

void Enemy_Shot(Enemy_t *enemy);
