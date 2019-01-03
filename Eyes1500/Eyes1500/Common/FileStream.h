/*
 * copied the source file by CopyLib.exe
 *
 */
FILE *fileOpen(char *file, char *mode);
/*
 * copied the source file by CopyLib.exe
 *
 */
void fileClose(FILE *fp);

/*
 * copied the source file by CopyLib.exe
 *
 */
autoList<uchar> *readFile(char *file);
/*
 * copied the source file by CopyLib.exe
 *
 */
autoList<uchar> *readFile_x(char *file);
/*
 * copied the source file by CopyLib.exe
 *
 */
int readChar(autoList<uchar> *fileData, int &rIndex);
/*
 * copied the source file by CopyLib.exe
 *
 */
char *readLine(autoList<uchar> *fileData, int &rIndex);
/*
 * copied the source file by CopyLib.exe
 *
 */
char *neReadLine(autoList<uchar> *fileData, int &rIndex);
/*
 * copied the source file by CopyLib.exe
 *
 */
char *nnReadLine(autoList<uchar> *fileData, int &rIndex, char *defaultLine = "");
/*
 * copied the source file by CopyLib.exe
 *
 */
autoList<char *> *readLines(autoList<uchar> *fileData);
/*
 * copied the source file by CopyLib.exe
 *
 */
autoList<char *> *readLines_x(autoList<uchar> *fileData);

/*
 * copied the source file by CopyLib.exe
 *
 */
void writeFile(char *file, autoList<uchar> *fileData);
/*
 * copied the source file by CopyLib.exe
 *
 */
void writeFile_cx(char *file, autoList<uchar> *fileData);
/*
 * copied the source file by CopyLib.exe
 *
 */
void writeToken(autoList<uchar> *fileData, char *token);
/*
 * copied the source file by CopyLib.exe
 *
 */
void writeLine(autoList<uchar> *fileData, char *line);
/*
 * copied the source file by CopyLib.exe
 *
 */
void writeLine_x(autoList<uchar> *fileData, char *line);

/*
 * copied the source file by CopyLib.exe
 *
 */
uint64 readUI64(autoList<uchar> *fileData, int &rIndex, int width = 8);
/*
 * copied the source file by CopyLib.exe
 *
 */
uint readUI32(autoList<uchar> *fileData, int &rIndex, int width = 4);

/*
 * copied the source file by CopyLib.exe
 *
 */
void writeUI64(autoList<uchar> *fileData, uint64 value, int width = 8);
/*
 * copied the source file by CopyLib.exe
 *
 */
void writeUI32(autoList<uchar> *fileData, uint value, int width = 4);

/*
 * copied the source file by CopyLib.exe
 *
 */
autoList<uchar> *readBlock(autoList<uchar> *fileData, int &rIndex, int width);
