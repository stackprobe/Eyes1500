/*
 * copied the source file by CopyLib.exe
 *
 */
typedef struct SubScreen_st
{
	int W;
	int H;
	int AFlag;
	int Handle;
}
/*
 * copied the source file by CopyLib.exe
 *
 */
SubScreen_t;

/*
 * copied the source file by CopyLib.exe
 *
 */
SubScreen_t *CreateSubScreen(int w, int h, int aFlag = 0);
/*
 * copied the source file by CopyLib.exe
 *
 */
void ReleaseSubScreen(SubScreen_t *i);

// <-- cdtor

/*
 * copied the source file by CopyLib.exe
 *
 */
int GetHandle(SubScreen_t *i);

// <-- accessor

/*
 * copied the source file by CopyLib.exe
 *
 */
extern int CurrDrawScreenHandle;

/*
 * copied the source file by CopyLib.exe
 *
 */
void ChangeDrawScreen(int handle);
/*
 * copied the source file by CopyLib.exe
 *
 */
void ChangeDrawScreen(SubScreen_t *screen);
/*
 * copied the source file by CopyLib.exe
 *
 */
void RestoreDrawScreen(void);

/*
 * copied the source file by CopyLib.exe
 *
 */
i2D_t GetSubScreenSize(SubScreen_t *screen);
/*
 * copied the source file by CopyLib.exe
 *
 */
i2D_t GetDrawScreenSize(void);
/*
 * copied the source file by CopyLib.exe
 *
 */
void UnloadAllSubScreenHandle(void);
