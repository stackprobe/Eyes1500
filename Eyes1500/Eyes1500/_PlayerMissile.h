typedef struct PlayerMissile_st
{
	int Frame;
	double X;
	double Y;
	double Dir; // 0.0 ` (PI * 2), ‰E^‰¡(0,0 -> 1,0•ûŒü)‚ð0.0‚Æ‚µ‚ÄŽžŒv‰ñ‚è
}
PlayerMissile_t;

PlayerMissile_t *CreatePlayerMissile(double x, double y, double dir = PI * 1.5);
void ReleasePlayerMissile(PlayerMissile_t *i);

// <-- cdtor

// <-- accessor

void PlayerMissile_Move(PlayerMissile_t *i);
