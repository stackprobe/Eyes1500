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

#define TIMETABLE_MAX 5
#define LAPTIME_MAX 10000

typedef struct LapTime_st
{
	__int64 LapTime;
	char *Source;
	int LineNo;
	char *Function;
}
LapTime_t;

static LapTime_t TimeTable[TIMETABLE_MAX][LAPTIME_MAX];
static int LapIndex[TIMETABLE_MAX];
static int TimeIndex = -1;
