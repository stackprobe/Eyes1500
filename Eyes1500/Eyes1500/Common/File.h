//
// copied the source file by CopyLib.exe
//
extern struct _finddata_t lastFindData;

//
// copied the source file by CopyLib.exe
//
void getFileList(char *dir, autoList<char *> *subDirs, autoList<char *> *files);
//
// copied the source file by CopyLib.exe
//
void updateFindData(char *path);

// ----

//
// copied the source file by CopyLib.exe
//
int accessible(char *path);
//
// copied the source file by CopyLib.exe
//
char *refLocalPath(char *path);
//
// copied the source file by CopyLib.exe
//
void createDir(char *dir);
//
// copied the source file by CopyLib.exe
//
void deleteDir(char *dir);

//
// copied the source file by CopyLib.exe
//
char *getCwd(void);
//
// copied the source file by CopyLib.exe
//
void changeCwd(char *dir);
//
// copied the source file by CopyLib.exe
//
void addCwd(char *dir);
//
// copied the source file by CopyLib.exe
//
void unaddCwd(void);

//
// copied the source file by CopyLib.exe
//
char *getAppTempDir(void);
