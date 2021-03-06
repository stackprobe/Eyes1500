enum
{
	SE_DUMMY,

	// app > @ SE_

	SE_BOMB,
	SE_BREAK,
	SE_DAMAGE,
	SE_DAMAGE_E,
	SE_DESTRUCT,
	SE_EXPLOSION_E,
	SE_LASER,
	SE_LASER_B,
	SE_MISSILE,
	SE_SHOT,
	SE_SIREN,
	SE_WARP,

	ENUM_RANGE(SE_VOICE_00, 8)

	// < app

	SE_MAX, // num of member
};

#define SE_HANDLE_MAX 64

typedef struct SEInfo_st
{
	int HandleList[SE_HANDLE_MAX];
	int HandleIndex;
	double Volume; // 0.0 - 1.0, def: 0.5
	int AlterCommand;
}
SEInfo_t;

int SEEachFrame(void);
void SEPlay(int seId);
void SEStop(int seId);
void SEPlayLoop(int seId);
void UpdateSEVolume(void);
