//#define APP_COMMON_FONT "メイリオ"
//#define APP_COMMON_FONT "ＭＳ ゴシック"
#define APP_COMMON_FONT "MS UI Gothic"

#define APP_COMMON_FONT_HANDLE (GetFontHandle(APP_COMMON_FONT, 18, 6))

typedef enum EnemyKind_et
{
	EK_EYE_1 = 1,
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
}
EnemyKind_t;

#define ENEMY_DAMAGED_FRAME_MAX 10
