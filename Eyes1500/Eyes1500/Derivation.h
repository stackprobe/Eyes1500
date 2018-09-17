enum
{
	ENUM_RANGE(D_DUMMY_00, 4)

	// app >

	ENUM_RANGE(D_CG_MESSAGE_00, 2)
	ENUM_RANGE(D_CHARA_PLAYER_00, 6)
	ENUM_RANGE(D_WEAPON_SHOT_00, 4)
	ENUM_RANGE(D_WEAPON_MISSILE_00, 4)
	ENUM_RANGE(D_WEAPON_LASER_00, 2)

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
