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

		// ここから描画

		DrawWall();
		DrawCenter(P_CG_PAUSE, SCREEN_W / 2, SCREEN_H / 2);

		// EachFrame

		EachFrame();
	}
	FreezeInput();
}
static void RebornPlayer(void)
{
	// clear
	{
		zeroclear(&GDc.Player);

		GDc.LaserFrame = 0;
		GDc.FlashFrame = 0;
	}

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

		// ここから描画

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
			int frm = GDc.Player.BornFrame++ - 1; // 0〜
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
			double speed = 2.0;

			if(GDc.Player.HiSpeed)
				speed *= 3.0;

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

			plTama->Frame++; // ここで 1〜, 下のifのところでは Frame == 0, よって 0〜
			plTama->Y -= 10.0;

			if(plTama->Y < 0.0) // ? 画面外に出た。-> 開放
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

		for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
		{
			PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

			plMissile->Frame++;

			PlayerMissile_Move(plMissile);
			//plMissile->Y -= 5.0; // test

//			if(IsOutOfScreen(plMissile->X, plMissile->Y)) // ? 画面外に出た。-> 開放
			if(plMissile->Y < 0.0 || SCREEN_H < plMissile->Y) // ? 画面上下から外に出た。-> 開放
			{
				ReleasePlayerMissile(plMissile);
				GDc.PlayerMissileList->FastDesertElement(index);
				index--;
			}
		}
		if(GetInput(INP_E) == 1) // Missile
		{
			GDc.PlayerMissileList->AddElement(CreatePlayerMissile(GDc.Player.X, GDc.Player.Y - 16.0));
			SEPlay(SE_MISSILE);
		}

		if(GetInput(INP_C)) // Laser
		{
			m_maxim(GDc.LaserFrame, 0);
			GDc.LaserFrame++;
		}
		else
		{
			GDc.LaserFrame = 1 <= GDc.LaserFrame ? -1 : 0;
		}

		if(1 <= GDc.LaserFrame)
		{
			int frm = GDc.LaserFrame - 1; // 0〜

			if(frm % 65 == 0)
			{
				SEPlay(SE_LASER);
			}
		}
		else if(GDc.LaserFrame == -1)
		{
			SEStop(SE_LASER);
		}

		if(1 <= GDc.FlashFrame) // Flash
		{
			int frm = GDc.FlashFrame++ - 1; // 0〜

			if(frm == 300) // 照射終了
			{
				GDc.FlashFrame = 0;
			}
		}
		else
		{
			if(GetInput(INP_D) == 1) // 照射開始
			{
				GDc.FlashFrame = 1;

				AddCommonEffect(
					Gnd.EL,
					1,
					P_WEAPON_LASER_B,
					SCREEN_W / 2,
					SCREEN_H / 2,
					0.0,
					1.0,
					0.8,
					0.0,
					0.0,
					0.0,
					0.0,
					-0.004
					);

				SEPlay(SE_LASER_B);
			}
		}

		if(GetInput(INP_A) == 1) // 高速移動
		{
			GDc.Player.HiSpeed = m_10(GDc.Player.HiSpeed);
		}

		// 敵_処理

		for(int index = 0; index < GDc.EnemyList->GetCount(); index++) // 敵_移動
		{
			Enemy_t *i = GDc.EnemyList->GetElement(index);

			if(EnemyEachFrame(i)) // ? 消滅
			{
				ReleaseEnemy(i);
				GDc.EnemyList->SetElement(index, NULL);
			}
		}
		GDc.EnemyList->MultiDiscard(isPointNull);

		// zantei
		if(dRnd() < 0.01)
		{
			GDc.EnemyList->AddElement(CreateEnemy(EK_EYE_1, dRnd() * SCREEN_W, -10.0));
		}

		// ★★★ ここから描画 ★★★

		DrawWall();

		// 自弾

		for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
		{
			PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

			DrawCenter(D_WEAPON_SHOT_00 + plTama->Frame / 6 % 4 | DTP, plTama->X, plTama->Y);
		}
		for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
		{
			PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

			DrawBegin(D_WEAPON_MISSILE_00 + plMissile->Frame / 6 % 4 | DTP, plMissile->X, plMissile->Y);
			DrawRotate(plMissile->Dir + PI / 2.0);
			DrawEnd();
		}
		if(1 <= GDc.LaserFrame)
		{
			double x = GDc.Player.RealX;
			double y = GDc.Player.RealY - 16.0;

			int iX = d2i(x);
			int iY = d2i(y);

			DrawRect(D_WEAPON_LASER_00 + ProcFrame / 6 % 2 | DTP, iX - 1, iY -  600, 2, 600);
			DrawRect(D_WEAPON_LASER_00 + ProcFrame / 6 % 2 | DTP, iX - 1, iY - 1200, 2, 600);
		}

		// Player
		{
			double x = GDc.Player.RealX;
			double y = GDc.Player.RealY;

			int iX = d2i(x);
			int iY = d2i(y);

			if(GDc.Player.BornFrame)
				DPE_SetAlpha(0.5);

			DrawCenter((D_CHARA_PLAYER_00 + (ProcFrame / 6) % 2) | DTP, iX, iY);
			DPE_Reset();
		}

		// 敵

		for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
		{
			DrawEnemy(GDc.EnemyList->GetElement(index));
		}

		// ★★★ EachFrame ★★★

		EachFrame();
	}
	FreezeInput();
//	MusicFade(); // 同じ曲なので

	forscene(20)
	{
		DrawWall();
		EachFrame();
	}
	sceneLeave();

	FreezeInput();
}
