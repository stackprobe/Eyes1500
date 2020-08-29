extern int IgnoreEscapeKey;

extern __int64 FrameStartTime;
extern __int64 HzChaserTime;
extern __int64 LowHzTime;
extern double EatenByLangolierEval;
extern double LowHzErrorRate;
extern int ProcFrame;
extern int FreezeInputFrame;
extern int WindowIsActive;

void EachFrame(void);
void FreezeInput(int frame = 1);
