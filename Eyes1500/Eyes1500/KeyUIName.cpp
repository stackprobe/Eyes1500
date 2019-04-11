#include "all.h"

typedef struct KeyUIName_st
{
	int KeyId;
	char *Name;
}
KeyUIName_t;

static KeyUIName_t KeyUINames[] =
{
	{ 0x0E, "BS" },
	{ 0x0F, "Tab" },
	{ 0x1C, "Enter" },
	{ 0x2A, "左Shift" },
	{ 0x36, "右Shift" },
	{ 0x1D, "左Ctrl" },
	{ 0x9D, "右Ctrl" },
	{ 0x01, "Esc" },
	{ 0x39, "Space" },
	{ 0xC9, "PgUp" },
	{ 0xD1, "PgDown" },
	{ 0xCF, "End" },
	{ 0xC7, "Home" },
	{ 0xCB, "←" },
	{ 0xC8, "↑" },
	{ 0xCD, "→" },
	{ 0xD0, "↓" },
	{ 0xD2, "Ins" },
	{ 0xD3, "Del" },
	{ 0x0C, "[-]" },
	{ 0x7D, "[\\]" },
	{ 0x90, "[^]" },
	{ 0x34, "[.]" },
	{ 0x35, "[/]" },
	{ 0x38, "左Alt" },
	{ 0xB8, "右Alt" },
	{ 0x46, "ScLock" },
	{ 0x27, "[;]" },
	{ 0x92, "[:]" },
	{ 0x1A, "[[]" },
	{ 0x1B, "[]]" },
	{ 0x91, "[@]" },
	{ 0x2B, "[_]" },
	{ 0x33, "[,]" },
	{ 0x94, "KNJ" },
	{ 0x79, "HK" },
	{ 0x7B, "MHK" },
	{ 0x70, "Kana" },
	{ 0xDD, "App" },
	{ 0x3A, "Casp" },
	{ 0xB7, "PrScr" },
	{ 0xC5, "PsBrk" },
	{ 0xDB, "左Win" },
	{ 0xDC, "右Win" },
	{ 0x45, "T-NumLock" },
	{ 0x52, "T-0" },
	{ 0x4F, "T-1" },
	{ 0x50, "T-2" },
	{ 0x51, "T-3" },
	{ 0x4B, "T-4" },
	{ 0x4C, "T-5" },
	{ 0x4D, "T-6" },
	{ 0x47, "T-7" },
	{ 0x48, "T-8" },
	{ 0x49, "T-9" },
	{ 0x37, "T-*" },
	{ 0x4E, "T-+" },
	{ 0x4A, "T--" },
	{ 0x53, "T-." },
	{ 0xB5, "T-/" },
	{ 0x9C, "T-Enter" },
	{ 0x3B, "F01" },
	{ 0x3C, "F02" },
	{ 0x3D, "F03" },
	{ 0x3E, "F04" },
	{ 0x3F, "F05" },
	{ 0x40, "F06" },
	{ 0x41, "F07" },
	{ 0x42, "F08" },
	{ 0x43, "F09" },
	{ 0x44, "F10" },
	{ 0x57, "F11" },
	{ 0x58, "F12" },
	{ 0x1E, "[A]" },
	{ 0x30, "[B]" },
	{ 0x2E, "[C]" },
	{ 0x20, "[D]" },
	{ 0x12, "[E]" },
	{ 0x21, "[F]" },
	{ 0x22, "[G]" },
	{ 0x23, "[H]" },
	{ 0x17, "[I]" },
	{ 0x24, "[J]" },
	{ 0x25, "[K]" },
	{ 0x26, "[L]" },
	{ 0x32, "[M]" },
	{ 0x31, "[N]" },
	{ 0x18, "[O]" },
	{ 0x19, "[P]" },
	{ 0x10, "[Q]" },
	{ 0x13, "[R]" },
	{ 0x1F, "[S]" },
	{ 0x14, "[T]" },
	{ 0x16, "[U]" },
	{ 0x2F, "[V]" },
	{ 0x11, "[W]" },
	{ 0x2D, "[X]" },
	{ 0x15, "[Y]" },
	{ 0x2C, "[Z]" },
	{ 0x0B, "[0]" },
	{ 0x02, "[1]" },
	{ 0x03, "[2]" },
	{ 0x04, "[3]" },
	{ 0x05, "[4]" },
	{ 0x06, "[5]" },
	{ 0x07, "[6]" },
	{ 0x08, "[7]" },
	{ 0x09, "[8]" },
	{ 0x0A, "[9]" },
};

char *KeyIdToUIName(int keyId)
{
	for(int index = 0; index < lengthof(KeyUINames); index++)
		if(KeyUINames[index].KeyId == keyId)
			return KeyUINames[index].Name;

	return NULL;
}
char *x_KeyIdToUIName(int keyId)
{
	char *ret = KeyIdToUIName(keyId);

	if(ret)
		ret = strx(ret);

	return ret;
}
