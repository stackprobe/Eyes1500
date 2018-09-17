#include "all.h"

static void DrawWall(void)
{
	DrawRect(P_CG_STAGE, 0, 0, SCREEN_W, SCREEN_H);
}
static void PauseMain(void)
{
	FreezeInput();

	for(; ; )
	{
		if(GetInput(INP_PAUSE) == 1)
			break;

		// ‚±‚±‚©‚ç•`‰æ

		DrawCenter(P_CG_PAUSE, SCREEN_W / 2, SCREEN_H / 2);

		// EachFrame

		EachFrame();
	}
	FreezeInput();
}
static void RebornPlayer(void)
{
	GDc.Player.BornFrame = 1;
	GDc.Player.X = SCREEN_W / 2;
	GDc.Player.Y = SCREEN_H - 50;
	GDc.Player.RealX = SCREEN_W / 2;
	GDc.Player.RealY = SCREEN_H;
}
void GameMain(void)
{
	SetCurtain();
	FreezeInput();

	forscene(10)
	{
		DrawWall();

		for(int xSft = -1; xSft <= 1; xSft += 2)
		for(int ySft = -1; ySft <= 1; ySft += 2)
		{
			double x = SCREEN_W / 2.0 + xSft * 40.0 * (1.0 - sc_rate);
			double y = SCREEN_H / 2.0 + ySft * 40.0 * (1.0 - sc_rate);

			DPE_SetAlpha(0.5);
			DrawCenter(D_CG_MESSAGE_00 | DTP, x, y);
			DPE_Reset();
		}

		EachFrame();
	}
	sceneLeave();

	FreezeInput();

	for(; ; )
	{
		if(
			GetInput(INP_PAUSE) == 1 ||
			GetInput(INP_A) == 1 ||
			GetInput(INP_B) == 1 ||
			GetInput(INP_C) == 1 ||
			GetInput(INP_D) == 1 ||
			GetInput(INP_E) == 1 ||
			GetInput(INP_F) == 1
			)
			break;

		// ‚±‚±‚©‚ç•`‰æ

		DrawWall();
		DrawCenter(D_CG_MESSAGE_00 | DTP, SCREEN_W / 2, SCREEN_H / 2);

		// EachFrame

		EachFrame();
	}

	for(int xSft = -1; xSft <= 1; xSft += 2)
	for(int ySft = -1; ySft <= 1; ySft += 2)
	{
		AddCommonEffect(
			Gnd.EL,
			1,
			D_CG_MESSAGE_00 | DTP,
			SCREEN_W / 2.0,
			SCREEN_H / 2.0,
			0.0,
			1.0,
			0.5,
			xSft * 4.0,
			ySft * 4.0,
			0.0,
			0.0,
			-0.05
			);
	}

	MusicPlay(MUS_BATTLE_1);
	FreezeInput();

	RebornPlayer();

	for(; ; )
	{
		if(GetInput(INP_PAUSE) == 1)
		{
			PauseMain();
		}

		double playerRealXYApproachRate = 0.0;

		if(GDc.Player.BornFrame)
		{
			int frm = GDc.Player.BornFrame++ - 1; // 0`
			const int FRM_MAX = 40;
			double frmRate = (double)frm / FRM_MAX;
			double frmRevRate = 1.0 - frmRate;

			if(frm == FRM_MAX)
			{
				GDc.Player.BornFrame = 0;
				goto endBornPlayer;
			}
			playerRealXYApproachRate = frmRevRate;
		}
endBornPlayer:

		{
			double speed = 4.0;

			if(1 <= GetInput(INP_DIR_2))
			{
				GDc.Player.Y += speed;
			}
			if(1 <= GetInput(INP_DIR_4))
			{
				GDc.Player.X -= speed;
			}
			if(1 <= GetInput(INP_DIR_6))
			{
				GDc.Player.X += speed;
			}
			if(1 <= GetInput(INP_DIR_8))
			{
				GDc.Player.Y -= speed;
			}
		}

		m_range(GDc.Player.X, 0.0, SCREEN_W);
		m_range(GDc.Player.Y, 0.0, SCREEN_H);

		m_approach(GDc.Player.RealX, GDc.Player.X, playerRealXYApproachRate);
		m_approach(GDc.Player.RealY, GDc.Player.Y, playerRealXYApproachRate);

		for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
		{
			PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

			plTama->Frame++;
			plTama->Y -= 10.0;

			if(plTama->Y < 0.0) // ? ‰æ–ÊŠO‚Éo‚½B-> ŠJ•ú
			{
				ReleasePlayerTama(plTama);
				GDc.PlayerTamaList->FastDesertElement(index);
				index--;
			}
		}

		if(GetInput(INP_B) == 1) // Shot
		{
			GDc.PlayerTamaList->AddElement(CreatePlayerTama(GDc.Player.X, GDc.Player.Y - 16.0));
			SEPlay(SE_SHOT);
		}

		// ‚±‚±‚©‚ç•`‰æ

		DrawWall();

		for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
		{
			PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

			DrawCenter(D_WEAPON_SHOT_00 + plTama->Frame % 4 | DTP, plTama->X, plTama->Y);
		}

		// Player•`‰æ
		{
			double x;
			double y;

			if(GDc.Player.BornFrame)
			{
				x = GDc.Player.RealX;
				y = GDc.Player.RealY;

				DPE_SetAlpha(0.5);
			}
			else
			{
				x = GDc.Player.X;
				y = GDc.Player.Y;
			}
			int iX = d2i(x);
			int iY = d2i(y);

			DrawCenter((D_CHARA_PLAYER_00 + (ProcFrame / 6) % 2) | DTP, iX, iY);
			DPE_Reset();
		}

		// EachFrame

		EachFrame();
	}
	FreezeInput();
//	MusicFade(); // “¯‚¶‹È‚È‚Ì‚Å

	forscene(20)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	FreezeInput();
}
