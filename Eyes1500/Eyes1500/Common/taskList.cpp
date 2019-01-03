#include "all.h"

/*
 * copied the source file by CopyLib.exe
 *
 */
int IsDeadTaskInfo(taskInfo_t *i)
{
	return i->Func == NULL;
}
