#include "all.h"

static void FontTest(void)
{
	DrawCurtain();
	EachFrame();

	for(; ; )
	{
		if(GetInput(INP_A))
			break;

		DrawCurtain();

		DrawStringByFont(
			10, 10,
			"�b�菬����",
			GetFontHandle("���E����", 70, 6, 1, 2),
			0,
			GetColor(0, 0, 0),
			GetColor(255, 255, 255)
			);

		DrawStringByFont(
			10, 150,
			"game start",
			GetFontHandle("�肢�Ă����M", 50, 6, 1, 2),
			0,
			GetColor(0, 0, 0),
			GetColor(255, 0, 0)
			);

		EachFrame();
	}
}
void ProcMain(void)
{
#if !LOG_ENABLED
TitleMenu(); // test
	//error(); // TODO
#elif 0 // test
	GameInit();
	GameMain();
	GameFnlz();
#elif 1 // test
	TitleMenu();
#elif 0 // test
	FontTest();
#elif 0 // test
	error(); // todo
#else
	error(); // todo
#endif
}
