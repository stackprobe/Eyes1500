#define MT19937_N 624

//
// copied the source file by CopyLib.exe
//
void initRnd(int seed);

//
// copied the source file by CopyLib.exe
//
void enterRnd(unsigned long *lmt, int lmti);
//
// copied the source file by CopyLib.exe
//
void leaveRnd(int *p_lmti);

//
// copied the source file by CopyLib.exe
//
int rnd(int modulo);
//
// copied the source file by CopyLib.exe
//
int bRnd(int minval, int maxval);
//
// copied the source file by CopyLib.exe
//
int sRnd(void);
//
// copied the source file by CopyLib.exe
//
double dRnd(void);
//
// copied the source file by CopyLib.exe
//
double eRnd(void);
//
// copied the source file by CopyLib.exe
//
int rndPct(int pct);
//
// copied the source file by CopyLib.exe
//
int rndPermil(int permil);

//
// copied the source file by CopyLib.exe
//
class Random
{
//
// copied the source file by CopyLib.exe
//
private:
	unsigned long *mt;
	int mti;

	void Enter()
	{
		enterRnd(this->mt, this->mti);
	}
	void Leave()
	{
		leaveRnd(&this->mti);
	}

//
// copied the source file by CopyLib.exe
//
public:
	Random(int seed)
	{
		this->mt = (unsigned long *)memAlloc_NC(MT19937_N * sizeof(unsigned long));
		this->Enter();
		initRnd(seed);
		this->Leave();
	}
	Random(const Random &source)
	{
		error();
	}
	~Random()
	{
		memFree(this->mt);
	}

#define WRAPPER(RET_TYPE, DEF_FUNC, CALL_FUNC) \
	DEF_FUNC \
	{ \
		this->Enter(); \
		RET_TYPE retval = CALL_FUNC; \
		this->Leave(); \
		return retval; \
	}

	WRAPPER(int, int Rnd(int modulo), rnd(modulo))
	WRAPPER(int, int BRnd(int minval, int maxval), bRnd(minval, maxval))
	WRAPPER(int, int SRnd(), sRnd())
	WRAPPER(double, double DRnd(), dRnd())
	WRAPPER(double, double ERnd(), eRnd())
	WRAPPER(int, int RndPct(int pct), rndPct(pct))
	WRAPPER(int, int RndPermil(int permil), rndPermil(permil))

#undef WRAPPER
};
