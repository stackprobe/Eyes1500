#include "all.h"

//
// copied the source file by CopyLib.exe
//
void termination(int errorLevel)
{
	GetFinalizers()->Flush();
	exit(errorLevel);
}
//
// copied the source file by CopyLib.exe
//
void error2(char *file, int lineno, char *function)
{
	{
		static int called;

		if(called)
			exit(2);

		called = 1;
	}

	LOG("[ERROR] %s %d %s\n", file, lineno, function);

	if(DxLibInited)
	{
		printfDx("Sorry! An error has occurred @ %s %d %s\n", refLocalPath(file), lineno, function);

		while((IgnoreEscapeKey || CheckHitKey(KEY_INPUT_ESCAPE) == 0) && ProcessMessage() != -1)
		{
			ScreenFlip();
		}
	}
	else
	{
		MessageBox(
			NULL,
			xcout("Sorry, An error has occurred @ %s %d %s", refLocalPath(file) ,lineno, function),
			"Error",
			MB_OK | MB_ICONSTOP | MB_TOPMOST
			);
	}
	termination(1);
}

#define LOG_DIR "C:\\tmp"
#define LOG_FILE LOG_DIR "\\Game.log"

//
// copied the source file by CopyLib.exe
//
FILE *GetLogFp(void)
{
	static FILE *fp;

	if(!fp)
	{
		if(!accessible(LOG_DIR))
			createDir(LOG_DIR);

		fp = fileOpen(LOG_FILE, "wt");
	}
	return fp;
}

// arg >

//
// copied the source file by CopyLib.exe
//
static int ArgIndex = 1;

//
// copied the source file by CopyLib.exe
//
int hasArgs(int count)
{
	return count <= __argc - ArgIndex;
}
//
// copied the source file by CopyLib.exe
//
int argIs(char *spell)
{
	if(ArgIndex < __argc)
	{
		if(!_stricmp(__argv[ArgIndex], spell))
		{
			ArgIndex++;
			return 1;
		}
	}
	return 0;
}
//
// copied the source file by CopyLib.exe
//
char *getArg(int index)
{
	errorCase(index < 0 || __argc - ArgIndex <= index);
	return __argv[ArgIndex + index];
}
//
// copied the source file by CopyLib.exe
//
char *nextArg(void)
{
	char *arg = getArg(0);
	ArgIndex++;
	return arg;
}

// < arg

//
// copied the source file by CopyLib.exe
//
int IsWindowActive(void) // ret: ? このウィンドウはアクティブ
{
	return GetActiveFlag() ? 1 : 0;
}
__int64 GetCurrTime(void)
{
	static __int64 lastTime = -1;
	static __int64 baseTime;
	static uint lastCount;
	uint currCount = (uint)GetNowCount();

	if(currCount < lastCount) // ? GetNowCount()のカンスト(オーバーフロー)
	{
		baseTime += (__int64)_UI32_MAX + 1;
	}
	lastCount = currCount;
	__int64 currTime = baseTime + currCount;

	errorCase(currTime < 0); // ? __int64のカンスト(オーバーフロー)
	errorCase(currTime < lastTime); // ? 時間が戻った || カンスト(オーバーフロー)
	errorCase(lastTime != -1 && lastTime + 60000 < currTime); // ? 1分以上経過 <- 飛び過ぎ

	lastTime = currTime;
	return currTime;
}
