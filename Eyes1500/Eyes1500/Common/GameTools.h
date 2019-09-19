extern int sc_numer; // 0 - sc_denom
extern int sc_denom; // 1 - *
extern double sc_rate; // 0.0 - 1.0

void sceneEnter(void);
void sceneLeave(void);

/*
	sceneLeave();

注意
	forscene ブロック内から return するときは sceneLeave(); すること。

	ex.
		forscene(123)
		{
			...
			if(...)
			{
				sceneLeave();
				return;
			}
			...
		}
		sceneLeave();
*/
// frameMax: (1 ～ *)
#define forscene(frameMax) \
	for(sceneEnter(), sc_denom = (frameMax), sc_numer = 0; sc_numer <= (frameMax) && (sc_rate = (double)sc_numer / sc_denom, 1); sc_numer++)

/*
	sceneLeave();

シーケンス
	ifsceneBegin (1) -> ifscene (0*) -> ifsceneEnd (0*1) -> sceneLeave (1)

注意
	ifsceneBegin, ifscene, ifsceneEnd ブロック内から continue, break, return するときは sceneLeave(); すること。

	ex.
		...
		ifsceneEnd
		{
			sceneLeave();
			continue; // break, return
		}
		sceneLeave();
*/
// frameMax: (1 ～ *), count: (0 ～ *)
#define ifsceneBegin(frameMax, count) \
	if(sceneEnter(), sc_numer = (count), 0) { } ifscene((frameMax))

// frameMax: (1 ～ *)
#define ifscene(frameMax) \
	else if(sc_numer <= (frameMax) ? (sc_denom = (frameMax), sc_rate = (double)sc_numer / sc_denom, 1) : (sc_numer -= (frameMax) + 1, 0))

#define ifsceneEnd \
	else

// ---- Curtain ----

extern double CurrCurtainWhiteLevel;

void CurtainEachFrame(int oncePerFrame = 1);
void SetCurtain(int frameMax = 30, double destWhiteLevel = 0.0, double startWhiteLevel = CurrCurtainWhiteLevel);

// ---- Print ----

typedef struct PrintExtra_st
{
	taskList *TL;
	int Color;

	// change by PE_*() -->

	int Border; // 0 == 無効
	int BorderColor;
}
PrintExtra_t;

extern PrintExtra_t PE;

void PE_Border(int color = GetColor(0, 0, 0));
void PE_Reset(void);

void SetPrint(int x = 0, int y = 0, int yStep = 16);
void PrintRet(void);
void Print(char *token);
void Print_x(char *token);

// ---- ui tools ----

void DrawCurtain(double whiteLevel = -1.0);

// ----

int RotDir(int dir, int rot);
int IsOut(double x, double y, double l, double t, double r, double b, double margin = 0.0);
int IsOutOfScreen(double x, double y, double margin = 0.0);
