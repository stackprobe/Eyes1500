typedef struct PlayerTama_st
{
	int Frame; // 0Å`
	double X;
	double Y;
}
PlayerTama_t;

PlayerTama_t *CreatePlayerTama(double x, double y);
void ReleasePlayerTama(PlayerTama_t *i);

// <-- cdtor

// <-- accessor
