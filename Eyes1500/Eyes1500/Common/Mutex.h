/*
 * copied the source file by CopyLib.exe
 *
 */
int mutexOpen(char *mutexName);
/*
 * copied the source file by CopyLib.exe
 *
 */
void mutexRelease(int h);

/*
 * copied the source file by CopyLib.exe
 *
 */
int eventOpen(char *eventName);
/*
 * copied the source file by CopyLib.exe
 *
 */
void eventSet(int h);

/*
 * copied the source file by CopyLib.exe
 *
 */
int waitForMillis(int h, int millis);
/*
 * copied the source file by CopyLib.exe
 *
 */
void waitForever(int h);
/*
 * copied the source file by CopyLib.exe
 *
 */
void handleClose(int h);
