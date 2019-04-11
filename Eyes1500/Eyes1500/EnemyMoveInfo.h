typedef enum EnemyAttackPtn_et
{
	EAP_JIKINERAI,
	EAP_HOMING,
	EAP_BOMB,

	EAP_MAX, // num of EAP_*
}
EnemyAttackPtn_t;

typedef enum EnemyMovePtn_et
{
	EMP_HOLD,
	EMP_AHEAD,
	EMP_SPEEDx15,
	EMP_SPEEDx15_L,
	EMP_SPEEDx15_R,
	EMP_SPEEDx15_UL,
	EMP_SPEEDx15_UR,
	EMP_SPEEDx15_A,
	EMP_SPEEDx20,
	EMP_SPEEDx20_L,
	EMP_SPEEDx20_R,
	EMP_SPEEDx20_UL,
	EMP_SPEEDx20_UR,
	EMP_SPEEDx20_A,
	EMP_HARITSUKI,

	EMP_MAX, // num of EMP_*
}
EnemyMovePtn_t;

EnemyAttackPtn_t GetEnemyAttackPtn(EnemyKind_t kind, int level);
EnemyMovePtn_t GetEnemyMovePtn(EnemyKind_t kind, int level);
int GetEnemyRenshaCount(EnemyKind_t kind, int level);
