#include "all.h"

static autoList<DerInfo_t *> *DerList;

static void AddDer(int parentPicId, int x, int y, int w, int h)
{
	DerInfo_t *i = nb_(DerInfo_t);

	i->ParentPicId = parentPicId;
	i->X = x;
	i->Y = y;
	i->W = w;
	i->H = h;

	DerList->AddElement(i);
}
static void AddAnimation(int parentPicId, int x, int y, int w, int h, int xNum, int yNum, int xStep = -1, int yStep = -1)
{
	if(xStep == -1) xStep = w;
	if(yStep == -1) yStep = h;

	for(int yc = 0; yc < yNum; yc++)
	for(int xc = 0; xc < xNum; xc++)
	{
		AddDer(parentPicId, x + xc * xStep, y + yc * yStep, w, h);
	}
}
static void CreateDerList(void)
{
	DerList = new autoList<DerInfo_t *>();

	AddAnimation(P_DUMMY, 0, 0, 25, 25, 2, 2); // D_DUMMY_00

	// app > @ AddDer

	AddAnimation(P_CG_END, 0, 0, 480, 128, 1, 7); // D_CG_END_00
	AddAnimation(P_CG_MESSAGE, 0, 0, 480, 128, 1, 2); // D_CG_MESSAGE_00
	AddAnimation(P_CHARA_PLAYER, 0, 0, 32, 32, 2, 3); // D_CHARA_PLAYER_00
	AddAnimation(P_WEAPON_SHOT, 0, 0, 4, 8, 4, 1); // D_WEAPON_SHOT_00
	AddAnimation(P_WEAPON_MISSILE, 0, 0, 8, 16, 4, 1); // D_WEAPON_MISSILE_00
	AddAnimation(P_WEAPON_LASER, 0, 0, 2, 600, 2, 1); // D_WEAPON_LASER_00
	AddAnimation(P_EYE_1, 0, 0, 32, 32, 2, 4); // D_EYE_1_00
	AddAnimation(P_EYE_2, 0, 0, 64, 32, 2, 4); // D_EYE_2_00
	AddAnimation(P_EYE_3, 0, 0, 64, 48, 2, 4); // D_EYE_3_00
	AddAnimation(P_EYE_4, 0, 0, 96, 32, 2, 4); // D_EYE_4_00
	AddAnimation(P_EYE_5, 0, 0, 96, 48, 2, 4); // D_EYE_5_00
	AddAnimation(P_EYE_6, 0, 0, 80, 80, 2, 4); // D_EYE_6_00
	AddAnimation(P_EYE_7, 0, 0, 96, 64, 2, 4); // D_EYE_7_00
	AddAnimation(P_EYE_8, 0, 0, 112, 64, 2, 4); // D_EYE_8_00
	AddAnimation(P_EYE_9, 0, 0,  96, 80, 2, 4); // D_EYE_9_00
	AddAnimation(P_EYE_10, 0, 0, 112, 80, 2, 4); // D_EYE_10_00
	AddAnimation(P_EYE_20, 0, 0, 128, 96, 2, 4); // D_EYE_20_00
	AddAnimation(P_EYE_50, 0, 0, 144, 192, 2, 4); // D_EYE_50_00
	AddAnimation(P_EYE_100, 0, 0, 288, 160, 2, 4); // D_EYE_100_00
	AddAnimation(P_ENEMY_SHOT, 0, 0, 8, 8, 4, 1); // D_ENEMY_SHOT_00
	
	// < app

	errorCase(DerList->GetCount() != D_MAX);
}
static autoList<DerInfo_t *> *GetDerList(void)
{
	if(!DerList)
		CreateDerList();

	return DerList;
}

static int LoadDer(PicInfo_t *parent, int x, int y, int w, int h)
{
	int der_h;

	// check rect {
	errorCase(x < 0 || IMAX < x);
	errorCase(y < 0 || IMAX < y);
	errorCase(w < 1 || IMAX - x < w);
	errorCase(h < 1 || IMAX - y < h);
	// }

	if(
		parent->W < x + w ||
		parent->H < y + h
		)
		// ? �͈͊O
	{
		m_range(w, 1, 50);
		m_range(h, 1, 50);

		der_h = DerivationGraph(0, 0, w, h, GetPicRes()->GetHandle(P_DUMMY)->Handle); // �_�~�[�摜
	}
	else
		der_h = DerivationGraph(x, y, w, h, parent->Handle);

	errorCase(der_h == -1); // ? ���s
	return der_h;
}
static void UnloadDer(int h)
{
	if(h == -1) // ? ���I�[�v��
		return;

	errorCase(DeleteGraph(h)); // ? ���s
}

int Der(int derId)
{
	return Der(derId, GetPicRes());
}
int Der(int derId, resCluster<PicInfo_t *> *resclu)
{
	errorCase(derId < 0 || D_MAX <= derId);

	int h = resclu->GetDerHandleList()->RefElement(derId, -1);

	if(h == -1)
	{
		DerInfo_t *i = GetDerList()->GetElement(derId);

		h = LoadDer(
			resclu->GetHandle(i->ParentPicId),
			i->X,
			i->Y,
			i->W,
			i->H
			);

		resclu->GetDerHandleList()->PutElement(derId, h, -1);
	}
	return h;
}
int Der_W(int derId)
{
	return GetDerList()->GetElement(derId)->W;
}
int Der_H(int derId)
{
	return GetDerList()->GetElement(derId)->H;
}

void UnloadAllDer(autoList<int> *derHandleList)
{
	for(int derId = 0; derId < derHandleList->GetCount(); derId++)
	{
		UnloadDer(derHandleList->GetElement(derId));
	}
	derHandleList->Clear();
}
