//
// copied the source file by CopyLib.exe
//
enum // SANWA Pad Btnno
{
	SNWPB_DIR_2,
	SNWPB_DIR_4,
	SNWPB_DIR_6,
	SNWPB_DIR_8,
	SNWPB_A1, // ���i��
	SNWPB_A2, // ���i��
	SNWPB_A3, // ���i�E
	SNWPB_B1, // ��i��
	SNWPB_B2, // ��i��
	SNWPB_B3, // ��i�E
	SNWPB_L,
	SNWPB_R,
	SNWPB_USTART, // ��X�^�[�g
	SNWPB_DSTART, // ���X�^�[�g
};

#define PAD_MAX 16
#define PAD_BUTTON_MAX 32

//
// copied the source file by CopyLib.exe
//
int GetPadCount(void);
//
// copied the source file by CopyLib.exe
//
void PadEachFrame(void);
//
// copied the source file by CopyLib.exe
//
int GetPadInput(int padId, int btnId);
//
// copied the source file by CopyLib.exe
//
int GetPadPound(int padId, int btnId);
