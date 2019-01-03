//
// copied the source file by CopyLib.exe
//
int LoadSound(autoList<uchar> *fileData);
//
// copied the source file by CopyLib.exe
//
int DuplSound(int h);
//
// copied the source file by CopyLib.exe
//
void UnloadSound(int h);

//
// copied the source file by CopyLib.exe
//
void SoundPlay(int h, int once_mode = 1, int resume_mode = 0);
//
// copied the source file by CopyLib.exe
//
void SetVolume(int h, double volume);
//
// copied the source file by CopyLib.exe
//
void SoundStop(int h);

//
// copied the source file by CopyLib.exe
//
double MixVolume(double volume1, double volume2);
