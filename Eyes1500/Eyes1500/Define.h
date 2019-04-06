//#define APP_COMMON_FONT "ÉÅÉCÉäÉI"
//#define APP_COMMON_FONT "ÇlÇr ÉSÉVÉbÉN"
#define APP_COMMON_FONT "MS UI Gothic"

#define APP_COMMON_FONT_HANDLE (GetFontHandle(APP_COMMON_FONT, 18, 6))

typedef enum EnemyKind_et
{
	EK_EYE_1,
	EK_EYE_2,
	EK_EYE_3,
	EK_EYE_4,
	EK_EYE_5,
	EK_EYE_6,
	EK_EYE_7,
	EK_EYE_8,
	EK_EYE_9,
	EK_EYE_10,
	EK_EYE_20,
	EK_EYE_50,
	EK_EYE_100,

	EK_MAX, // num of EK_*
}
EnemyKind_t;

#define ENEMY_DAMAGED_FRAME_MAX 10
#define PLAYER_HP_MAX 3

enum
{
	END_NORMAL,
	END_SENMETSU,
	END_KANPEKI,
	END_AKAJI,
	END_ZENCLEAR,
	END_KAMICLEAR,
	END_JIBAKU,

	END_MAX, // num of END_*
};

//#define BATTLE_STARTABLE_FRAME 30
#define BATTLE_START_FRAME (3 * 60)

#define PLAYER_CRASH_R 15.0 // é©ã@ìñÇËîºåa
#define PLAYER_SHOT_CRASH_R 1.0
#define PLAYER_MISSILE_CRASH_R 1.0

#define DEFICIT_SEC_MAX 20
#define DEFICIT_FRAME_MAX ((DEFICIT_SEC_MAX + 1) * 60 - 1) // 20 Å` 0 ÇÃ 21 ïbä‘

#define ENEMY_MOVE_SPEED_CONV(rawSpeedVal) ((SCREEN_H / 60.0) / (rawSpeedVal))
#define ENEMY_TAMA_SPEED_CONV(rawSpeedVal) ((SCREEN_H / 60.0) / (rawSpeedVal))
