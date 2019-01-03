//
// copied the source file by CopyLib.exe
//
char *xcout(char *format, ...);
//
// copied the source file by CopyLib.exe
//
char *strrm(char *line, size_t extend);
//
// copied the source file by CopyLib.exe
//
char *strr(char *line);
//
// copied the source file by CopyLib.exe
//
char *strx(char *line);
//
// copied the source file by CopyLib.exe
//
void strz(char *&buffer, char *line);
//
// copied the source file by CopyLib.exe
//
void strz_x(char *&buffer, char *line);
//
// copied the source file by CopyLib.exe
//
int atoi_x(char *line);
__int64 atoi64_x(char *line);

#define isMbc(p) \
	(_ismbblead((p)[0]) && (p)[1])
//	(_ismbblead((p)[0]) && _ismbbtrail((p)[1]))

#define mbsNext(p) \
	(p + (isMbc(p) ? 2 : 1))

//
// copied the source file by CopyLib.exe
//
char *mbs_strrchr(char *str, int chr);

//
// copied the source file by CopyLib.exe
//
void replaceChar(char *str, int srcChr, int destChr);
//
// copied the source file by CopyLib.exe
//
char *replace(char *str, char *srcPtn, char *destPtn);
//
// copied the source file by CopyLib.exe
//
char *replaceLoop(char *str, char *srcPtn, char *destPtn, int max);

//
// copied the source file by CopyLib.exe
//
char *combine(char *path1, char *path2);

//
// copied the source file by CopyLib.exe
//
char *addLine(char *line, char *addPtn);
//
// copied the source file by CopyLib.exe
//
char *addChar(char *line, int chr);
//
// copied the source file by CopyLib.exe
//
char *insertLine(char *line, int index, char *insPtn);
//
// copied the source file by CopyLib.exe
//
char *insertChar(char *line, int index, int chr);
//
// copied the source file by CopyLib.exe
//
void reverseLine(char *line);
//
// copied the source file by CopyLib.exe
//
char *thousandComma(char *line);

//
// copied the source file by CopyLib.exe
//
void tokinit(char *str, char *delims);
//
// copied the source file by CopyLib.exe
//
char *toknext(char *str, char *delims);
//
// copied the source file by CopyLib.exe
//
char *ne_toknext(char *str, char *delims);
