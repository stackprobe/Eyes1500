#include "all.h"

PlayerMissile_t *CreatePlayerMissile(double x, double y, double dir)
{
	PlayerMissile_t *i = nb(PlayerMissile_t);

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
