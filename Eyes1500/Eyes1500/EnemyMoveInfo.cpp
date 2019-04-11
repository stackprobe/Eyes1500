#include "all.h"

typedef struct EnemyMoveInfo_st
{
	EnemyAttackPtn_t AttackPtn;
	EnemyMovePtn_t MovePtn;
}
EnemyMoveInfo_t;

static EnemyMoveInfo_t EnemyMoveInfos[] =
{
	// EK_EYE_1
	{ EAP_JIKINERAI, EMP_AHEAD      },
	{ EAP_BOMB,      EMP_SPEEDx15_R },
	{ EAP_HOMING,    EMP_HARITSUKI  },

	// EK_EYE_2
	{ EAP_JIKINERAI, EMP_AHEAD      },
	{ EAP_BOMB,      EMP_SPEEDx15_L },
	{ EAP_HOMING,    EMP_SPEEDx20   },

	// EK_EYE_3
	{ EAP_JIKINERAI, EMP_AHEAD       },
	{ EAP_HOMING,    EMP_SPEEDx20    },
	{ EAP_BOMB,      EMP_SPEEDx15_UR },

	// EK_EYE_4
	{ EAP_JIKINERAI, EMP_AHEAD       },
	{ EAP_HOMING,    EMP_SPEEDx20    },
	{ EAP_BOMB,      EMP_SPEEDx15_UL },

	// EK_EYE_5
	{ EAP_JIKINERAI, EMP_AHEAD     },
	{ EAP_HOMING,    EMP_SPEEDx20  },
	{ EAP_BOMB,      EMP_HARITSUKI },

	// EK_EYE_6
	{ EAP_JIKINERAI, EMP_AHEAD      },
	{ EAP_HOMING,    EMP_SPEEDx15_A },
	{ EAP_BOMB,      EMP_SPEEDx20_R },

	// EK_EYE_7
	{ EAP_JIKINERAI, EMP_AHEAD      },
	{ EAP_HOMING,    EMP_SPEEDx15_A },
	{ EAP_BOMB,      EMP_SPEEDx20_L },

	// EK_EYE_8
	{ EAP_JIKINERAI, EMP_AHEAD      },
	{ EAP_BOMB,      EMP_SPEEDx15_R },
	{ EAP_BOMB,      EMP_SPEEDx20   },

	// EK_EYE_9
	{ EAP_JIKINERAI, EMP_HOLD       },
	{ EAP_BOMB,      EMP_SPEEDx15_L },
	{ EAP_BOMB,      EMP_SPEEDx20   },

	// EK_EYE_10
	{ EAP_JIKINERAI, EMP_AHEAD     },
	{ EAP_BOMB,      EMP_SPEEDx15  },
	{ EAP_HOMING,    EMP_HARITSUKI },

	// EK_EYE_20
	{ EAP_JIKINERAI, EMP_AHEAD    },
	{ EAP_BOMB,      EMP_SPEEDx15 },
	{ EAP_HOMING,    EMP_SPEEDx20 },

	// EK_EYE_50
	{ EAP_JIKINERAI, EMP_AHEAD },
	{ EAP_BOMB,      EMP_AHEAD },
	{ EAP_HOMING,    EMP_AHEAD },

	// EK_EYE_100
	{ EAP_JIKINERAI, EMP_AHEAD },
	{ EAP_BOMB,      EMP_AHEAD },
	{ EAP_HOMING,    EMP_AHEAD },
};

static EnemyMoveInfo_t *GetEnemyMoveInfo(EnemyKind_t kind, int level)
{
	errorCase(!m_isRange((int)kind, 0, EK_MAX - 1));
	errorCase(!m_isRange(level, 1, 3));

	int index = (int)kind * 3 + (level - 1);

	errorCase(!m_isRange(index, 0, lengthof(EnemyMoveInfos) - 1));

	return EnemyMoveInfos + index;
}
EnemyAttackPtn_t GetEnemyAttackPtn(EnemyKind_t kind, int level)
{
	return GetEnemyMoveInfo(kind, level)->AttackPtn;
}
EnemyMovePtn_t GetEnemyMovePtn(EnemyKind_t kind, int level)
{
	return GetEnemyMoveInfo(kind, level)->MovePtn;
}
int GetEnemyRenshaCount(EnemyKind_t kind, int level)
{
	return level;
}
