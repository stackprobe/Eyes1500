typedef struct EnemyTamaBlast_st
{
	int Frame;
	int X;
	int Y;
}
EnemyTamaBlast_t;

EnemyTamaBlast_t *CreateEnemyTamaBlast(int x, int y);
void ReleaseEnemyTamaBlast(EnemyTamaBlast_t *i);

// <-- cdtor

int EnemyTamaBlastEachFrame(EnemyTamaBlast_t *i);
void DrawEnemyTamaBlast(EnemyTamaBlast_t *i);

// <-- accessor
