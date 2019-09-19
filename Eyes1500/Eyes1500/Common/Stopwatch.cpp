/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	[Žg‚¢•û]

	SW_Start();

	SW_Lap();
	SW_Lap();
	SW_Lap();
	...

	SW_End();
*/

#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define TIMETABLE_MAX 5
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define LAPTIME_MAX 10000

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
typedef struct LapTime_st
{
	__int64 LapTime;
	char *Source;
	int LineNo;
	char *Function;
}
LapTime_t;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static LapTime_t TimeTable[TIMETABLE_MAX][LAPTIME_MAX];
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int LapIndex[TIMETABLE_MAX];
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int TimeIndex = -1;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000140 $$$$ //	void SW_Start2(void)
// #### DELETED ==== 0000140 $$$$ //	{
// #### DELETED ==== 0000140 $$$$ //		errorCase(TIMETABLE_MAX - 1 <= TimeIndex);
// #### DELETED ==== 0000140 $$$$ //	
// #### DELETED ==== 0000140 $$$$ //		TimeIndex++;
// #### DELETED ==== 0000140 $$$$ //		TimeTable[TimeIndex][0].LapTime = GetPerformanceCounter();
// #### DELETED ==== 0000140 $$$$ //		LapIndex[TimeIndex] = 0;
// #### DELETED ==== 0000140 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000141 $$$$ //	void SW_Lap2(char *source, int lineNo, char *function)
// #### DELETED ==== 0000141 $$$$ //	{
// #### DELETED ==== 0000141 $$$$ //		errorCase(TimeIndex < 0);
// #### DELETED ==== 0000141 $$$$ //		errorCase(LAPTIME_MAX - 1 <= LapIndex[TimeIndex]);
// #### DELETED ==== 0000141 $$$$ //	
// #### DELETED ==== 0000141 $$$$ //		__int64 currTime = GetPerformanceCounter();
// #### DELETED ==== 0000141 $$$$ //	
// #### DELETED ==== 0000141 $$$$ //		LapTime_t *lt = TimeTable[TimeIndex] + LapIndex[TimeIndex];
// #### DELETED ==== 0000141 $$$$ //	
// #### DELETED ==== 0000141 $$$$ //		lt->LapTime = currTime - lt->LapTime;
// #### DELETED ==== 0000141 $$$$ //		lt->Source = source;
// #### DELETED ==== 0000141 $$$$ //		lt->LineNo = lineNo;
// #### DELETED ==== 0000141 $$$$ //		lt->Function = function;
// #### DELETED ==== 0000141 $$$$ //	
// #### DELETED ==== 0000141 $$$$ //		LapIndex[TimeIndex]++;
// #### DELETED ==== 0000141 $$$$ //		TimeTable[TimeIndex][LapIndex[TimeIndex]].LapTime = currTime;
// #### DELETED ==== 0000141 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000142 $$$$ //	void SW_End2(char *source, int lineNo, char *function)
// #### DELETED ==== 0000142 $$$$ //	{
// #### DELETED ==== 0000142 $$$$ //		errorCase(TimeIndex < 0);
// #### DELETED ==== 0000142 $$$$ //	
// #### DELETED ==== 0000142 $$$$ //		LapTime_t *lt = TimeTable[TimeIndex] + LapIndex[TimeIndex];
// #### DELETED ==== 0000142 $$$$ //	
// #### DELETED ==== 0000142 $$$$ //		lt->LapTime = GetPerformanceCounter() - lt->LapTime;
// #### DELETED ==== 0000142 $$$$ //		lt->Source = source;
// #### DELETED ==== 0000142 $$$$ //		lt->LineNo = lineNo;
// #### DELETED ==== 0000142 $$$$ //		lt->Function = function;
// #### DELETED ==== 0000142 $$$$ //	
// #### DELETED ==== 0000142 $$$$ //		double freq = (double)GetPerformanceFrequency();
// #### DELETED ==== 0000142 $$$$ //	
// #### DELETED ==== 0000142 $$$$ //		for(int index = 0; index <= LapIndex[TimeIndex]; index++)
// #### DELETED ==== 0000142 $$$$ //		{
// #### DELETED ==== 0000142 $$$$ //			LapTime_t *lt = TimeTable[TimeIndex] + index;
// #### DELETED ==== 0000142 $$$$ //	
// #### DELETED ==== 0000142 $$$$ //			fprintf(GetLogFp(),
// #### DELETED ==== 0000142 $$$$ //				"[LAP.%d] %I64d %.6f @ %s %d %s\n"
// #### DELETED ==== 0000142 $$$$ //				,index
// #### DELETED ==== 0000142 $$$$ //				,lt->LapTime
// #### DELETED ==== 0000142 $$$$ //				,lt->LapTime / freq
// #### DELETED ==== 0000142 $$$$ //				,lt->Source
// #### DELETED ==== 0000142 $$$$ //				,lt->LineNo
// #### DELETED ==== 0000142 $$$$ //				,lt->Function
// #### DELETED ==== 0000142 $$$$ //				);
// #### DELETED ==== 0000142 $$$$ //		}
// #### DELETED ==== 0000142 $$$$ //		TimeIndex--;
// #### DELETED ==== 0000142 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000143 $$$$ //	__int64 GetPerformanceCounter(void)
// #### DELETED ==== 0000143 $$$$ //	{
// #### DELETED ==== 0000143 $$$$ //		LARGE_INTEGER i;
// #### DELETED ==== 0000143 $$$$ //	
// #### DELETED ==== 0000143 $$$$ //		errorCase(!QueryPerformanceCounter(&i)); // ? Ž¸”s
// #### DELETED ==== 0000143 $$$$ //		errorCase(i.QuadPart <= 0i64); // ? Ž¸”s
// #### DELETED ==== 0000143 $$$$ //	
// #### DELETED ==== 0000143 $$$$ //		return i.QuadPart;
// #### DELETED ==== 0000143 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000144 $$$$ //	__int64 GetPerformanceFrequency(void)
// #### DELETED ==== 0000144 $$$$ //	{
// #### DELETED ==== 0000144 $$$$ //		static __int64 freq;
// #### DELETED ==== 0000144 $$$$ //	
// #### DELETED ==== 0000144 $$$$ //		if(freq == 0i64)
// #### DELETED ==== 0000144 $$$$ //		{
// #### DELETED ==== 0000144 $$$$ //			LARGE_INTEGER i;
// #### DELETED ==== 0000144 $$$$ //	
// #### DELETED ==== 0000144 $$$$ //			errorCase(!QueryPerformanceFrequency(&i)); // ? Ž¸”s
// #### DELETED ==== 0000144 $$$$ //			errorCase(i.QuadPart <= 0i64); // ? Ž¸”s
// #### DELETED ==== 0000144 $$$$ //	
// #### DELETED ==== 0000144 $$$$ //			freq = i.QuadPart;
// #### DELETED ==== 0000144 $$$$ //		}
// #### DELETED ==== 0000144 $$$$ //		return freq;
// #### DELETED ==== 0000144 $$$$ //	}
