//
// copied the source file by CopyLib.exe
//
int d2i(double value);
//
// copied the source file by CopyLib.exe
//
int s2i(char *line, int minval, int maxval, int defval);
//
// copied the source file by CopyLib.exe
//
int s2i_x(char *line, int minval, int maxval, int defval);
//
// copied the source file by CopyLib.exe
//
int isPound(int counter);
//
// copied the source file by CopyLib.exe
//
autoList<char *> *tokenize(char *line, char *delimiters);
//
// copied the source file by CopyLib.exe
//
char *untokenize(autoList<char *> *tokens, char *separator);

//
// copied the source file by CopyLib.exe
//
template <class Var_t>
//
// copied the source file by CopyLib.exe
//
void t_swap(Var_t &a, Var_t &b)
{
	Var_t tmp = a;
	a = b;
	b = tmp;
}

//
// copied the source file by CopyLib.exe
//
int getZero(void);
//
// copied the source file by CopyLib.exe
//
uint getUIZero(void);
__int64 getI64Zero(void);
//
// copied the source file by CopyLib.exe
//
void noop(void);
//
// copied the source file by CopyLib.exe
//
void noop_i(int dummy);
//
// copied the source file by CopyLib.exe
//
void noop_ui(uint dummy);
//
// copied the source file by CopyLib.exe
//
void noop_i64(__int64 dummy);

//
// copied the source file by CopyLib.exe
//
i2D_t makeI2D(int x, int y);
//
// copied the source file by CopyLib.exe
//
d2D_t makeD2D(double x, double y);

//
// copied the source file by CopyLib.exe
//
bitList *createBitList(void);
//
// copied the source file by CopyLib.exe
//
void releaseBitList(bitList *bl);

//
// copied the source file by CopyLib.exe
//
void my_memset(void *block, int fillValue, int size);
//
// copied the source file by CopyLib.exe
//
int isfilled(void *block, int fillValue, int size);
//
// copied the source file by CopyLib.exe
//
int isSame(autoList<uchar> *binData1, autoList<uchar> *binData2);

//
// copied the source file by CopyLib.exe
//
template <class Var_t>
//
// copied the source file by CopyLib.exe
//
void zeroclear(Var_t *var, int num = 1)
{
	my_memset(var, 0x00, num * sizeof(Var_t));
}

//
// copied the source file by CopyLib.exe
//
template <class Var_t>
//
// copied the source file by CopyLib.exe
//
int isallzero(Var_t *var, int num = 1)
{
	return isfilled(var, 0x00, num * sizeof(Var_t));
}

//
// copied the source file by CopyLib.exe
//
template <class Type_t>
//
// copied the source file by CopyLib.exe
//
int isPointNull(Type_t **pp)
{
	return !*pp;
}

//
// copied the source file by CopyLib.exe
//
template <class Deletable_t>
//
// copied the source file by CopyLib.exe
//
void callDelete(Deletable_t *i)
{
	delete i;
}

//
// copied the source file by CopyLib.exe
//
template <class Deletable_t>
//
// copied the source file by CopyLib.exe
//
void deleteList(autoList<Deletable_t> *list)
{
	list->CallAllElement(callDelete);
	delete list;
}

//
// copied the source file by CopyLib.exe
//
double getAngle(double x, double y);
//
// copied the source file by CopyLib.exe
//
double getAngle(double x, double y, double originX, double originY);
//
// copied the source file by CopyLib.exe
//
void rotatePos(double angle, double &x, double &y);
//
// copied the source file by CopyLib.exe
//
void rotatePos(double angle, double &x, double &y, double originX, double originY);
//
// copied the source file by CopyLib.exe
//
void angleToXY(double angle, double distance, double &x, double &y);
//
// copied the source file by CopyLib.exe
//
void angleToXY(double angle, double distance, double &x, double &y, double originX, double originY);
//
// copied the source file by CopyLib.exe
//
void angleMoveXY(double angle, double distance, double &x, double &y);
