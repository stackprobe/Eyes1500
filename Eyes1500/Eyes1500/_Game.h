typedef struct GDc_st
{
	// Params {
	// }

	// Return {
	// }

	__int64 Score;

	struct
	{
		int BornFrame; // 0 == ñ≥å¯, 1Å`
		double X;
		double Y;
		double RealX;
		double RealY;
	}
	Player;

	autoList<PlayerTama_t *> *PlayerTamaList;
}
GDc_t;

extern GDc_t GDc;

void GameInit(void);
void GameFnlz(void);
