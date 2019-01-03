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

//
// copied the source file by CopyLib.exe
//
int mutexOpen(char *mutexName)
{
	HANDLE h = CreateMutexA(NULL, FALSE, mutexName);
	errorCase(h == NULL); // ? ���s
	return (int)h;
}
//
// copied the source file by CopyLib.exe
//
void mutexRelease(int h)
{
	errorCase(!ReleaseMutex((HANDLE)h)); // ? ���s
}

//
// copied the source file by CopyLib.exe
//
int eventOpen(char *eventName)
{
	HANDLE h = CreateEventA(NULL, FALSE, FALSE, eventName);
	errorCase(h == NULL); // ? ���s
	return (int)h;
}
//
// copied the source file by CopyLib.exe
//
void eventSet(int h)
{
	errorCase(!SetEvent((HANDLE)h)); // ? ���s
}

//
// copied the source file by CopyLib.exe
//
int waitForMillis(int h, int millis) // ret: ? ���b�N���� || �V�O�i���擾
{
	return WaitForSingleObject((HANDLE)h, millis) == WAIT_OBJECT_0;
}
//
// copied the source file by CopyLib.exe
//
void waitForever(int h)
{
	errorCase(!waitForMillis(h, INFINITE));
}
//
// copied the source file by CopyLib.exe
//
void handleClose(int h)
{
	errorCase(!CloseHandle((HANDLE)h)); // ? ���s
}
