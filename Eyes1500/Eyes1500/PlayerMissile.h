typedef struct PlayerMissile_st
{
	int Frame;
	double X;
	double Y;
	double Dir; // 0.0 〜 (PI * 2), 右真横(0,0 -> 1,0方向)を0.0として時計回り
}
PlayerMissile_t;

PlayerMissile_t *CreatePlayerMissile(double x, double y, double dir = PI * 1.5);
void ReleasePlayerMissile(PlayerMissile_t *i);

// <-- cdtor

// <-- accessor

void PlayerMissile_Move(PlayerMissile_t *i);
