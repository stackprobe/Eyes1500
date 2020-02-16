#include "all.h"

PlayerTama_t *CreatePlayerTama(double x, double y)
{
	PlayerTama_t *i = nb_(PlayerTama_t);

	i->X = x;
	i->Y = y;

	return i;
}
void ReleasePlayerTama(PlayerTama_t *i)
{
	if(!i)
		return;

	memFree(i);
}

// <-- cdtor

// <-- accessor
