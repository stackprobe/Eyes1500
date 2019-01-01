enum
{
	ENUM_RANGE(D_DUMMY_00, 4)

	// app >

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

typedef struct DerInfo_st
{
	int ParentPicId;
	int X;
	int Y;
	int W;
	int H;
}
DerInfo_t;

int Der(resCluster<PicInfo_t *> *resclu, int derId);
int Der_W(int derId);
int Der_H(int derId);

void UnloadAllDer(autoList<int> *derHandleList);
