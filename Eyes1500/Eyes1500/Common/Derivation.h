/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
enum
{
	ENUM_RANGE(D_DUMMY_00, 4)

	// app > @ D_

	ENUM_RANGE(D_CG_END_00, 7)
	ENUM_RANGE(D_CG_MESSAGE_00, 2)
	ENUM_RANGE(D_CHARA_PLAYER_00, 6)
	ENUM_RANGE(D_WEAPON_SHOT_00, 4)
	ENUM_RANGE(D_WEAPON_MISSILE_00, 4)
	ENUM_RANGE(D_WEAPON_LASER_00, 2)
	ENUM_RANGE(D_EYE_1_00, 8)
	ENUM_RANGE(D_EYE_2_00, 8)
	ENUM_RANGE(D_EYE_3_00, 8)
	ENUM_RANGE(D_EYE_4_00, 8)
	ENUM_RANGE(D_EYE_5_00, 8)
	ENUM_RANGE(D_EYE_6_00, 8)
	ENUM_RANGE(D_EYE_7_00, 8)
	ENUM_RANGE(D_EYE_8_00, 8)
	ENUM_RANGE(D_EYE_9_00, 8)
	ENUM_RANGE(D_EYE_10_00, 8)
	ENUM_RANGE(D_EYE_20_00, 8)
	ENUM_RANGE(D_EYE_50_00, 8)
	ENUM_RANGE(D_EYE_100_00, 8)
	ENUM_RANGE(D_ENEMY_SHOT_00, 4)

	// < app

	D_MAX, // num of member
};

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
typedef struct DerInfo_st
{
	int ParentPicId;
	int X;
	int Y;
	int W;
	int H;
}
DerInfo_t;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int Der(int derId);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int Der(int derId, resCluster<PicInfo_t *> *resclu);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int Der_W(int derId);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int Der_H(int derId);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void UnloadAllDer(autoList<int> *derHandleList);
