#include "all.h"

//
// copied the source file by CopyLib.exe
//
FILE *fileOpen(char *file, char *mode)
{
	errorCase(m_isEmpty(file));
#if LOG_ENABLED == 0
	errorCase(!_strnicmp(file, "C:\\tmp\\", 7)); // ? リリース版で C:\\tmp\\* を参照している。-> 何かおかしい。
	errorCase(!_strnicmp(file, "C:\\temp\\", 7)); // ? リリース版で C:\\temp\\* を参照している。-> 何かおかしい。
#endif

	FILE *fp = fopen(file, mode);

	if(!fp) // ? 失敗
	{
		{
			static int once;

			if(once)
				error();

			once = 1;
		}

		LOG("[fileOpen] %s %s\n", file, mode);
		error();
	}
	return fp;
}
//
// copied the source file by CopyLib.exe
//
void fileClose(FILE *fp)
{
	errorCase(fclose(fp)); // ? 失敗
}

//
// copied the source file by CopyLib.exe
//
static int GetFileSize(FILE *fp)
{
	errorCase(_fseeki64(fp, 0I64, SEEK_END)); // ? 失敗

	__int64 size = _ftelli64(fp);

	errorCase(size < 0i64 || (__int64)IMAX < size);
	errorCase(_fseeki64(fp, 0, SEEK_SET)); // ? 失敗

	return (int)size;
}
//
// copied the source file by CopyLib.exe
//
autoList<uchar> *readFile(char *file)
{
	FILE *fp = fileOpen(file, "rb");
	int size = GetFileSize(fp);
	uchar *fileData = (uchar *)memAlloc_NC(size);

	if(size)
	{
		errorCase(fread(fileData, 1, size, fp) != size); // ? read error
	}
	fileClose(fp);
	return new autoList<uchar>(fileData, size);
}
//
// copied the source file by CopyLib.exe
//
autoList<uchar> *readFile_x(char *file)
{
	autoList<uchar> *out = readFile(file);
	memFree(file);
	return out;
}
//
// copied the source file by CopyLib.exe
//
int readChar(autoList<uchar> *fileData, int &rIndex)
{
	if(rIndex < fileData->GetCount())
	{
		return fileData->GetElement(rIndex++);
	}
	return EOF;
}
//
// copied the source file by CopyLib.exe
//
char *readLine(autoList<uchar> *fileData, int &rIndex)
{
	autoList<char> *line = new autoList<char>();

	while(rIndex < fileData->GetCount())
	{
		int chr = fileData->GetElement(rIndex++);

		if(chr == '\r')
		{
			1; // 読み飛ばす。
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
	if(line->GetCount() == 0 && rIndex == fileData->GetCount()) // ? 読み込み終了
	{
		delete line;
		return NULL;
	}
	line->AddElement('\0');

	char *result = line->UnbindBuffer();
	delete line;
	return result;
}
//
// copied the source file by CopyLib.exe
//
char *neReadLine(autoList<uchar> *fileData, int &rIndex)
{
	char *line = readLine(fileData, rIndex);
	errorCase(!line);
	return line;
}
//
// copied the source file by CopyLib.exe
//
char *nnReadLine(autoList<uchar> *fileData, int &rIndex, char *defaultLine)
{
	char *line = readLine(fileData, rIndex);

	if(!line)
		line = strx(defaultLine);

	return line;
}
//
// copied the source file by CopyLib.exe
//
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
//
// copied the source file by CopyLib.exe
//
autoList<char *> *readLines_x(autoList<uchar> *fileData)
{
	autoList<char *> *lines = readLines(fileData);
	delete fileData;
	return lines;
}

//
// copied the source file by CopyLib.exe
//
void writeFile(char *file, autoList<uchar> *fileData)
{
	FILE *fp = fileOpen(file, "wb");

	errorCase(fwrite(fileData->ElementAt(0), 1, fileData->GetCount(), fp) != fileData->GetCount()); // ? write error

	fileClose(fp);
}
//
// copied the source file by CopyLib.exe
//
void writeFile_cx(char *file, autoList<uchar> *fileData)
{
	writeFile(file, fileData);
	delete fileData;
}
//
// copied the source file by CopyLib.exe
//
void writeToken(autoList<uchar> *fileData, char *token)
{
	for(char *p = token; *p; p++)
	{
		fileData->AddElement(*p);
	}
}
//
// copied the source file by CopyLib.exe
//
void writeLine(autoList<uchar> *fileData, char *line)
{
	writeToken(fileData, line);
	fileData->AddElement('\n');
}
//
// copied the source file by CopyLib.exe
//
void writeLine_x(autoList<uchar> *fileData, char *line)
{
	writeLine(fileData, line);
	memFree(line);
}

//
// copied the source file by CopyLib.exe
//
uint64 readUI64(autoList<uchar> *fileData, int &rIndex, int width)
{
	uint64 value = 0;

	for(int c = 0; c < width; c++)
	{
		value |= (uint64)fileData->GetElement(rIndex++) << c * 8;
	}
	return value;
}
//
// copied the source file by CopyLib.exe
//
uint readUI32(autoList<uchar> *fileData, int &rIndex, int width)
{
	return (uint)readUI64(fileData, rIndex, width);
}

//
// copied the source file by CopyLib.exe
//
void writeUI64(autoList<uchar> *fileData, uint64 value, int width)
{
	for(int c = 0; c < width; c++)
	{
		fileData->AddElement((uchar)(value >> c * 8 & 0xff));
	}
}
//
// copied the source file by CopyLib.exe
//
void writeUI32(autoList<uchar> *fileData, uint value, int width)
{
	writeUI64(fileData, (uint64)value, width);
}

//
// copied the source file by CopyLib.exe
//
autoList<uchar> *readBlock(autoList<uchar> *fileData, int &rIndex, int width)
{
	autoList<uchar> *retBlock = new autoList<uchar>();

	for(int index = 0; index < width; index++)
	{
		retBlock->AddElement(fileData->RefElement(rIndex++, 0x00));
	}
	return retBlock;
}
