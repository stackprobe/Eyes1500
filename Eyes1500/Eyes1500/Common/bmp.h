//
// copied the source file by CopyLib.exe
//
autoTable<uint> *readBmpFile(autoList<uchar> *fileData);
//
// copied the source file by CopyLib.exe
//
autoTable<uint> *readBmpFile_x(autoList<uchar> *fileData);

//
// copied the source file by CopyLib.exe
//
void writeBmpFile(autoList<uchar> *fileData, autoTable<uint> *bmp);
//
// copied the source file by CopyLib.exe
//
void writeBmpFile_x(autoList<uchar> *fileData, autoTable<uint> *bmp);
//
// copied the source file by CopyLib.exe
//
void writeBmpFile(char *file, autoTable<uint> *bmp);
//
// copied the source file by CopyLib.exe
//
void writeBmpFile_cx(char *file, autoTable<uint> *bmp);
//
// copied the source file by CopyLib.exe
//
void writeBmpFile_xx(char *file, autoTable<uint> *bmp);

#define m_bmpColor(r, g, b) \
	((r) * 65536 + (g) * 256 + (b))
