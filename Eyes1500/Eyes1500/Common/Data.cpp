#include "all.h"

int d2i(double value)
{
	return (int)(value + (value < 0.0 ? -0.5 : 0.5));
}
__int64 d2i64(double value)
{
	return (__int64)(value + (value < 0.0 ? -0.5 : 0.5));
}
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

void my_memset(void *block, int fillValue, int size)
{
	for(int index = 0; index < size; index++)
	{
		((uchar *)block)[index] = fillValue;
	}
}

// 角度から方向 ... MakeXYSpeed, angleToXY

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
double getAngle(double x, double y, double originX, double originY)
{
	return getAngle(x - originX, y - originY);
}
void rotatePos(double angle, double &x, double &y)
{
	double w;

	w = x * cos(angle) - y * sin(angle);
	y = x * sin(angle) + y * cos(angle);
	x = w;
}
void angleToXY(double angle, double distance, double &x, double &y)
{
	x = distance * cos(angle);
	y = distance * sin(angle);
}
void angleToXY(double angle, double distance, double &x, double &y, double originX, double originY)
{
	angleToXY(angle, distance, x, y);

	x += originX;
	y += originY;
}
void angleMoveXY(double angle, double distance, double &x, double &y)
{
	angleToXY(angle, distance, x, y, x, y);
}
