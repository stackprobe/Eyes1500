#include "all.h"

Enemy_t *CreateEnemy(EnemyKind_t kind, double x, double y)
{
	Enemy_t *i = nb(Enemy_t);

	i->Kind = kind;
	i->X = x;
	i->Y = y;
	i->HP = GetEnemyInfo(kind)->HP;
	i->HaritsukiMode = EHM_DISABLED;

	if(GDcNV.GameLapCount == 2)
		i->HP *= 2;

	return i;
}
void ReleaseEnemy(Enemy_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

static void CommonMove(Enemy_t *i, double xSpeedRate, double ySpeedRate)
{
	double speed = ENEMY_MOVE_SPEED_CONV(GetEnemyInfo(i->Kind)->MoveSpeed);

	i->X += speed * xSpeedRate;
	i->Y += speed * ySpeedRate;

	m_range(i->X, 0.0, SCREEN_W);
}
static void CommonApproach(Enemy_t *i, double targetX, double targetY, double speedRate)
{
	double speed = ENEMY_MOVE_SPEED_CONV(GetEnemyInfo(i->Kind)->MoveSpeed);

	double moveX;
	double moveY;

	MakeXYSpeed(i->X, i->Y, targetX, targetY, speed * speedRate, moveX, moveY);

	i->X += moveX;
	i->Y += moveY;
}
int EnemyEachFrame(Enemy_t *i) // ret: ? Á–Å
{
	int frm = i->Frame++; // frm == 0`

	double plDist = GetDistance(GDc.Player.X, GDc.Player.Y, i->X, i->Y);
	int level;

	if((plDist < ENEMY_HARITSUKI_R || i->HaritsukiMode == EHM_ENABLED) && i->HaritsukiMode != EHM_ANTI_HARITSUKI)
	{
		level = 3;
	}
	else if(plDist < 176.0)
	{
		level = 2;
	}
	else
	{
		level = 1;

		if(i->HaritsukiMode == EHM_ANTI_HARITSUKI)
			i->HaritsukiMode = EHM_DISABLED;
	}

	if(i->DamagedFrame == 0 && GDc.FlashFrame == 0)
	{
		EnemyMovePtn_t emp = GetEnemyMovePtn(i->Kind, level);

		switch(emp)
		{
		case EMP_HOLD:        CommonMove(i,  0.0, 0.0); break;
		case EMP_AHEAD:       CommonMove(i,  0.0, 1.0); break;
		case EMP_SPEEDx15:    CommonMove(i,  0.0, 1.5); break;
		case EMP_SPEEDx15_L:  CommonMove(i, -1.0, 1.5); break;
		case EMP_SPEEDx15_R:  CommonMove(i,  1.0, 1.5); break;
		case EMP_SPEEDx15_UL: CommonApproach(i, 0.0, 0.0, 1.5); break;
		case EMP_SPEEDx15_UR: CommonApproach(i, 0.0, SCREEN_W, 1.5); break;
		case EMP_SPEEDx15_A:  CommonApproach(i, GDc.Player.X, GDc.Player.Y, 1.5); break;
		case EMP_SPEEDx20:    CommonMove(i,  0.0, 2.0); break;
		case EMP_SPEEDx20_L:  CommonMove(i,  0.0, 2.0); break;
		case EMP_SPEEDx20_R:  CommonMove(i,  0.0, 2.0); break;
		case EMP_SPEEDx20_UL: CommonApproach(i, 0.0, 0.0, 2.0); break;
		case EMP_SPEEDx20_UR: CommonApproach(i, 0.0, SCREEN_W, 2.0); break;
		case EMP_SPEEDx20_A:  CommonApproach(i, GDc.Player.X, GDc.Player.Y, 2.0); break;

		case EMP_HARITSUKI:
			{
				double d = GetDistance(GDc.Player.X, GDc.Player.Y, i->X, i->Y);

				m_approach(d, ENEMY_HARITSUKI_R, 0.9);

				double relX;
				double relY;

				MakeXYSpeed(GDc.Player.X, GDc.Player.Y, i->X, i->Y, d, relX, relY);

				i->X = GDc.Player.X + relX;
				i->Y = GDc.Player.Y + relY;
			}

			if(i->HaritsukiMode != EHM_ENABLED)
			{
				AllEnemy_AntiHaritsuki();
				i->HaritsukiMode = EHM_ENABLED;
			}
			break;

		default:
			error();
		}
	}

	if(GDc.Player.DamagedFrame == 0 && GDc.Player.DeadFrame == 0)
	{
		EnemyAttackPtn_t eap = GetEnemyAttackPtn(i->Kind, level);
		int renshaCount = GetEnemyRenshaCount(i->Kind, level);
		int shoot = 0;

		if(1 <= i->RenshaRemaining)
		{
			if(ENEMY_SHOOT_RENSHA_FRAME < i->ShootedFrame)
			{
				shoot = 1;
				i->RenshaRemaining--;
			}
		}
		else
		{
			if(ENEMY_SHOOT_FRAME < i->ShootedFrame)
			{
				shoot = 1;
				i->RenshaRemaining = renshaCount - 1;
			}
		}

		if(shoot)
		{
			Enemy_Shot(i, eap == EAP_BOMB, eap == EAP_HOMING);
			i->ShootedFrame = 0;
		}
	}

	m_countDown(i->DamagedFrame);
	i->ShootedFrame++;

	if(SCREEN_H + Pic_H(GetEnemyPicId(i->Kind)) / 2 < i->Y) // “Ë”j‚µ‚½B
	{
		GDcNV.Score -= 1000000; // Œo”ï_“Ë”j(”±‹à)
		GDcNV.WipeOut = 0;
		return 1;
	}
	return 0;
}
void DrawEnemy(Enemy_t *i)
{
	if(!GDc.BattleStarted)
	{
		// i->Frame == 0 ŒÅ’è

		DPE_SetAlpha(0.5);
		DrawCenter(GetEnemyPicId(i->Kind) + ProcFrame / 6 % 2, d2i(i->X), d2i(i->Y));
		DPE_Reset();
	}
	else
	{
		int frm = i->Frame - 1; // frm == 0`

		if(i->DamagedFrame)
		{
			DrawCenter(GetEnemyDamagedPicId(i->Kind) + frm / 3 % 2, d2i(i->X), d2i(i->Y));
		}
		else
		{
			DrawCenter(GetEnemyPicId(i->Kind) + frm / 6 % 2, d2i(i->X), d2i(i->Y));
		}
	}
}

// <-- accessor

Enemy_t *GetNearestEnemy(double x, double y)
{
	Enemy_t *ret = NULL;
	double ret_distance = -1.0;

	for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *i = GDc.EnemyList->GetElement(index);
		double distance = GetDistance(x, y, i->X, i->Y);

		if(!ret || distance < ret_distance)
		{
			ret = i;
			ret_distance = distance;
		}
	}
	return ret;
}

int GetEnemyPicId(int kind)
{
	switch(kind)
	{
	case EK_EYE_1: return D_EYE_1_00 | DTP;
	case EK_EYE_2: return D_EYE_2_00 | DTP;
	case EK_EYE_3: return D_EYE_3_00 | DTP;
	case EK_EYE_4: return D_EYE_4_00 | DTP;
	case EK_EYE_5: return D_EYE_5_00 | DTP;
	case EK_EYE_6: return D_EYE_6_00 | DTP;
	case EK_EYE_7: return D_EYE_7_00 | DTP;
	case EK_EYE_8: return D_EYE_8_00 | DTP;
	case EK_EYE_9: return D_EYE_9_00 | DTP;
	case EK_EYE_10: return D_EYE_10_00 | DTP;
	case EK_EYE_20: return D_EYE_20_00 | DTP;
	case EK_EYE_50: return D_EYE_50_00 | DTP;
	case EK_EYE_100: return D_EYE_100_00 | DTP;

	default:
		error();
	}
}
int GetEnemyDamagedPicId(int kind)
{
	return GetEnemyPicId(kind) + 2;
}
int GetEnemyDeadPicId(int kind)
{
	return GetEnemyPicId(kind) + 4;
}
double GetEnemy_W(int kind)
{
	return Pic_W(GetEnemyPicId(kind));
}
double GetEnemy_H(int kind)
{
	return Pic_H(GetEnemyPicId(kind));
}
double GetEnemyAtari_W(int kind)
{
	return GetEnemy_W(kind) * 0.9;
}
double GetEnemyAtari_H(int kind)
{
	return GetEnemy_H(kind) * 0.9;
}

void AllEnemy_AntiHaritsuki(void)
{
	for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
	{
		Enemy_t *i = GDc.EnemyList->GetElement(index);

		if(i->HaritsukiMode == EHM_ENABLED)
			i->HaritsukiMode = EHM_ANTI_HARITSUKI;
	}
}
