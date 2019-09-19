/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void termination(int errorLevel)
{
	GetFinalizers()->Flush();
	exit(errorLevel);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
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

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define LOG_DIR "C:\\tmp"
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define LOG_FILE LOG_DIR "\\Game.log"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
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

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int ArgIndex = 1;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000149 $$$$ //	int hasArgs(int count)
// #### DELETED ==== 0000149 $$$$ //	{
// #### DELETED ==== 0000149 $$$$ //		return count <= __argc - ArgIndex;
// #### DELETED ==== 0000149 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
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
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *getArg(int index)
{
	errorCase(index < 0 || __argc - ArgIndex <= index);
	return __argv[ArgIndex + index];
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000150 $$$$ //	char *nextArg(void)
// #### DELETED ==== 0000150 $$$$ //	{
// #### DELETED ==== 0000150 $$$$ //		char *arg = getArg(0);
// #### DELETED ==== 0000150 $$$$ //		ArgIndex++;
// #### DELETED ==== 0000150 $$$$ //		return arg;
// #### DELETED ==== 0000150 $$$$ //	}

// < arg

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int IsWindowActive(void) // ret: ? このウィンドウはアクティブ
{
	return GetActiveFlag() ? 1 : 0;
}
#if 0 // test
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000151 $$$$ //	static int GetNowCount_TEST()
// #### DELETED ==== 0000151 $$$$ //	{
// #### DELETED ==== 0000151 $$$$ //		static int inited = 0;
// #### DELETED ==== 0000151 $$$$ //		static int startCount;
// #### DELETED ==== 0000151 $$$$ //		int currCount = GetNowCount();
// #### DELETED ==== 0000151 $$$$ //	
// #### DELETED ==== 0000151 $$$$ //		if(!inited)
// #### DELETED ==== 0000151 $$$$ //		{
// #### DELETED ==== 0000151 $$$$ //			startCount = GetNowCount();
// #### DELETED ==== 0000151 $$$$ //			inited = 1;
// #### DELETED ==== 0000151 $$$$ //		}
// #### DELETED ==== 0000151 $$$$ //		currCount -= startCount;
// #### DELETED ==== 0000151 $$$$ //		currCount -= 10000; // 要調整
// #### DELETED ==== 0000151 $$$$ //		return currCount;
// #### DELETED ==== 0000151 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define GetNowCount() GetNowCount_TEST()
#endif
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 GetCurrTime(void)
{
#if 0 // 精度がいまいち
	return (__int64)GetTickCount64();
#else
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
//	errorCase(lastTime != -1 && lastTime + 60000 < currTime); // ? 1分以上経過 <- 飛び過ぎ // タイトルバーを長時間掴んでいれば有り得る。

	lastTime = currTime;
	return currTime;
#endif
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void execute(char *command)
{
	system(command);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void execute_x(char *command)
{
	execute(command);
	memFree(command);
}
