enum
{
	ETC_DATSTRINGS,
	ETC_JCHAR,

	// app > @ ETC_

	ETC_STAGE_INFO,
	ETC_ENEMY_INFO,
	ETC_ENEMY_SHOT_INFO,

	// < app

	ETC_MAX, // num of member
};

oneObjectProto(resCluster<autoList<uchar> *>, GetEtcRes);
