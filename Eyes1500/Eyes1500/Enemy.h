typedef enum EnemyHaritsukiMode_et
{
	EHM_DISABLED = 1,   // 無効
	EHM_ENABLED,        // 有効
	EHM_ANTI_HARITSUKI, // 抑止
}
EnemyHaritsukiMode_t;

typedef struct Enemy_st
{
	EnemyKind_t Kind;
	double X;
	double Y;
	int Frame;
	int HP;
	int DamagedFrame; // 0 == 無効, 1 〜 ENEMY_DAMAGED_FRAME_MAX
	int ShootedFrame; // 最後に弾を撃ってからの経過フレーム
	int RenshaRemaining; // 連射であと何発打てるか
	EnemyHaritsukiMode_t HaritsukiMode;
}
Enemy_t;

Enemy_t *CreateEnemy(EnemyKind_t kind, double x, double y);
void ReleaseEnemy(Enemy_t *i);

// <-- cdtor

int EnemyEachFrame(Enemy_t *i);
void DrawEnemy(Enemy_t *i);

// <-- accessor

Enemy_t *GetNearestEnemy(double x, double y);

int GetEnemyPicId(int kind);
int GetEnemyDamagedPicId(int kind);
int GetEnemyDeadPicId(int kind);
double GetEnemy_W(int kind);
double GetEnemy_H(int kind);
double GetEnemyAtari_W(int kind);
double GetEnemyAtari_H(int kind);

#define GetEnemyAtari_L(enemy) ((enemy)->X - GetEnemyAtari_W((enemy)->Kind) / 2.0)
#define GetEnemyAtari_R(enemy) ((enemy)->X + GetEnemyAtari_W((enemy)->Kind) / 2.0)
#define GetEnemyAtari_T(enemy) ((enemy)->Y - GetEnemyAtari_H((enemy)->Kind) / 2.0)
#define GetEnemyAtari_B(enemy) ((enemy)->Y + GetEnemyAtari_H((enemy)->Kind) / 2.0)

void AllEnemy_AntiHaritsuki(void);
