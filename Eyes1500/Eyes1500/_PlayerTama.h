typedef struct PlayerTama_st
{
	int Frame; // -1 == 初期化直後, 0〜
	double X;
	double Y;
}
PlayerTama_t;

PlayerTama_t *CreatePlayerTama(double x, double y);
void ReleasePlayerTama(PlayerTama_t *i);

// <-- cdtor

// <-- accessor
