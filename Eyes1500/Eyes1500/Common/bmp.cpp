#include "all.h"

//
// copied the source file by CopyLib.exe
//
static struct
{
	uint16 Type;
	uint Size;
	uint16 Reserved_01;
	uint16 Reserved_02;
	uint OffBits;
}
//
// copied the source file by CopyLib.exe
//
Bfh;

//
// copied the source file by CopyLib.exe
//
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
//
// copied the source file by CopyLib.exe
//
Bfi;

//
// copied the source file by CopyLib.exe
//
autoTable<uint> *readBmpFile(autoList<uchar> *fileData)
{
	autoTable<uint> *table = new autoTable<uint>(getUIZero, noop_ui);
	autoList<uint> *colorPallet = new autoList<uint>();
	int rIndex = 0;
	uint colPalCnt;
	uint x;
	uint y;
	uint hiSign;

	Bfh.Type = readUI32(fileData, rIndex, 2); // 'BM'
	Bfh.Size = readUI32(fileData, rIndex);
	Bfh.Reserved_01 = (uint)readUI32(fileData, rIndex, 2);
	Bfh.Reserved_02 = (uint)readUI32(fileData, rIndex, 2);
	Bfh.OffBits = readUI32(fileData, rIndex);

	Bfi.Size = readUI32(fileData, rIndex);
	Bfi.Width = readUI32(fileData, rIndex);
	Bfi.Height = readUI32(fileData, rIndex);
	Bfi.Planes = (uint)readUI32(fileData, rIndex, 2);
	Bfi.BitCount = (uint)readUI32(fileData, rIndex, 2);
	Bfi.Compression = readUI32(fileData, rIndex);
	Bfi.SizeImage = readUI32(fileData, rIndex);
	Bfi.XPelsPerMeter = readUI32(fileData, rIndex);
	Bfi.YPelsPerMeter = readUI32(fileData, rIndex);
	Bfi.ClrUsed = readUI32(fileData, rIndex);
	Bfi.ClrImportant = readUI32(fileData, rIndex);

	errorCase(Bfh.Type != ('B' | 'M' << 8));

	hiSign = 0x80000000 & Bfi.Height;

	if(hiSign)
		Bfi.Height = (Bfi.Height ^ 0xffffffff) + 1;

	errorCase(!Bfi.Width);
	errorCase(!Bfi.Height);
	errorCase(IMAX / Bfi.Width < Bfi.Height);

	table->Resize(Bfi.Width, Bfi.Height);

	switch(Bfi.BitCount)
	{
	case 1: colPalCnt = 2; break;
	case 4: colPalCnt = 16; break;
	case 8: colPalCnt = 256; break;
	case 24:
		colPalCnt = 0;
		break;

	default:
		error();
	}
	while(colPalCnt)
	{
		uchar cR;
		uchar cG;
		uchar cB;

		// BGR 注意
		cB = fileData->GetElement(rIndex++);
		cG = fileData->GetElement(rIndex++);
		cR = fileData->GetElement(rIndex++);
		rIndex++; // reserved

		colorPallet->AddElement(cR << 16 | cG << 8 | cB);
		colPalCnt--;
	}
	for(y = 0; y < Bfi.Height; y++)
	{
		if(Bfi.BitCount <= 8)
		{
			uint bitMax = 8 / Bfi.BitCount;
			uint bit;

			x = 0;

			while(x < Bfi.Width)
			{
				uchar c8 = fileData->GetElement(rIndex++);

				for(bit = bitMax; bit && x < Bfi.Width; bit--, x++)
				{
					table->SetCell(x, y, colorPallet->GetElement(c8 & (1 << Bfi.BitCount) - 1));
					c8 >>= Bfi.BitCount;
				}
			}
			for(x = (4 - ((Bfi.Width + bitMax - 1) / bitMax) % 4) % 4; x; x--)
			{
				rIndex++;
			}
		}
		else
		{
			for(x = 0; x < Bfi.Width; x++)
			{
				uchar cR;
				uchar cG;
				uchar cB;

				// BGR 注意
				cB = fileData->GetElement(rIndex++);
				cG = fileData->GetElement(rIndex++);
				cR = fileData->GetElement(rIndex++);

				table->SetCell(x, y, cR << 16 | cG << 8 | cB);
			}
			for(x = Bfi.Width % 4; x; x--)
			{
				rIndex++;
			}
		}
	}
	if(!hiSign)
		table->Reverse(); // 0 <= Bfi.Height なら、下から上 (左から右) に並ぶ。

	delete colorPallet;
	return table;
}
//
// copied the source file by CopyLib.exe
//
autoTable<uint> *readBmpFile_x(autoList<uchar> *fileData)
{
	autoTable<uint> *out = readBmpFile_x(fileData);
	delete fileData;
	return out;
}

//
// copied the source file by CopyLib.exe
//
static uint GetSizeImage(uint xSize, uint ySize)
{
	return ((xSize * 3 + 3) / 4) * 4 * ySize;
}
//
// copied the source file by CopyLib.exe
//
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

			// BGR 注意
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
//
// copied the source file by CopyLib.exe
//
void writeBmpFile_x(autoList<uchar> *fileData, autoTable<uint> *bmp)
{
	writeBmpFile(fileData, bmp);
	delete bmp;
}
//
// copied the source file by CopyLib.exe
//
void writeBmpFile(char *file, autoTable<uint> *bmp)
{
	autoList<uchar> *fileData = new autoList<uchar>();
	writeBmpFile(fileData, bmp);
	writeFile_cx(file, fileData);
}
//
// copied the source file by CopyLib.exe
//
void writeBmpFile_cx(char *file, autoTable<uint> *bmp)
{
	writeBmpFile(file, bmp);
	delete bmp;
}
//
// copied the source file by CopyLib.exe
//
void writeBmpFile_xx(char *file, autoTable<uint> *bmp)
{
	writeBmpFile_cx(file, bmp);
	memFree(file);
}
