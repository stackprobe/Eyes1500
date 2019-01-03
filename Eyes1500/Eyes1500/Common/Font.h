/*
 * copied the source file by CopyLib.exe
 *
 */
void AddFontFile(int etcId, char *localFile);

// ---- FontHandle ----

/*
 * copied the source file by CopyLib.exe
 *
 */
typedef struct FontHandle_st
{
	int Handle;
	char *FontName;
	int FontSize;
	int FontThick;
	int AntiAliasing;
	int EdgeSize;
	int ItalicFlag;
}
/*
 * copied the source file by CopyLib.exe
 *
 */
FontHandle_t;

/*
 * copied the source file by CopyLib.exe
 *
 */
FontHandle_t *CreateFontHandle(char *fontName, int fontSize, int fontThick = 6, int antiAliasing = 1, int edgeSize = 0, int italicFlag = 0);
/*
 * copied the source file by CopyLib.exe
 *
 */
void ReleaseFontHandle(FontHandle_t *fh);

// ---- GetFontHandle ----

/*
 * copied the source file by CopyLib.exe
 *
 */
FontHandle_t *GetFontHandle(char *fontName, int fontSize, int fontThick, int antiAliasing = 1, int edgeSize = 0, int italicFlag = 0);
/*
 * copied the source file by CopyLib.exe
 *
 */
void ReleaseAllFontHandle(void);

// ----

/*
 * copied the source file by CopyLib.exe
 *
 */
void DrawStringByFont(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag = 0, int color = GetColor(255, 255, 255), int edgeColor = GetColor(0, 0, 0));
/*
 * copied the source file by CopyLib.exe
 *
 */
int GetDrawStringByFontWidth(char *str, FontHandle_t *fh, int tategakiFlag = 0);
/*
 * copied the source file by CopyLib.exe
 *
 */
void DrawStringByFont_XCenter(int x, int y, char *str, FontHandle_t *fh, int tategakiFlag = 0, int color = GetColor(255, 255, 255), int edgeColor = GetColor(0, 0, 0));
