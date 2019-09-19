/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000054 $$$$ //	template <class Value_t>
// #### DELETED ==== 0000054 $$$$ //	void swap(Value_t *a, Value_t *b, int size)
// #### DELETED ==== 0000054 $$$$ //	{
// #### DELETED ==== 0000054 $$$$ //		Value_t *tmp = na(Value_t, size);
// #### DELETED ==== 0000054 $$$$ //	
// #### DELETED ==== 0000054 $$$$ //		memcpy(tmp, a, size);
// #### DELETED ==== 0000054 $$$$ //		memcpy(a, b, size);
// #### DELETED ==== 0000054 $$$$ //		memcpy(b, tmp, size);
// #### DELETED ==== 0000054 $$$$ //	
// #### DELETED ==== 0000054 $$$$ //		memFree(tmp);
// #### DELETED ==== 0000054 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000055 $$$$ //	template <class Value_t>
// #### DELETED ==== 0000055 $$$$ //	void swap(Value_t &a, Value_t &b)
// #### DELETED ==== 0000055 $$$$ //	{
// #### DELETED ==== 0000055 $$$$ //		Value_t tmp = a;
// #### DELETED ==== 0000055 $$$$ //		a = b;
// #### DELETED ==== 0000055 $$$$ //		b = tmp;
// #### DELETED ==== 0000055 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void swapBlock(void *a, void *b, int size);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int d2i(double value);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 d2i64(double value);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int s2i(char *line, int minval, int maxval, int defval);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int s2i_x(char *line, int minval, int maxval, int defval);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int getZero(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
uint getUIZero(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 getI64Zero(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void noop(void);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void noop_i(int dummy);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void noop_ui(uint dummy);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void noop_i64(__int64 dummy);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
i2D_t makeI2D(int x, int y);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
iRect_t makeIRect(int l, int t, int w, int h);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
d2D_t makeD2D(double x, double y);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void my_memset(void *block, int fillValue, int size);

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
template <class Var_t>
void zeroclear(Var_t *var, int num = 1)
{
	my_memset(var, 0x00, num * sizeof(Var_t));
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000056 $$$$ //	template <class Var_t>
// #### DELETED ==== 0000056 $$$$ //	int isallzero(Var_t *var, int num = 1)
// #### DELETED ==== 0000056 $$$$ //	{
// #### DELETED ==== 0000056 $$$$ //		return isFilled(var, 0x00, num * sizeof(Var_t));
// #### DELETED ==== 0000056 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
template <class Type_t>
int isPointNull(Type_t **pp)
{
	return !*pp;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000057 $$$$ //	template <class Deletable_t>
// #### DELETED ==== 0000057 $$$$ //	void callDelete(Deletable_t *i)
// #### DELETED ==== 0000057 $$$$ //	{
// #### DELETED ==== 0000057 $$$$ //		delete i;
// #### DELETED ==== 0000057 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000058 $$$$ //	template <class Deletable_t>
// #### DELETED ==== 0000058 $$$$ //	void deleteList(autoList<Deletable_t> *list)
// #### DELETED ==== 0000058 $$$$ //	{
// #### DELETED ==== 0000058 $$$$ //		list->CallAllElement(callDelete);
// #### DELETED ==== 0000058 $$$$ //		delete list;
// #### DELETED ==== 0000058 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double getAngle(double x, double y);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double getAngle(double x, double y, double originX, double originY);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void rotatePos(double angle, double &x, double &y);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void rotatePos(double angle, double &x, double &y, double originX, double originY);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void angleToXY(double angle, double distance, double &x, double &y);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void angleToXY(double angle, double distance, double &x, double &y, double originX, double originY);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void angleMoveXY(double angle, double distance, double &x, double &y);
