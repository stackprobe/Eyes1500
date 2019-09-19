#include "all.h"

static FILE *Game_rfopen(char *file, char *mode)
{
	FILE *fp;

	for(int c = 0; ; c++)
	{
		fp = fopen(file, mode);

		if(fp || 8 < c)
			break;

		LOGPOS();
		Sleep(100);
	}
	return fp;
}
FILE *fileOpen(char *file, char *mode)
{
	FILE *fp = Game_rfopen(file, mode);

	if(!fp) // ? ���s
	{
		{
			static int passed;

			if(passed)
				error();

			passed = 1;
		}

		LOG("[fileOpen] %s %s\n", file, mode);
		error();
	}
	return fp;
}
void fileClose(FILE *fp)
{
	errorCase(fclose(fp)); // ? ���s
}

int readChar(FILE *fp) // �o�C�i���E�e�L�X�g��킸�X�g���[������P�o�C�g(�P����)�ǂݍ��ށB
{
	int chr = fgetc(fp);

	if(chr == EOF && ferror(fp))
	{
		error();
	}
	return chr;
}
char *readLine(FILE *fp, int lenmax)
{
	autoList<char> *lineBuff = new autoList<char>(128);
	char *line;
	int chr;

	for(; ; )
	{
		chr = readChar(fp);

		if(chr == '\r')
		{
			if(readChar(fp) != '\n') // ? CR-(not_LF)
			{
				error();
			}
			break;
		}
		if(chr == '\n' || chr == EOF)
		{
			break;
		}
		if(lenmax <= lineBuff->GetCount())
		{
			break;
		}
		if(chr == '\0')
		{
			chr = '\1';
		}
		lineBuff->AddElement(chr);
	}
	line = unbindBlock2Line(lineBuff);

	if(line[0] == '\0' && chr == EOF)
	{
		memFree(line);
		line = NULL;
	}
	return line;
}
autoList<char *> *readLines(char *file)
{
	FILE *fp = fileOpen(file, "rt");
	autoList<char *> *lines = new autoList<char *>();

	for(; ; )
	{
		char *line = readLine(fp);

		if(!line)
			break;

		lines->AddElement(line);
	}
	fileClose(fp);
	return lines;
}

void writeChar(FILE *fp, int chr) // �o�C�i���E�e�L�X�g��킸�X�g���[���ɂP�o�C�g(�P����)�����o���B
{
	errorCase(fputc(chr, fp) == EOF);
}
void writeToken(FILE *fp, char *line)
{
	for(char *p = line; *p; p++)
		writeChar(fp, *p);
}
void writeLine(FILE *fp, char *line)
{
	writeToken(fp, line);
	writeChar(fp, '\n');
}

uint64 readUI64(FILE *fp, int width)
{
	uint64 value = 0;

	for(int c = 0; c < width; c++)
	{
		value |= (uint64)readChar(fp) << c * 8;
	}
	return value;
}
void writeUI64(FILE *fp, uint64 value, int width)
{
	for(int c = 0; c < width; c++)
	{
		writeChar(fp, (uchar)(value >> c * 8 & 0xff));
	}
}
