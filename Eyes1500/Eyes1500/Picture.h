enum
{
	P_DUMMY,
	P_WHITEBOX,
	P_WHITECIRCLE,

	// app >

	P_CG_CONTROLLER,
	P_CG_CREDIT,
	P_CG_END,
	P_CG_FRAME,
	P_CG_MESSAGE,
	P_CG_ORDER,
	P_CG_PAUSE,
	P_CG_SCORE,
	P_CG_SCREEN,
	P_CG_STAGE,
	P_CG_START,

	P_CHARA_ENEMY1,
	P_CHARA_ENEMY10,
	P_CHARA_ENEMY100,
	P_CHARA_ENEMY2,
	P_CHARA_ENEMY20,
	P_CHARA_ENEMY3,
	P_CHARA_ENEMY4,
	P_CHARA_ENEMY5,
	P_CHARA_ENEMY50,
	P_CHARA_ENEMY6,
	P_CHARA_ENEMY7,
	P_CHARA_ENEMY8,
	P_CHARA_ENEMY9,
	P_CHARA_PLAYER,

	P_ENEMY_BOMB,
	P_ENEMY_SHOT,
	P_WEAPON_LASER,
	P_WEAPON_LASER_B,
	P_WEAPON_MISSILE,
	P_WEAPON_SHOT,

	// < app

	P_MAX, // num of member
};

typedef struct PicInfo_st
{
	int Handle;
	int W;
	int H;
}
PicInfo_t;

// Pic_ >

int Pic_FileData2SoftImage(autoList<uchar> *fileData);
int Pic_SoftImage2GraphicHandle(int si_h);
PicInfo_t *Pic_GraphicHandle2PicInfo(int handle);
void Pic_ReleasePicInfo(PicInfo_t *i);

void Pic_GetSoftImageSize(int si_h, int &w, int &h);
void Pic_GetGraphicHandleSize(int handle, int &w, int &h);

extern int SI_R;
extern int SI_G;
extern int SI_B;
extern int SI_A;

void Pic_GetSIPixel(int si_h, int x, int y);
void Pic_SetSIPixel(int si_h, int x, int y);

int Pic_CreateSoftImage(int w, int h);
void Pic_ReleaseSoftImage(int si_h);
void Pic_ReleaseGraphicHandle(int handle);

// < Pic_

resCluster<PicInfo_t *> *CreatePicRes(PicInfo_t *(*picLoader)(autoList<uchar> *), void (*picUnloader)(PicInfo_t *));
void UnloadAllPicResHandle(void);

void SetPicRes(resCluster<PicInfo_t *> *resclu);
resCluster<PicInfo_t *> *GetPicRes(void);
void ResetPicRes(void);

#define DTP 0x40000000

int Pic(int picId);
int Pic_W(int picId);
int Pic_H(int picId);
