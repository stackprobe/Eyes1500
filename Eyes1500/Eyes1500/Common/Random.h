/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define MT19937_N 624

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void initRnd(int seed);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void enterRnd(unsigned long *lmt, int lmti);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void leaveRnd(int *p_lmti);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int rnd(int modulo);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int bRnd(int minval, int maxval);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int sRnd(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double dRnd(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double eRnd(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int rndPct(int pct);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int rndPermil(int permil);

class Random
{
private:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	unsigned long *mt;
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int mti;

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Enter()
	{
		enterRnd(this->mt, this->mti);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Leave()
	{
		leaveRnd(&this->mti);
	}

public:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000131 $$$$ //		Random(int seed)
// #### DELETED ==== 0000131 $$$$ //		{
// #### DELETED ==== 0000131 $$$$ //			this->mt = (unsigned long *)memAlloc_NC(MT19937_N * sizeof(unsigned long));
// #### DELETED ==== 0000131 $$$$ //			this->Enter();
// #### DELETED ==== 0000131 $$$$ //			initRnd(seed);
// #### DELETED ==== 0000131 $$$$ //			this->Leave();
// #### DELETED ==== 0000131 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000132 $$$$ //		Random(const Random &source)
// #### DELETED ==== 0000132 $$$$ //		{
// #### DELETED ==== 0000132 $$$$ //			error();
// #### DELETED ==== 0000132 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	~Random()
	{
		memFree(this->mt);
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
#define WRAPPER(RET_TYPE, DEF_FUNC, CALL_FUNC) \
	DEF_FUNC \
	{ \
		this->Enter(); \
		RET_TYPE retval = CALL_FUNC; \
		this->Leave(); \
		return retval; \
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(int, int Rnd(int modulo), rnd(modulo))
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(int, int BRnd(int minval, int maxval), bRnd(minval, maxval))
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(int, int SRnd(), sRnd())
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(double, double DRnd(), dRnd())
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(double, double ERnd(), eRnd())
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(int, int RndPct(int pct), rndPct(pct))
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	WRAPPER(int, int RndPermil(int permil), rndPermil(permil))

#undef WRAPPER
};
