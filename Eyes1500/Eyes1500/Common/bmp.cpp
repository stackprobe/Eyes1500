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
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/

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
