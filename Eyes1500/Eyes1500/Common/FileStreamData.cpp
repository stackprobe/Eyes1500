/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
autoList<uchar> *readAllBytes(char *file)
{
	FILE *fp = fileOpen(file, "rb");
	int size;

	{
		__int64 size64 = getFileSizeFPSS(fp);
		errorCase((__int64)IMAX < size64); // ? ëÂÇ´Ç∑Ç¨ÇÈÅB
		size = (int)size64;
	}

	uchar *fileData = (uchar *)memAlloc_NC(size);

	if(size)
		errorCase(fread(fileData, 1, size, fp) != size); // ? read error

	fileClose(fp);
	return new autoList<uchar>(fileData, size);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000070 $$$$ //	autoList<uchar> *readAllBytes_x(char *file)
// #### DELETED ==== 0000070 $$$$ //	{
// #### DELETED ==== 0000070 $$$$ //		autoList<uchar> *out = readAllBytes(file);
// #### DELETED ==== 0000070 $$$$ //		memFree(file);
// #### DELETED ==== 0000070 $$$$ //		return out;
// #### DELETED ==== 0000070 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000071 $$$$ //	int readChar(autoList<uchar> *fileData, int &rIndex)
// #### DELETED ==== 0000071 $$$$ //	{
// #### DELETED ==== 0000071 $$$$ //		if(rIndex < fileData->GetCount())
// #### DELETED ==== 0000071 $$$$ //		{
// #### DELETED ==== 0000071 $$$$ //			return fileData->GetElement(rIndex++);
// #### DELETED ==== 0000071 $$$$ //		}
// #### DELETED ==== 0000071 $$$$ //		return EOF;
// #### DELETED ==== 0000071 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *readLine(autoList<uchar> *fileData, int &rIndex)
{
	autoList<char> *line = new autoList<char>();

	while(rIndex < fileData->GetCount())
	{
		int chr = fileData->GetElement(rIndex++);

		if(chr == '\r')
		{
			// ì«Ç›îÚÇŒÇ∑ÅB
		}
		else if(chr == '\n')
		{
			break;
		}
		else
		{
			line->AddElement(chr);
		}
	}
	if(line->GetCount() == 0 && rIndex == fileData->GetCount()) // ? ì«Ç›çûÇ›èIóπ
	{
		delete line;
		return NULL;
	}
	return unbindBlock2Line(line);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *neReadLine(autoList<uchar> *fileData, int &rIndex)
{
	char *line = readLine(fileData, rIndex);
	errorCase(!line);
	return line;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000072 $$$$ //	char *nnReadLine(autoList<uchar> *fileData, int &rIndex, char *defaultLine)
// #### DELETED ==== 0000072 $$$$ //	{
// #### DELETED ==== 0000072 $$$$ //		char *line = readLine(fileData, rIndex);
// #### DELETED ==== 0000072 $$$$ //	
// #### DELETED ==== 0000072 $$$$ //		if(!line)
// #### DELETED ==== 0000072 $$$$ //			line = strx(defaultLine);
// #### DELETED ==== 0000072 $$$$ //	
// #### DELETED ==== 0000072 $$$$ //		return line;
// #### DELETED ==== 0000072 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
autoList<char *> *readLines(autoList<uchar> *fileData)
{
	autoList<char *> *lines = new autoList<char *>();
	int rIndex = 0;

	for(; ; )
	{
		char *line = readLine(fileData, rIndex);

		if(!line)
			break;

		lines->AddElement(line);
	}
	return lines;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
autoList<char *> *readLines_x(autoList<uchar> *fileData)
{
	autoList<char *> *lines = readLines(fileData);
	delete fileData;
	return lines;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeAllBytes(char *file, autoList<uchar> *fileData)
{
	FILE *fp = fileOpen(file, "wb");

	errorCase(fwrite(fileData->ElementAt(0), 1, fileData->GetCount(), fp) != fileData->GetCount()); // ? write error

	fileClose(fp);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeAllBytes_cx(char *file, autoList<uchar> *fileData)
{
	writeAllBytes(file, fileData);
	delete fileData;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000073 $$$$ //	void writeChar(autoList<uchar> *fileData, int chr)
// #### DELETED ==== 0000073 $$$$ //	{
// #### DELETED ==== 0000073 $$$$ //		fileData->AddElement(chr);
// #### DELETED ==== 0000073 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeToken(autoList<uchar> *fileData, char *token)
{
	for(char *p = token; *p; p++)
	{
		fileData->AddElement(*p);
	}
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeLine(autoList<uchar> *fileData, char *line)
{
	writeToken(fileData, line);
	fileData->AddElement('\n');
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000074 $$$$ //	void writeLine_x(autoList<uchar> *fileData, char *line)
// #### DELETED ==== 0000074 $$$$ //	{
// #### DELETED ==== 0000074 $$$$ //		writeLine(fileData, line);
// #### DELETED ==== 0000074 $$$$ //		memFree(line);
// #### DELETED ==== 0000074 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
uint64 readUI64(autoList<uchar> *fileData, int &rIndex, int width)
{
	uint64 value = 0;

	for(int c = 0; c < width; c++)
	{
		value |= (uint64)fileData->GetElement(rIndex++) << c * 8;
	}
	return value;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000075 $$$$ //	uint readUI32(autoList<uchar> *fileData, int &rIndex, int width)
// #### DELETED ==== 0000075 $$$$ //	{
// #### DELETED ==== 0000075 $$$$ //		return (uint)readUI64(fileData, rIndex, width);
// #### DELETED ==== 0000075 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeUI64(autoList<uchar> *fileData, uint64 value, int width)
{
	for(int c = 0; c < width; c++)
	{
		fileData->AddElement((uchar)(value >> c * 8 & 0xff));
	}
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeUI32(autoList<uchar> *fileData, uint value, int width)
{
	writeUI64(fileData, (uint64)value, width);
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000076 $$$$ //	autoList<uchar> *readBlock(FILE *fp, int width)
// #### DELETED ==== 0000076 $$$$ //	{
// #### DELETED ==== 0000076 $$$$ //		autoList<uchar> *retBlock = new autoList<uchar>();
// #### DELETED ==== 0000076 $$$$ //	
// #### DELETED ==== 0000076 $$$$ //		for(int index = 0; index < width; index++)
// #### DELETED ==== 0000076 $$$$ //		{
// #### DELETED ==== 0000076 $$$$ //			retBlock->AddElement((uchar)readChar(fp));
// #### DELETED ==== 0000076 $$$$ //		}
// #### DELETED ==== 0000076 $$$$ //		return retBlock;
// #### DELETED ==== 0000076 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000077 $$$$ //	autoList<uchar> *readBlock(autoList<uchar> *fileData, int &rIndex, int width)
// #### DELETED ==== 0000077 $$$$ //	{
// #### DELETED ==== 0000077 $$$$ //		autoList<uchar> *retBlock = new autoList<uchar>();
// #### DELETED ==== 0000077 $$$$ //	
// #### DELETED ==== 0000077 $$$$ //		for(int index = 0; index < width; index++)
// #### DELETED ==== 0000077 $$$$ //		{
// #### DELETED ==== 0000077 $$$$ //			retBlock->AddElement(fileData->RefElement(rIndex++, 0x00));
// #### DELETED ==== 0000077 $$$$ //		}
// #### DELETED ==== 0000077 $$$$ //		return retBlock;
// #### DELETED ==== 0000077 $$$$ //	}
