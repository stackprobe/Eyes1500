/*
 * copied the source file by CopyLib.exe
 *
 */
enum
{
	SE_DUMMY,

	// app >

	SE_BOMB,
	SE_BREAK,
	SE_DAMAGE,
	SE_DAMAGE_E,
	SE_DESTRUCT,
	SE_EXPLOSION_E,
	SE_LASER,
	SE_LASER_B,
	SE_MISSILE,
	SE_SHOT,
	SE_SIREN,

	// < app

	SE_MAX, // num of member
};

#define SE_HANDLE_MAX 64

/*
 * copied the source file by CopyLib.exe
 *
 */
typedef struct SEInfo_st
{
	int HandleList[SE_HANDLE_MAX];
	int HandleIndex;
	double Volume; // 0.0 - 1.0, def: 0.5
	int AlterCommand;
}
/*
 * copied the source file by CopyLib.exe
 *
 */
SEInfo_t;

/*
 * copied the source file by CopyLib.exe
 *
 */
int SEEachFrame(void);
/*
 * copied the source file by CopyLib.exe
 *
 */
void SEPlay(int seId);
/*
 * copied the source file by CopyLib.exe
 *
 */
void SEStop(int seId);
/*
 * copied the source file by CopyLib.exe
 *
 */
void UpdateSEVolume(void);
