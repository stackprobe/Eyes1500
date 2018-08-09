#include "all.h"

// Conf_* >

/*
	-1 == �f�t�H���g
	0  == �ŏ��̃��j�^
	1  == 2�Ԗڂ̃��j�^
	2  == 3�Ԗڂ̃��j�^
	...
*/
int Conf_DisplayIndex = 1;

// < Conf_*

void ImportConfig(void)
{
	char *confFile = "Config.conf";

	if(accessible(confFile))
	{
		autoList<uchar> *fileData = readFile(confFile);
		int rIndex = 0;

		// Conf_* >

		Conf_DisplayIndex = atoi_x(neReadCfgLine(fileData, rIndex));

		// < Conf_*

		{
			char *line = neReadCfgLine(fileData, rIndex);

			errorCase(strcmp(line, "\\e"));
			memFree(line);
		}
	}
}
char *neReadCfgLine(autoList<uchar> *fileData, int &rIndex)
{
	for(; ; )
	{
		char *line = neReadLine(fileData, rIndex);

		if(*line && *line != ';')
			return line;

		memFree(line);
	}
}
