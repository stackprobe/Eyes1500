//
// copied the source file by CopyLib.exe
//
void termination(int errorLevel = 0);

#define errorCase(status) \
	do { \
	if((status)) { \
		error(); \
	} \
	} while(0)

#define error() \
	error2(__FILE__, __LINE__, __FUNCTION__)

//
// copied the source file by CopyLib.exe
//
void error2(char *file, int lineno, char *function);

//
// copied the source file by CopyLib.exe
//
FILE *GetLogFp(void);

#if LOG_ENABLED
#define LOG(format, ...) (fprintf(GetLogFp(), format, ## __VA_ARGS__), fflush(GetLogFp()))
#else
#define LOG(format, ...) 1
#endif

#define LOGPOS() \
	LOG("[POS] %s %d %s\n", __FILE__, __LINE__, __FUNCTION__)

//
// copied the source file by CopyLib.exe
//
int hasArgs(int count);
//
// copied the source file by CopyLib.exe
//
int argIs(char *spell);
//
// copied the source file by CopyLib.exe
//
char *getArg(int index);
//
// copied the source file by CopyLib.exe
//
char *nextArg(void);

//
// copied the source file by CopyLib.exe
//
int IsWindowActive(void);
__int64 GetCurrTime(void);
