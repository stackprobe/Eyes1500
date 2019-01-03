#include "all.h"

/*
 * copied the source file by CopyLib.exe
 *
 */
static autoList<uchar> *LoadFileData(autoList<uchar> *fileData)
{
	return fileData->Ecdysis();
}
/*
 * copied the source file by CopyLib.exe
 *
 */
static void UnloadFileData(autoList<uchar> *fileData)
{
	delete fileData;
}

/*
 * copied the source file by CopyLib.exe
 *
 */
oneObject(
	resCluster<autoList<uchar> *>,
	new resCluster<autoList<uchar> *>("Etcetera.dat", "..\\..\\Etcetera.txt", ETC_MAX, 140000000, LoadFileData, UnloadFileData),
	GetEtcRes
	);
