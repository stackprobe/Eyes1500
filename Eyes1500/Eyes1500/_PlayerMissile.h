typedef struct PlayerMissile_st
{
	int Frame;
	double X;
	double Y;
	double Dir; // 0.0 〜 (PI * 2), 0.0を右として時計回り
}
PlayerMissile_t;

PlayerMissile_t *CreatePlayerMissile(double x, double y, double dir = PI * 1.5);
void ReleasePlayerMissile(PlayerMissile_t *i);

// <-- cdtor

// <-- accessor
