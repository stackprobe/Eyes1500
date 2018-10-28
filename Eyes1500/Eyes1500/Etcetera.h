enum
{
	ETC_DATSTRINGS,
	ETC_JCHAR,

	// app >

	ETC_STAGEINFOS,
	ETC_ENEMYINFOS,
	ETC_ENEMYSHOTINFOS,

	// < app

	ETC_MAX, // num of member
};

oneObjectProto(resCluster<autoList<uchar> *>, GetEtcRes);
