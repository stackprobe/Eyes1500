void swapBlock(void *a, void *b, int size);

int d2i(double value);
__int64 d2i64(double value);
int s2i(char *line, int minval, int maxval, int defval);
int s2i_x(char *line, int minval, int maxval, int defval);

int getZero(void);
uint getUIZero(void);
__int64 getI64Zero(void);
void noop(void);
void noop_i(int dummy);
void noop_ui(uint dummy);
void noop_i64(__int64 dummy);

i2D_t makeI2D(int x, int y);
iRect_t makeIRect(int l, int t, int w, int h);
d2D_t makeD2D(double x, double y);

void my_memset(void *block, int fillValue, int size);

template <class Var_t>
void zeroclear(Var_t *var, int num = 1)
{
	my_memset(var, 0x00, num * sizeof(Var_t));
}

template <class Type_t>
int isPointNull(Type_t **pp)
{
	return !*pp;
}

double getAngle(double x, double y);
double getAngle(double x, double y, double originX, double originY);
void rotatePos(double angle, double &x, double &y);
void rotatePos(double angle, double &x, double &y, double originX, double originY);
void angleToXY(double angle, double distance, double &x, double &y);
void angleToXY(double angle, double distance, double &x, double &y, double originX, double originY);
void angleMoveXY(double angle, double distance, double &x, double &y);
