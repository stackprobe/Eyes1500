/*
 * copied the source file by CopyLib.exe
 *
 */
extern int SmplMenu_Color;
/*
 * copied the source file by CopyLib.exe
 *
 */
extern int SmplMenu_BorderColor;
/*
 * copied the source file by CopyLib.exe
 *
 */
extern int SmplMenu_WallPicId;
/*
 * copied the source file by CopyLib.exe
 *
 */
extern double SmplMenu_WallCurtain;
/*
 * copied the source file by CopyLib.exe
 *
 */
extern int SmplMenu_X;
/*
 * copied the source file by CopyLib.exe
 *
 */
extern int SmplMenu_Y;
/*
 * copied the source file by CopyLib.exe
 *
 */
extern int SmplMenu_YStep;

/*
 * copied the source file by CopyLib.exe
 *
 */
int SmplMenu(char *menuTitle, char **menuItems, int selectMax, int selectIndex = 0);
/*
 * copied the source file by CopyLib.exe
 *
 */
double SmplVolumeConfig(char *menuTitle, double rate, int minval, int maxval, int valStep, int valFastStep, void (*valChanged)(double), void (*pulse)(void) = NULL);
/*
 * copied the source file by CopyLib.exe
 *
 */
void SmplPadConfig(void);
/*
 * copied the source file by CopyLib.exe
 *
 */
void SmplWindowSizeConfig(void);
