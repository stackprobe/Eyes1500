#include "all.h"

// ---- FontFile ----

//
// copied the source file by CopyLib.exe
//
static autoList<char *> *FontFileList;

//
// copied the source file by CopyLib.exe
//
static char *GetFontDir(void)
{
	static char *dir;

	if(!dir)
	{
		dir = combine(getAppTempDir(), "Font");
		createDir(dir);
	}
	return dir;
}
//
// copied the source file by CopyLib.exe
//
static void RemoveAllFontFile(void)
{
	while(FontFileList->GetCount())
	{
		errorCase(!RemoveFontResourceEx(FontFileList->UnaddElement(), FR_PRIVATE, NULL)); // ? ���s
	}
}
//
// copied the source file by CopyLib.exe
//
void AddFontFile(int etcId, char *localFile)
{
	char *file = combine(GetFontDir(), localFile);

	{
		autoList<uchar> *fileData = GetEtcRes()->GetHandle(etcId);
		writeFile(file, fileData);
	}

	GetEtcRes()->UnloadAllHandle(); // �e��S�~�J��

	LOG("AddFontResourceEx ST %u\n", (uint)time(NULL));
	errorCase(!AddFontResourceEx(file, FR_PRIVATE, NULL)); // ? ���s
	LOG("AddFontResourceEx ED %u\n", (uint)time(NULL));

	if(!FontFileList)
	{
		FontFileList = new autoList<char *>();
		GetFinalizers()->AddFunc(RemoveAllFontFile);
	}
	FontFileList->AddElement(file);
}

// ---- FontHandle ----

/*
	fontThick: 1 - 9, def == 6   -- ���� DxLib �̃\�[�X�� SetFontThickness() �����ăf�t�H�� 6 �������񂾂Ǝv���B
*/
//
// copied the source file by CopyLib.exe
//
FontHandle_t *CreateFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(m_isEmpty(fontName));
	errorCase(!m_isRange(fontSize, 1, IMAX));
	errorCase(!m_isRange(fontThick, 1, 9));
	// antiAliasing
	errorCase(!m_isRange(edgeSize, 0, IMAX));
	// italicFlag

	int h = CreateFontToHandle(
		fontName,
		fontSize,
		fontThick,
		antiAliasing ? DX_FONTTYPE_ANTIALIASING : DX_FONTTYPE_NORMAL,
		-1,
		edgeSize
		);

	errorCase(h == -1); // ? ���s

	FontHandle_t *fh = nb(FontHandle_t);
	fh->Handle = h;
	fh->FontName = strx(fontName);
	fh->FontSize = fontSize;
	fh->FontThick = fontThick;
	fh->AntiAliasing = antiAliasing;
	fh->EdgeSize = edgeSize;
	fh->ItalicFlag = italicFlag;
	return fh;
}
//
// copied the source file by CopyLib.exe
//
void ReleaseFontHandle(FontHandle_t *fh)
{
	if(!fh)
		return;

	errorCase(DeleteFontToHandle(fh->Handle)); // ? ���s
	memFree(fh->FontName);
	memFree(fh);
}

// ---- GetFontHandle ----

//
// copied the source file by CopyLib.exe
//
static oneObject(autoList<FontHandle_t *>, new autoList<FontHandle_t *>(), GetFontHandleList);

//
// copied the source file by CopyLib.exe
//
FontHandle_t *GetFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing, int edgeSize, int italicFlag)
{
	errorCase(!fontName);

	FontHandle_t *fh;

	for(int index = 0; index < GetFontHandleList()->GetCount(); index++)
	{
		fh = GetFontHandleList()->GetElement(index);

		if(
			!strcmp(fh->FontName, fontName) &&
			fh->FontSize == fontSize &&
			fh->FontThick == fontThick &&
			(fh->AntiAliasing ? antiAliasing : !antiAliasing) &&
			fh->EdgeSize == edgeSize &&
			(fh->ItalicFlag ? italicFlag : !italicFlag)
			)
		{
			goto found;
		}
	}
	fh = CreateFontHandle(fontName, fontSize, fontThick, antiAliasing, edgeSize, italicFlag);
	GetFontHandleList()->AddElement(fh);
//
// copied the source file by CopyLib.exe
//
found:
	return fh;
}
//
// copied the source file by CopyLib.exe
//
void ReleaseAllFontHandle(void)
{
	while(GetFontHandleList()->GetCount())
	{
		ReleaseFontHandle(GetFontHandleList()->UnaddElement());
	}
}

// ----

//
// copied the source file by CopyLib.exe
//
void DrawStringByFont(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag, int color, int edgeColor)
{
	errorCase(!str);
	errorCase(!fh);

	DrawStringToHandle(x, y, str, color, fh->Handle, edgeColor, tategakiFlag);
}
//
// copied the source file by CopyLib.exe
//
int GetDrawStringByFontWidth(char *str, FontHandle_t *fh, int tategakiFlag)
{
	errorCase(!str);
	errorCase(!fh);

	return GetDrawStringWidthToHandle(str, strlen(str), fh->Handle, tategakiFlag);
}
//
// copied the source file by CopyLib.exe
//
void DrawStringByFont_XCenter(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag, int color, int edgeColor)
{
	x -= GetDrawStringByFontWidth(str, fh, tategakiFlag) / 2;

	DrawStringByFont(x, y, str, fh, tategakiFlag, color, edgeColor);
}
