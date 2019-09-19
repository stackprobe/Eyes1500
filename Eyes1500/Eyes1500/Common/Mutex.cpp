/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	mutex
		int h = mutexOpen("ABC");
		waitForMillis(h, 1000);
		waitForever(h);
		mutexRelease(h);
		handleClose(h);

	event
		int h = eventOpen("ABC");
		eventSet(h);
		waitForMillis(h, 1000);
		waitForever(h);
		handleClose(h);
*/

#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int mutexOpen(char *mutexName)
{
	HANDLE h = CreateMutexA(NULL, FALSE, mutexName);
	errorCase(h == NULL); // ? é∏îs
	return (int)h;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void mutexRelease(int h)
{
	errorCase(!ReleaseMutex((HANDLE)h)); // ? é∏îs
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000113 $$$$ //	int eventOpen(char *eventName)
// #### DELETED ==== 0000113 $$$$ //	{
// #### DELETED ==== 0000113 $$$$ //		HANDLE h = CreateEventA(NULL, FALSE, FALSE, eventName);
// #### DELETED ==== 0000113 $$$$ //		errorCase(h == NULL); // ? é∏îs
// #### DELETED ==== 0000113 $$$$ //		return (int)h;
// #### DELETED ==== 0000113 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000114 $$$$ //	void eventSet(int h)
// #### DELETED ==== 0000114 $$$$ //	{
// #### DELETED ==== 0000114 $$$$ //		errorCase(!SetEvent((HANDLE)h)); // ? é∏îs
// #### DELETED ==== 0000114 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int waitForMillis(int h, int millis) // ret: ? ÉçÉbÉNê¨å˜ || ÉVÉOÉiÉãéÊìæ
{
	return WaitForSingleObject((HANDLE)h, millis) == WAIT_OBJECT_0;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000115 $$$$ //	void waitForever(int h)
// #### DELETED ==== 0000115 $$$$ //	{
// #### DELETED ==== 0000115 $$$$ //		errorCase(!waitForMillis(h, INFINITE));
// #### DELETED ==== 0000115 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void handleClose(int h)
{
	errorCase(!CloseHandle((HANDLE)h)); // ? é∏îs
}
