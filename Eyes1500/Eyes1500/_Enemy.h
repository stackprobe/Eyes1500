typedef struct Enemy_st
{
	EnemyKind_t Kind;
	double X;
	double Y;
	int Frame;
}
Enemy_t;

Enemy_t *CreateEnemy(EnemyKind_t kind, double x, double y);
void ReleaseEnemy(Enemy_t *i);

// <-- cdtor

int EnemyEachFrame(Enemy_t *i);
void DrawEnemy(Enemy_t *i);

// <-- accessor

Enemy_t *GetNearestEnemy(double x, double y);
