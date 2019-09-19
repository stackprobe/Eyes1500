/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
DrawPicExtra_t DPE;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
typedef struct Layout_st
{
	int Mode; // "FRS"

	union
	{
		struct
		{
			double LTX;
			double LTY;
			double RTX;
			double RTY;
			double RBX;
			double RBY;
			double LBX;
			double LBY;
		}
		Free;

		struct
		{
			double L;
			double T;
			double R;
			double B;
		}
		Rect;

		struct
		{
			double X;
			double Y;
		}
		Simple;
	}
	u;
}
Layout_t;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
typedef struct Param_st
{
	int PicId;
	Layout_t *Layout;
	DrawPicExtra_t Extra;
}
Param_t;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void SetBlend(int mode, double a)
{
	m_range(a, 0.0, 1.0);

	int pal = d2i(a * 255.0);

	errorCase(pal < 0 || 255 < pal);
	errorCase(SetDrawBlendMode(mode, pal)); // ? ���s
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void ResetBlend(void)
{
	errorCase(SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0)); // ? ���s
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void SetBright(double cR, double cG, double cB) // (cR, cG, cB): 0.0 - 1.0 == �Á`��
{
	/*
		0 - 255 �ƊԈႦ�Ă��� etc.
	*/
	errorCase(!m_isRange(cR, -0.5, 1.5));
	errorCase(!m_isRange(cG, -0.5, 1.5));
	errorCase(!m_isRange(cB, -0.5, 1.5));

	m_range(cR, 0.0, 1.0);
	m_range(cG, 0.0, 1.0);
	m_range(cB, 0.0, 1.0);

	int palR = d2i(cR * 255.0);
	int palG = d2i(cG * 255.0);
	int palB = d2i(cB * 255.0);

	errorCase(!m_isRange(palR, 0, 255));
	errorCase(!m_isRange(palG, 0, 255));
	errorCase(!m_isRange(palB, 0, 255));

	errorCase(SetDrawBright(palR, palG, palB)); // ? ���s
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void ResetBright(void)
{
	errorCase(SetDrawBright(255, 255, 255)); // ? ���s
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int DrawPicFunc(Param_t *i)
{
	if(i->Extra.PicRes)
	{
		SetPicRes(i->Extra.PicRes);
	}
	if(i->Extra.AlphaOn)
	{
		SetBlend(DX_BLENDMODE_ALPHA, i->Extra.A);
	}
	else if(i->Extra.BlendAddOn)
	{
		SetBlend(DX_BLENDMODE_ADD, i->Extra.A);
	}
	else if(i->Extra.BlendInvOn)
	{
		SetBlend(DX_BLENDMODE_INVSRC, 1.0);
	}
	if(i->Extra.MosaicOn)
	{
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
	if(i->Extra.BrightOn)
	{
		SetBright(i->Extra.R, i->Extra.G, i->Extra.B);
	}

	int grphHdl;

	if(i->Extra.GraphicHandleFlag)
		grphHdl = i->PicId;
	else
		grphHdl = Pic(i->PicId);

	switch(i->Layout->Mode)
	{
	case 'F':
		{
			const double F_ZURE = 0.0;
//			const double F_ZURE = -0.5; // old

			if(i->Extra.IntPosOn ?
				DrawModiGraph(
					d2i(i->Layout->u.Free.LTX),
					d2i(i->Layout->u.Free.LTY),
					d2i(i->Layout->u.Free.RTX),
					d2i(i->Layout->u.Free.RTY),
					d2i(i->Layout->u.Free.RBX),
					d2i(i->Layout->u.Free.RBY),
					d2i(i->Layout->u.Free.LBX),
					d2i(i->Layout->u.Free.LBY),
					grphHdl,
					1
					)
				:
				DrawModiGraphF(
					(float)(i->Layout->u.Free.LTX + F_ZURE),
					(float)(i->Layout->u.Free.LTY + F_ZURE),
					(float)(i->Layout->u.Free.RTX + F_ZURE),
					(float)(i->Layout->u.Free.RTY + F_ZURE),
					(float)(i->Layout->u.Free.RBX + F_ZURE),
					(float)(i->Layout->u.Free.RBY + F_ZURE),
					(float)(i->Layout->u.Free.LBX + F_ZURE),
					(float)(i->Layout->u.Free.LBY + F_ZURE),
					grphHdl,
					1
					)
				) // ? ���s
			{
				if(!i->Extra.IgnoreError)
				{
					LOG("[DrawFree] %f %f %f %f %f %f %f %f %c %d %d\n"
						,i->Layout->u.Free.LTX
						,i->Layout->u.Free.LTY
						,i->Layout->u.Free.RTX
						,i->Layout->u.Free.RTY
						,i->Layout->u.Free.RBX
						,i->Layout->u.Free.RBY
						,i->Layout->u.Free.LBX
						,i->Layout->u.Free.LBY
						,i->PicId | DTP ? 'D' : 'P'
						,i->PicId & ~DTP
						,grphHdl
						);

					error();
				}
			}
		}
		break;

	case 'R':
		{
			if(i->Extra.IntPosOn ?
				DrawExtendGraph(
					d2i(i->Layout->u.Rect.L),
					d2i(i->Layout->u.Rect.T),
					d2i(i->Layout->u.Rect.R),
					d2i(i->Layout->u.Rect.B),
					grphHdl,
					1
					)
				:
				DrawExtendGraphF(
					(float)i->Layout->u.Rect.L,
					(float)i->Layout->u.Rect.T,
					(float)i->Layout->u.Rect.R,
					(float)i->Layout->u.Rect.B,
					grphHdl,
					1
					)
				) // ? ���s
			{
				if(!i->Extra.IgnoreError)
				{
					LOG("[DrawRect] %f %f %f %f %c %d %d\n"
						,i->Layout->u.Rect.L
						,i->Layout->u.Rect.T
						,i->Layout->u.Rect.R
						,i->Layout->u.Rect.B
						,i->PicId | DTP ? 'D' : 'P'
						,i->PicId & ~DTP
						,grphHdl
						);

					error();
				}
			}
		}
		break;

	case 'S':
		{
			if(i->Extra.IntPosOn ?
				DrawGraph(
					d2i(i->Layout->u.Simple.X),
					d2i(i->Layout->u.Simple.Y),
					grphHdl,
					1
					)
				:
				DrawGraphF(
					(float)i->Layout->u.Simple.X,
					(float)i->Layout->u.Simple.Y,
					grphHdl,
					1
					)
				) // ? ���s
			{
				if(!i->Extra.IgnoreError)
				{
					LOG("[DrawSimple] %f %f %c %d %d\n"
						,i->Layout->u.Simple.X
						,i->Layout->u.Simple.Y
						,i->PicId | DTP ? 'D' : 'P'
						,i->PicId & ~DTP
						,grphHdl
						);

					error();
				}
			}
		}
		break;

	default:
		error();
	}

	if(i->Extra.PicRes)
	{
		ResetPicRes();
	}
	if(i->Extra.AlphaOn || i->Extra.BlendAddOn || i->Extra.BlendInvOn)
	{
		ResetBlend();
	}
	if(i->Extra.MosaicOn)
	{
		SetDrawMode(DX_DRAWMODE_BILINEAR);
	}
	if(i->Extra.BrightOn)
	{
		ResetBright();
	}

	return 0;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void DrawPicReleaseParam(Param_t *i)
{
	memFree(i->Layout);
	memFree(i);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static void DrawPic(int picId, Layout_t *layout_bind)
{
	Param_t *i = nb(Param_t);

	i->PicId = picId;
	i->Layout = layout_bind;
	i->Extra = DPE;

	if(!i->Extra.TL)
	{
		DrawPicFunc(i);
		DrawPicReleaseParam(i);
	}
	else
		AddTask(i->Extra.TL, 0, DrawPicFunc, i, DrawPicReleaseParam);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000059 $$$$ //	void DrawFree(int picId, double ltx, double lty, double rtx, double rty, double rbx, double rby, double lbx, double lby)
// #### DELETED ==== 0000059 $$$$ //	{
// #### DELETED ==== 0000059 $$$$ //		// layout no-check
// #### DELETED ==== 0000059 $$$$ //	
// #### DELETED ==== 0000059 $$$$ //		Layout_t *i = nb(Layout_t);
// #### DELETED ==== 0000059 $$$$ //	
// #### DELETED ==== 0000059 $$$$ //		i->Mode = 'F';
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.LTX = ltx;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.LTY = lty;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.RTX = rtx;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.RTY = rty;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.RBX = rbx;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.RBY = rby;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.LBX = lbx;
// #### DELETED ==== 0000059 $$$$ //		i->u.Free.LBY = lby;
// #### DELETED ==== 0000059 $$$$ //	
// #### DELETED ==== 0000059 $$$$ //		DrawPic(picId, i);
// #### DELETED ==== 0000059 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawRect_LTRB(int picId, double l, double t, double r, double b)
{
	// layout check {
	errorCase(l < -(double)IMAX || (double)IMAX - 1.0 < l);
	errorCase(t < -(double)IMAX || (double)IMAX - 1.0 < t);
	errorCase(r < l + 1.0 || (double)IMAX < r);
	errorCase(b < t + 1.0 || (double)IMAX < b);
	// }

	Layout_t *i = nb(Layout_t);

	i->Mode = 'R';
	i->u.Rect.L = l;
	i->u.Rect.T = t;
	i->u.Rect.R = r;
	i->u.Rect.B = b;

	DrawPic(picId, i);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawRect(int picId, double l, double t, double w, double h)
{
	DrawRect_LTRB(picId, l, t, l + w, t + h);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawSimple(int picId, double x, double y)
{
	// layout check {
	errorCase(x < -(double)IMAX || (double)IMAX < x);
	errorCase(y < -(double)IMAX || (double)IMAX < y);
	// }

	Layout_t *i = nb(Layout_t);

	i->Mode = 'S';
	i->u.Simple.X = x;
	i->u.Simple.Y = y;

	DrawPic(picId, i);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawCenter(int picId, double x, double y)
{
	// layout check {
	errorCase(x < -(double)IMAX || (double)IMAX < x);
	errorCase(y < -(double)IMAX || (double)IMAX < y);
	// }

	DrawBegin(picId, x, y);
	DrawEnd();
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int DB_PicId;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static double DB_X;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static double DB_Y;
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static Layout_t *DB_L;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawBegin(int picId, double x, double y)
{
	errorCase(DB_L);

	Layout_t *i = nb(Layout_t);

	double w;
	double h;

	if(DPE.GraphicHandleFlag)
	{
		w = DPE.GraphicSize.X;
		h = DPE.GraphicSize.Y;

		errorCase(!m_isRange(w, 1, IMAX));
		errorCase(!m_isRange(h, 1, IMAX));
	}
	else
	{
		w = Pic_W(picId);
		h = Pic_H(picId);
	}
	w /= 2.0;
	h /= 2.0;

	i->Mode = 'F';
	i->u.Free.LTX = -w;
	i->u.Free.LTY = -h;
	i->u.Free.RTX =  w;
	i->u.Free.RTY = -h;
	i->u.Free.RBX =  w;
	i->u.Free.RBY =  h;
	i->u.Free.LBX = -w;
	i->u.Free.LBY =  h;

	DB_PicId = picId;
	DB_X = x;
	DB_Y = y;
	DB_L = i;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawSlide(double x, double y)
{
	errorCase(!DB_L);

	Layout_t *i = DB_L;

	i->u.Free.LTX += x;
	i->u.Free.LTY += y;
	i->u.Free.RTX += x;
	i->u.Free.RTY += y;
	i->u.Free.RBX += x;
	i->u.Free.RBY += y;
	i->u.Free.LBX += x;
	i->u.Free.LBY += y;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawRotate(double rot)
{
	errorCase(!DB_L);

	Layout_t *i = DB_L;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define ROTATE(x, y) \
	w = x * cos(rot) - y * sin(rot); \
	y = x * sin(rot) + y * cos(rot); \
	x = w

	double w;

	ROTATE(i->u.Free.LTX, i->u.Free.LTY);
	ROTATE(i->u.Free.RTX, i->u.Free.RTY);
	ROTATE(i->u.Free.RBX, i->u.Free.RBY);
	ROTATE(i->u.Free.LBX, i->u.Free.LBY);

#undef ROTATE
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawZoom_X(double z)
{
	errorCase(!DB_L);

	Layout_t *i = DB_L;

	i->u.Free.LTX *= z;
	i->u.Free.RTX *= z;
	i->u.Free.RBX *= z;
	i->u.Free.LBX *= z;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawZoom_Y(double z)
{
	errorCase(!DB_L);

	Layout_t *i = DB_L;

	i->u.Free.LTY *= z;
	i->u.Free.RTY *= z;
	i->u.Free.RBY *= z;
	i->u.Free.LBY *= z;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawZoom(double z)
{
	DrawZoom_X(z);
	DrawZoom_Y(z);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DrawEnd(void)
{
	errorCase(!DB_L);

	Layout_t *i = DB_L;

	i->u.Free.LTX += DB_X;
	i->u.Free.LTY += DB_Y;
	i->u.Free.RTX += DB_X;
	i->u.Free.RTY += DB_Y;
	i->u.Free.RBX += DB_X;
	i->u.Free.RBY += DB_Y;
	i->u.Free.LBX += DB_X;
	i->u.Free.LBY += DB_Y;

	DrawPic(DB_PicId, i);
	DB_L = NULL;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DPE_SetAlpha(double a)
{
	DPE.A = a;
	DPE.AlphaOn = 1;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DPE_SetBlendAdd(double a)
{
	DPE.A = a;
	DPE.BlendAddOn = 1;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DPE_SetBright(double cR, double cG, double cB)
{
	DPE.R = cR;
	DPE.G = cG;
	DPE.B = cB;
	DPE.BrightOn = 1;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000060 $$$$ //	void DPE_SetBright(int color)
// #### DELETED ==== 0000060 $$$$ //	{
// #### DELETED ==== 0000060 $$$$ //		int r = color >> 16 & 0xff;
// #### DELETED ==== 0000060 $$$$ //		int g = color >>  8 & 0xff;
// #### DELETED ==== 0000060 $$$$ //		int b = color >>  0 & 0xff;
// #### DELETED ==== 0000060 $$$$ //	
// #### DELETED ==== 0000060 $$$$ //		DPE_SetBright((double)r / 0xff, (double)g / 0xff, (double)b / 0xff);
// #### DELETED ==== 0000060 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DPE_SetGraphicSize(i2D_t size)
{
	DPE.GraphicHandleFlag = 1;
	DPE.GraphicSize = size;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void DPE_Reset(void)
{
	memset(&DPE, 0x00, sizeof(DrawPicExtra_t));
}
