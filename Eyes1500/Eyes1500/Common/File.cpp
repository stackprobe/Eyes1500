/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

// ---- getFileList ----

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	unsigned attrib;
		_A_ARCH
		_A_HIDDEN
		_A_NORMAL
		_A_RDONLY
		_A_SUBDIR
		_A_SYSTEM

	time_t time_create;
	time_t time_access;
	time_t time_write;
	_fsize_t size;
	char name[_MAX_PATH];
*/
struct _finddata_t lastFindData;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	dir 直下のサブディレクトリ・ファイルのリストを返す。
	返すサブディレクトリ・ファイルは「ローカル名」なので注意！

	subDirs: NULL == 出力しない。
	files: NULL == 出力しない。
*/
void getFileList(char *dir, autoList<char *> *subDirs, autoList<char *> *files)
{
	errorCase(m_isEmpty(dir));

	char *wCard = xcout("%s\\*", dir);
	intptr_t h = _findfirst(wCard, &lastFindData);
	memFree(wCard);

	if(h != -1)
	{
		do
		{
			char *name = lastFindData.name;

			if(name[0] == '.' && (name[1] == '\0' || name[1] == '.' && name[2] == '\0')) // ".", ".." を除外
				continue;

			errorCase(m_isEmpty(name));
			errorCase(strchr(name, '?')); // ? 変な文字を含む

			if(lastFindData.attrib & _A_SUBDIR) // ? subDir
			{
				if(subDirs)
					subDirs->AddElement(strx(name));
			}
			else // ? file
			{
				if(files)
					files->AddElement(strx(name));
			}
		}
		while(_findnext(h, &lastFindData) == 0);

		_findclose(h);
	}
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000061 $$$$ //	void updateFindData(char *path)
// #### DELETED ==== 0000061 $$$$ //	{
// #### DELETED ==== 0000061 $$$$ //		errorCase(m_isEmpty(path));
// #### DELETED ==== 0000061 $$$$ //	
// #### DELETED ==== 0000061 $$$$ //		intptr_t h = _findfirst(path, &lastFindData);
// #### DELETED ==== 0000061 $$$$ //		errorCase(h == -1);
// #### DELETED ==== 0000061 $$$$ //		_findclose(h);
// #### DELETED ==== 0000061 $$$$ //	}

// ----

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *combine(char *path1, char *path2)
{
	char *path;

	if(path1[0] && path1[1] == ':' && path1[2] == '\0')
		path = xcout("%s.\\%s", path1, path2);
	else
		path = xcout("%s\\%s", path1, path2);

	replaceChar(path, '\\', '/');
	path = replacePtnLoop(path, "//", "/");
	replaceChar(path, '/', '\\');

	return path;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int Game_mkdir(char *dir) // ret: ? 失敗
{
	if(CreateDirectory(dir, NULL) == 0) // ? 失敗
	{
		if(accessible(dir))
			return 0;

		execute_x(xcout("MD \"%s\"", dir));

		if(!accessible(dir))
			return 1;
	}
	return 0;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int accessible(char *path)
{
	return !_access(path, 0);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *refLocalPath(char *path)
{
	char *p = mbs_strrchr(path, '\\');

	if(p)
		return p + 1;

	return path;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void createFile(char *file)
{
	fileClose(fileOpen(file, "wb"));
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void createDir(char *dir)
{
	errorCase(m_isEmpty(dir));
	errorCase(Game_mkdir(dir)); // ? 失敗
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void deleteFile(char *file)
{
	remove(file);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void deleteDir(char *dir)
{
	errorCase(m_isEmpty(dir));

	autoList<char *> *subDirs = new autoList<char *>();
	autoList<char *> *files = new autoList<char *>();

	getFileList(dir, subDirs, files);
	addCwd(dir);

	for(int index = 0; index < subDirs->GetCount(); index++)
		deleteDir(subDirs->GetElement(index));

	for(int index = 0; index < files->GetCount(); index++)
		deleteFile(files->GetElement(index));

	unaddCwd();
	_rmdir(dir);

	releaseList(subDirs, (void (*)(char *))memFree);
	releaseList(files, (void (*)(char *))memFree);
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static oneObject(autoList<char *>, new autoList<char *>(), GetCwdStack);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *getCwd(void)
{
	char *tmp = _getcwd(NULL, 0);

	errorCase(m_isEmpty(tmp));

	char *dir = strx(tmp);
	free(tmp);
	return dir;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void changeCwd(char *dir)
{
	errorCase(m_isEmpty(dir));
	errorCase(_chdir(dir)); // ? 失敗
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void addCwd(char *dir)
{
	GetCwdStack()->AddElement(getCwd());
	changeCwd(dir);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void unaddCwd(void)
{
	char *dir = GetCwdStack()->UnaddElement();

	changeCwd(dir);
	memFree(dir);
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define APP_TEMP_DIR_UUID "{8f8ce7a6-fea3-455c-8d7a-a6ebfd9b9944}" // shared_uuid@g -- このソースを使い回すので、global指定

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static char *GetSystemTempDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = getenv("TMP");

		if(m_isEmpty(dir))
		{
			dir = getenv("TEMP");
			errorCase(m_isEmpty(dir));
		}
	}
	return dir;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void DeleteAppTempDir(void)
{
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
LOGPOS(); // test
	deleteDir(getAppTempDir());
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *getAppTempDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = combine(GetSystemTempDir(), APP_TEMP_DIR_UUID);

		if(accessible(dir))
			deleteDir(dir);

		createDir(dir);
		GetFinalizers()->AddFunc(DeleteAppTempDir);
	}
	return dir;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static char *NextTempLocalName(void)
{
	static char name[32] = "zzz"; // 長さ適当、ここまで長くなることは無いだろう。また "prn" など使用出来ないので４文字から開始する。

	for(char *p = name; ; p++)
	{
		if(!*p)
		{
			*p = 'a';
			p[1] = '\0';
			break;
		}
		if(*p < 'z')
		{
			++*p;
			break;
		}
		*p = 'a';
	}
	return name;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *makeTempPath(char *ext) // ext: NULL ok
{
	char *path = combine(getAppTempDir(), NextTempLocalName());

	if(ext)
	{
		path = addChar(path, '.');
		path = addLine(path, ext);
	}
	return path;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000062 $$$$ //	char *makeTempFile(char *ext) // ext: NULL ok
// #### DELETED ==== 0000062 $$$$ //	{
// #### DELETED ==== 0000062 $$$$ //		char *file = makeTempPath(ext);
// #### DELETED ==== 0000062 $$$$ //		createFile(file);
// #### DELETED ==== 0000062 $$$$ //		return file;
// #### DELETED ==== 0000062 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *makeTempDir(char *ext) // ext: NULL ok
{
	char *dir = makeTempPath(ext);
	createDir(dir);
	return dir;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 getFileSizeFP(FILE *fp)
{
	errorCase(_fseeki64(fp, 0I64, SEEK_END) != 0); // ? 失敗

	__int64 size = _ftelli64(fp);

	errorCase(size < 0I64);
	return size;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 getFileSizeFPSS(FILE *fp)
{
	__int64 size = getFileSizeFP(fp);

	errorCase(_fseeki64(fp, 0I64, SEEK_SET) != 0); // ? 失敗
	return size;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000063 $$$$ //	__int64 getFileSize(char *file)
// #### DELETED ==== 0000063 $$$$ //	{
// #### DELETED ==== 0000063 $$$$ //		FILE *fp = fileOpen(file, "rb");
// #### DELETED ==== 0000063 $$$$ //	
// #### DELETED ==== 0000063 $$$$ //		__int64 size = getFileSizeFP(fp);
// #### DELETED ==== 0000063 $$$$ //	
// #### DELETED ==== 0000063 $$$$ //		fileClose(fp);
// #### DELETED ==== 0000063 $$$$ //		return size;
// #### DELETED ==== 0000063 $$$$ //	}
