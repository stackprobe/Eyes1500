/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
enum
{
	ETC_DATSTRINGS,
	ETC_JCHAR,

	// app >

	ETC_STAGE_INFO,
	ETC_ENEMY_INFO,
	ETC_ENEMY_SHOT_INFO,

	// < app

	ETC_MAX, // num of member
};

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
oneObjectProto(resCluster<autoList<uchar> *>, GetEtcRes);
