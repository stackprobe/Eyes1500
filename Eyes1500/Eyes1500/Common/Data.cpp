/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000041 $$$$ //	void swapBlock(void *a, void *b, int size)
// #### DELETED ==== 0000041 $$$$ //	{
// #### DELETED ==== 0000041 $$$$ //		swap((uchar *)a, (uchar *)b, size);
// #### DELETED ==== 0000041 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int d2i(double value)
{
	return (int)(value + (value < 0.0 ? -0.5 : 0.5));
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
__int64 d2i64(double value)
{
	return (__int64)(value + (value < 0.0 ? -0.5 : 0.5));
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int s2i(char *line, int minval, int maxval, int defval)
{
	if(m_isEmpty(line) || !strchr("-0123456789", *line))
	{
		return defval;
	}
	int value = atoi(line);
	m_range(value, minval, maxval);
	return value;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000042 $$$$ //	int s2i_x(char *line, int minval, int maxval, int defval)
// #### DELETED ==== 0000042 $$$$ //	{
// #### DELETED ==== 0000042 $$$$ //		int value = s2i(line, minval, maxval, defval);
// #### DELETED ==== 0000042 $$$$ //		memFree(line);
// #### DELETED ==== 0000042 $$$$ //		return value;
// #### DELETED ==== 0000042 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000043 $$$$ //	int getZero(void)
// #### DELETED ==== 0000043 $$$$ //	{
// #### DELETED ==== 0000043 $$$$ //		return 0;
// #### DELETED ==== 0000043 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000044 $$$$ //	uint getUIZero(void)
// #### DELETED ==== 0000044 $$$$ //	{
// #### DELETED ==== 0000044 $$$$ //		return 0;
// #### DELETED ==== 0000044 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000045 $$$$ //	__int64 getI64Zero(void)
// #### DELETED ==== 0000045 $$$$ //	{
// #### DELETED ==== 0000045 $$$$ //		return 0;
// #### DELETED ==== 0000045 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000046 $$$$ //	void noop(void)
// #### DELETED ==== 0000046 $$$$ //	{
// #### DELETED ==== 0000046 $$$$ //		1; // noop
// #### DELETED ==== 0000046 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000047 $$$$ //	void noop_i(int dummy)
// #### DELETED ==== 0000047 $$$$ //	{
// #### DELETED ==== 0000047 $$$$ //		1; // noop
// #### DELETED ==== 0000047 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000048 $$$$ //	void noop_ui(uint dummy)
// #### DELETED ==== 0000048 $$$$ //	{
// #### DELETED ==== 0000048 $$$$ //		1; // noop
// #### DELETED ==== 0000048 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000049 $$$$ //	void noop_i64(__int64 dummy)
// #### DELETED ==== 0000049 $$$$ //	{
// #### DELETED ==== 0000049 $$$$ //		1; // noop
// #### DELETED ==== 0000049 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000050 $$$$ //	i2D_t makeI2D(int x, int y)
// #### DELETED ==== 0000050 $$$$ //	{
// #### DELETED ==== 0000050 $$$$ //		i2D_t pos;
// #### DELETED ==== 0000050 $$$$ //	
// #### DELETED ==== 0000050 $$$$ //		pos.X = x;
// #### DELETED ==== 0000050 $$$$ //		pos.Y = y;
// #### DELETED ==== 0000050 $$$$ //	
// #### DELETED ==== 0000050 $$$$ //		return pos;
// #### DELETED ==== 0000050 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000051 $$$$ //	iRect_t makeIRect(int l, int t, int w, int h)
// #### DELETED ==== 0000051 $$$$ //	{
// #### DELETED ==== 0000051 $$$$ //		iRect_t rect;
// #### DELETED ==== 0000051 $$$$ //	
// #### DELETED ==== 0000051 $$$$ //		rect.L = l;
// #### DELETED ==== 0000051 $$$$ //		rect.T = t;
// #### DELETED ==== 0000051 $$$$ //		rect.W = w;
// #### DELETED ==== 0000051 $$$$ //		rect.H = h;
// #### DELETED ==== 0000051 $$$$ //	
// #### DELETED ==== 0000051 $$$$ //		return rect;
// #### DELETED ==== 0000051 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000052 $$$$ //	d2D_t makeD2D(double x, double y)
// #### DELETED ==== 0000052 $$$$ //	{
// #### DELETED ==== 0000052 $$$$ //		d2D_t pos;
// #### DELETED ==== 0000052 $$$$ //	
// #### DELETED ==== 0000052 $$$$ //		pos.X = x;
// #### DELETED ==== 0000052 $$$$ //		pos.Y = y;
// #### DELETED ==== 0000052 $$$$ //	
// #### DELETED ==== 0000052 $$$$ //		return pos;
// #### DELETED ==== 0000052 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void my_memset(void *block, int fillValue, int size)
{
	for(int index = 0; index < size; index++)
	{
		((uchar *)block)[index] = fillValue;
	}
}

// 角度から方向 ... MakeXYSpeed, angleToXY

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	ret: 0.0 ～ PI * 2.0
		右真横(0,0 -> 1,0方向)を0.0として、時計回り。(但し、X軸プラス方向を右、Y軸プラス方向を下)
		1周は PI * 2.0
*/
double getAngle(double x, double y)
{
	if(y < 0.0) return PI * 2.0 - getAngle(x, -y);
	if(x < 0.0) return PI - getAngle(-x, y);

	if(x <= 0.0) return PI / 2.0;
	if(y <= 0.0) return 0;

	double r1 = 0;
	double r2 = PI / 2.0;
	double t = y / x;
	double rm;

	for(int c = 1; ; c++)
	{
		rm = (r1 + r2) / 2.0;

		if(10 <= c)
			break;

		double rmt = tan(rm);

		if(t < rmt)
			r2 = rm;
		else
			r1 = rm;
	}
	return rm;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double getAngle(double x, double y, double originX, double originY)
{
	return getAngle(x - originX, y - originY);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void rotatePos(double angle, double &x, double &y)
{
	double w;

	w = x * cos(angle) - y * sin(angle);
	y = x * sin(angle) + y * cos(angle);
	x = w;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000053 $$$$ //	void rotatePos(double angle, double &x, double &y, double originX, double originY)
// #### DELETED ==== 0000053 $$$$ //	{
// #### DELETED ==== 0000053 $$$$ //		x -= originX;
// #### DELETED ==== 0000053 $$$$ //		y -= originY;
// #### DELETED ==== 0000053 $$$$ //	
// #### DELETED ==== 0000053 $$$$ //		rotatePos(angle, x, y);
// #### DELETED ==== 0000053 $$$$ //	
// #### DELETED ==== 0000053 $$$$ //		x += originX;
// #### DELETED ==== 0000053 $$$$ //		y += originY;
// #### DELETED ==== 0000053 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void angleToXY(double angle, double distance, double &x, double &y)
{
	x = distance * cos(angle);
	y = distance * sin(angle);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void angleToXY(double angle, double distance, double &x, double &y, double originX, double originY)
{
	angleToXY(angle, distance, x, y);

	x += originX;
	y += originY;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void angleMoveXY(double angle, double distance, double &x, double &y)
{
	angleToXY(angle, distance, x, y, x, y);
}
