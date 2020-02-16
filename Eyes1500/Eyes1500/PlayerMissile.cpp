#include "all.h"

PlayerMissile_t *CreatePlayerMissile(double x, double y, double dir)
{
	PlayerMissile_t *i = nb_(PlayerMissile_t);

	i->X = x;
	i->Y = y;
	i->Dir = dir;

	return i;
}
void ReleasePlayerMissile(PlayerMissile_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

// <-- accessor

void PlayerMissile_Move(PlayerMissile_t *i)
{
	Enemy_t *e = GetNearestEnemy(i->X, i->Y);

	if(e)
	{
		double angle = getAngle(e->X, e->Y, i->X, i->Y);

		if(PI < abs(angle - i->Dir))
		{
			if(angle < i->Dir)
				angle += PI * 2.0;
			else
				angle -= PI * 2.0;
		}
		
		{
			double rotSpeed = 0.03;

			if(rotSpeed < abs(angle - i->Dir))
			{
				if(angle < i->Dir)
					i->Dir -= rotSpeed;
				else
					i->Dir += rotSpeed;
			}
			else
				i->Dir = angle;
		}
	}

	angleMoveXY(i->Dir, 3.0, i->X, i->Y); // ˆÚ“®
}
