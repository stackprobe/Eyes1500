//
// copied the source file by CopyLib.exe
//
enum
{
	MUS_DUMMY,

	// app >

	MUS_MAIN,
	MUS_BATTLE_1 = MUS_MAIN, // “¯‚¶‹È‚ðŽg‚¤B
	MUS_BATTLE_2,
	MUS_END,

	// < app

	MUS_MAX, // num of member
};

//
// copied the source file by CopyLib.exe
//
typedef struct MusicInfo_st
{
	int Handle;
	double Volume; // 0.0 - 1.0, def: 0.5
}
//
// copied the source file by CopyLib.exe
//
MusicInfo_t;

//
// copied the source file by CopyLib.exe
//
extern MusicInfo_t *CurrDestMusic;
//
// copied the source file by CopyLib.exe
//
extern double CurrDestMusicVolumeRate;

//
// copied the source file by CopyLib.exe
//
void MusicEachFrame(void);
//
// copied the source file by CopyLib.exe
//
void MusicPlay(int musId, int once_mode = 0, int resume_mode = 0, double volumeRate = 1.0, int fadeFrameMax = 30);
//
// copied the source file by CopyLib.exe
//
void MusicFade(int frameMax = 30, double destVRate = 0.0, double startVRate = CurrDestMusicVolumeRate);
//
// copied the source file by CopyLib.exe
//
void MusicStop(void);
//
// copied the source file by CopyLib.exe
//
void MusicTouch(int musId);
//
// copied the source file by CopyLib.exe
//
void UpdateMusicVolume(void);
