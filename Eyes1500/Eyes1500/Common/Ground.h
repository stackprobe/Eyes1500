/*
 * copied the source file by CopyLib.exe
 *
 */
typedef struct Gnd_st
{
	taskList *EL; // EffectList
	int PrimaryPadId; // -1 == ���ݒ�
	SubScreen_t *MainScreen; // NULL == �s�g�p

	iRect_t Monitors[MONITOR_MAX];
	int MonitorNum;

	// app >

	// < app

	// SaveData {

	int RealScreen_W;
	int RealScreen_H;

	/*
		����
		0.0 - 1.0
		def: DEFAULT_VOLUME
	*/
	double MusicVolume;
	double SEVolume;

	/*
		-1 == ���蓖�ăi�V
		0 - (PAD_BUTTON_MAX - 1) == ���蓖�ă{�^��ID
		def: SNWPB_*
	*/
	struct PadBtnId_st
	{
		int Dir_2;
		int Dir_4;
		int Dir_6;
		int Dir_8;
		int A;
		int B;
		int C;
		int D;
		int E;
		int F;
		int L;
		int R;
		int Pause;
		int Start;
	}
	PadBtnId;

	struct PadBtnId_st KbdKeyId;

	int RO_MouseDispMode;

	// app >

	__int64 HiScore;

	// < app

	// }
}
/*
 * copied the source file by CopyLib.exe
 *
 */
Gnd_t;

/*
 * copied the source file by CopyLib.exe
 *
 */
extern Gnd_t Gnd;

/*
 * copied the source file by CopyLib.exe
 *
 */
void Gnd_INIT(void);
/*
 * copied the source file by CopyLib.exe
 *
 */
void Gnd_FNLZ(void);

/*
 * copied the source file by CopyLib.exe
 *
 */
void ImportSaveData(void);
/*
 * copied the source file by CopyLib.exe
 *
 */
void ExportSaveData(void);

/*
 * copied the source file by CopyLib.exe
 *
 */
void UnassignAllPadBtnId(void);
