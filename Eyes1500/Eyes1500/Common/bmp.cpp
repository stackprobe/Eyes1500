/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static struct
{
	uint16 Type;
	uint Size;
	uint16 Reserved_01;
	uint16 Reserved_02;
	uint OffBits;
}
Bfh;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static struct
{
	uint Size;
	uint Width;
	uint Height;
	uint16 Planes;
	uint16 BitCount;
	uint Compression;
	uint SizeImage;
	uint XPelsPerMeter;
	uint YPelsPerMeter;
	uint ClrUsed;
	uint ClrImportant;
}
Bfi;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000031 $$$$ //	autoTable<uint> *readBmpFile(autoList<uchar> *fileData)
// #### DELETED ==== 0000031 $$$$ //	{
// #### DELETED ==== 0000031 $$$$ //		autoTable<uint> *table = new autoTable<uint>(getUIZero, noop_ui);
// #### DELETED ==== 0000031 $$$$ //		autoList<uint> *colorPallet = new autoList<uint>();
// #### DELETED ==== 0000031 $$$$ //		int rIndex = 0;
// #### DELETED ==== 0000031 $$$$ //		uint colPalCnt;
// #### DELETED ==== 0000031 $$$$ //		uint x;
// #### DELETED ==== 0000031 $$$$ //		uint y;
// #### DELETED ==== 0000031 $$$$ //		uint hiSign;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		Bfh.Type = readUI32(fileData, rIndex, 2); // 'BM'
// #### DELETED ==== 0000031 $$$$ //		Bfh.Size = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfh.Reserved_01 = (uint)readUI32(fileData, rIndex, 2);
// #### DELETED ==== 0000031 $$$$ //		Bfh.Reserved_02 = (uint)readUI32(fileData, rIndex, 2);
// #### DELETED ==== 0000031 $$$$ //		Bfh.OffBits = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		Bfi.Size = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.Width = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.Height = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.Planes = (uint)readUI32(fileData, rIndex, 2);
// #### DELETED ==== 0000031 $$$$ //		Bfi.BitCount = (uint)readUI32(fileData, rIndex, 2);
// #### DELETED ==== 0000031 $$$$ //		Bfi.Compression = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.SizeImage = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.XPelsPerMeter = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.YPelsPerMeter = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.ClrUsed = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //		Bfi.ClrImportant = readUI32(fileData, rIndex);
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		errorCase(Bfh.Type != ('B' | 'M' << 8));
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		hiSign = 0x80000000 & Bfi.Height;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		if(hiSign)
// #### DELETED ==== 0000031 $$$$ //			Bfi.Height = (Bfi.Height ^ 0xffffffff) + 1;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		errorCase(!Bfi.Width);
// #### DELETED ==== 0000031 $$$$ //		errorCase(!Bfi.Height);
// #### DELETED ==== 0000031 $$$$ //		errorCase(IMAX / Bfi.Width < Bfi.Height);
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		table->Resize(Bfi.Width, Bfi.Height);
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		switch(Bfi.BitCount)
// #### DELETED ==== 0000031 $$$$ //		{
// #### DELETED ==== 0000031 $$$$ //		case 1: colPalCnt = 2; break;
// #### DELETED ==== 0000031 $$$$ //		case 4: colPalCnt = 16; break;
// #### DELETED ==== 0000031 $$$$ //		case 8: colPalCnt = 256; break;
// #### DELETED ==== 0000031 $$$$ //		case 24:
// #### DELETED ==== 0000031 $$$$ //			colPalCnt = 0;
// #### DELETED ==== 0000031 $$$$ //			break;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		default:
// #### DELETED ==== 0000031 $$$$ //			error();
// #### DELETED ==== 0000031 $$$$ //		}
// #### DELETED ==== 0000031 $$$$ //		while(colPalCnt)
// #### DELETED ==== 0000031 $$$$ //		{
// #### DELETED ==== 0000031 $$$$ //			uchar cR;
// #### DELETED ==== 0000031 $$$$ //			uchar cG;
// #### DELETED ==== 0000031 $$$$ //			uchar cB;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //			// BGR ’ˆÓ
// #### DELETED ==== 0000031 $$$$ //			cB = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //			cG = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //			cR = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //			rIndex++; // reserved
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //			colorPallet->AddElement(cR << 16 | cG << 8 | cB);
// #### DELETED ==== 0000031 $$$$ //			colPalCnt--;
// #### DELETED ==== 0000031 $$$$ //		}
// #### DELETED ==== 0000031 $$$$ //		for(y = 0; y < Bfi.Height; y++)
// #### DELETED ==== 0000031 $$$$ //		{
// #### DELETED ==== 0000031 $$$$ //			if(Bfi.BitCount <= 8)
// #### DELETED ==== 0000031 $$$$ //			{
// #### DELETED ==== 0000031 $$$$ //				uint bitMax = 8 / Bfi.BitCount;
// #### DELETED ==== 0000031 $$$$ //				uint bit;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //				x = 0;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //				while(x < Bfi.Width)
// #### DELETED ==== 0000031 $$$$ //				{
// #### DELETED ==== 0000031 $$$$ //					uchar c8 = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //					for(bit = bitMax; bit && x < Bfi.Width; bit--, x++)
// #### DELETED ==== 0000031 $$$$ //					{
// #### DELETED ==== 0000031 $$$$ //						table->SetCell(x, y, colorPallet->GetElement(c8 & (1 << Bfi.BitCount) - 1));
// #### DELETED ==== 0000031 $$$$ //						c8 >>= Bfi.BitCount;
// #### DELETED ==== 0000031 $$$$ //					}
// #### DELETED ==== 0000031 $$$$ //				}
// #### DELETED ==== 0000031 $$$$ //				for(x = (4 - ((Bfi.Width + bitMax - 1) / bitMax) % 4) % 4; x; x--)
// #### DELETED ==== 0000031 $$$$ //				{
// #### DELETED ==== 0000031 $$$$ //					rIndex++;
// #### DELETED ==== 0000031 $$$$ //				}
// #### DELETED ==== 0000031 $$$$ //			}
// #### DELETED ==== 0000031 $$$$ //			else
// #### DELETED ==== 0000031 $$$$ //			{
// #### DELETED ==== 0000031 $$$$ //				for(x = 0; x < Bfi.Width; x++)
// #### DELETED ==== 0000031 $$$$ //				{
// #### DELETED ==== 0000031 $$$$ //					uchar cR;
// #### DELETED ==== 0000031 $$$$ //					uchar cG;
// #### DELETED ==== 0000031 $$$$ //					uchar cB;
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //					// BGR ’ˆÓ
// #### DELETED ==== 0000031 $$$$ //					cB = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //					cG = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //					cR = fileData->GetElement(rIndex++);
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //					table->SetCell(x, y, cR << 16 | cG << 8 | cB);
// #### DELETED ==== 0000031 $$$$ //				}
// #### DELETED ==== 0000031 $$$$ //				for(x = Bfi.Width % 4; x; x--)
// #### DELETED ==== 0000031 $$$$ //				{
// #### DELETED ==== 0000031 $$$$ //					rIndex++;
// #### DELETED ==== 0000031 $$$$ //				}
// #### DELETED ==== 0000031 $$$$ //			}
// #### DELETED ==== 0000031 $$$$ //		}
// #### DELETED ==== 0000031 $$$$ //		if(!hiSign)
// #### DELETED ==== 0000031 $$$$ //			table->Reverse(); // 0 <= Bfi.Height ‚È‚çA‰º‚©‚çã (¶‚©‚ç‰E) ‚É•À‚ÔB
// #### DELETED ==== 0000031 $$$$ //	
// #### DELETED ==== 0000031 $$$$ //		delete colorPallet;
// #### DELETED ==== 0000031 $$$$ //		return table;
// #### DELETED ==== 0000031 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000032 $$$$ //	autoTable<uint> *readBmpFile_x(autoList<uchar> *fileData)
// #### DELETED ==== 0000032 $$$$ //	{
// #### DELETED ==== 0000032 $$$$ //		autoTable<uint> *out = readBmpFile_x(fileData);
// #### DELETED ==== 0000032 $$$$ //		delete fileData;
// #### DELETED ==== 0000032 $$$$ //		return out;
// #### DELETED ==== 0000032 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static uint GetSizeImage(uint xSize, uint ySize)
{
	return ((xSize * 3 + 3) / 4) * 4 * ySize;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeBmpFile(autoList<uchar> *fileData, autoTable<uint> *bmp)
{
	fileData->Clear();

	int w = bmp->GetWidth();
	int h = bmp->GetHeight();

	// Bfh
	fileData->AddElement('B');
	fileData->AddElement('M');
	writeUI32(fileData, GetSizeImage(w, h) + 0x36);
	writeUI32(fileData, 0); // Reserved_01 + Reserved_02
	writeUI32(fileData, 0x36);

	// Bfi
	writeUI32(fileData, 0x28);
	writeUI32(fileData, w);
	writeUI32(fileData, h);
	writeUI32(fileData, 0x00180001); // Planes + BitCount
	writeUI32(fileData, 0);
	writeUI32(fileData, GetSizeImage(w, h));
	writeUI32(fileData, 0);
	writeUI32(fileData, 0);
	writeUI32(fileData, 0);
	writeUI32(fileData, 0);

	for(int y = h - 1; 0 <= y; y--)
	{
		for(int x = 0; x < w; x++)
		{
			uint color = bmp->GetCell(x, y);
			uchar cR;
			uchar cG;
			uchar cB;

			cR = color >> 16;
			cG = color >> 8;
			cB = color;

			// BGR ’ˆÓ
			fileData->AddElement(cB);
			fileData->AddElement(cG);
			fileData->AddElement(cR);
		}
		for(int x = w % 4; x; x--)
		{
			fileData->AddElement(0x00);
		}
	}
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000033 $$$$ //	void writeBmpFile_x(autoList<uchar> *fileData, autoTable<uint> *bmp)
// #### DELETED ==== 0000033 $$$$ //	{
// #### DELETED ==== 0000033 $$$$ //		writeBmpFile(fileData, bmp);
// #### DELETED ==== 0000033 $$$$ //		delete bmp;
// #### DELETED ==== 0000033 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeBmpFile(char *file, autoTable<uint> *bmp)
{
	autoList<uchar> *fileData = new autoList<uchar>();
	writeBmpFile(fileData, bmp);
	writeAllBytes_cx(file, fileData);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void writeBmpFile_cx(char *file, autoTable<uint> *bmp)
{
	writeBmpFile(file, bmp);
	delete bmp;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000034 $$$$ //	void writeBmpFile_xx(char *file, autoTable<uint> *bmp)
// #### DELETED ==== 0000034 $$$$ //	{
// #### DELETED ==== 0000034 $$$$ //		writeBmpFile_cx(file, bmp);
// #### DELETED ==== 0000034 $$$$ //		memFree(file);
// #### DELETED ==== 0000034 $$$$ //	}
