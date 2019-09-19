#include "all.h"

void termination(int errorLevel)
{
	GetFinalizers()->Flush();
	exit(errorLevel);
}
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

static int ArgIndex = 1;

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
char *getArg(int index)
{
	errorCase(index < 0 || __argc - ArgIndex <= index);
	return __argv[ArgIndex + index];
}

// < arg

int IsWindowActive(void) // ret: ? ���̃E�B���h�E�̓A�N�e�B�u
{
	return GetActiveFlag() ? 1 : 0;
}
#if 0 // test
#define GetNowCount() GetNowCount_TEST()
#endif
__int64 GetCurrTime(void)
{
#if 0 // ���x�����܂���
	return (__int64)GetTickCount64();
#else
	static __int64 lastTime = -1;
	static __int64 baseTime;
	static uint lastCount;
	uint currCount = (uint)GetNowCount();

	if(currCount < lastCount) // ? GetNowCount()�̃J���X�g(�I�[�o�[�t���[)
	{
		baseTime += (__int64)_UI32_MAX + 1;
	}
	lastCount = currCount;
	__int64 currTime = baseTime + currCount;

	errorCase(currTime < 0); // ? __int64�̃J���X�g(�I�[�o�[�t���[)
	errorCase(currTime < lastTime); // ? ���Ԃ��߂��� || �J���X�g(�I�[�o�[�t���[)
//	errorCase(lastTime != -1 && lastTime + 60000 < currTime); // ? 1���ȏ�o�� <- ��щ߂� // �^�C�g���o�[�𒷎��Ԓ͂�ł���ΗL�蓾��B

	lastTime = currTime;
	return currTime;
#endif
}

void execute(char *command)
{
	system(command);
}
void execute_x(char *command)
{
	execute(command);
	memFree(command);
}
