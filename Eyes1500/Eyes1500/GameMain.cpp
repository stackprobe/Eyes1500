#include "all.h"

static void DrawWall(void)
{
	DrawRect(P_CG_STAGE, 0, 0, SCREEN_W, SCREEN_H);
}
static void PauseMain(void)
{
	Gnd.EL->Clear();
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
	int hs = GDc.Player.HiSpeed;

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
	GDc.Player.HiSpeed = hs;
	GDc.Player.HP = PLAYER_HP_MAX;

	if(!GDc.BattleStarted && GDc.StageIndex) // ? 前のステージからこのステージへ来たところ。
	{
		GDc.Player.BornFrame = 0;
		GDc.Player.X = GDcNV.X;
		GDc.Player.Y = GDcNV.Y;
		GDc.Player.RealX = GDcNV.X;
		GDc.Player.RealY = GDcNV.Y;
	}
}
static void DrawScore(int onBattle)
{
	m_approach(GDcNV.ScoreDisp, GDcNV.Score, 0.666);

	__int64 iScoreDisp = d2i64(GDcNV.ScoreDisp);

	// Score
	{
		char *str = xcout("%09I64d", abs(iScoreDisp));
		int iro;

		str = thousandComma(str);

		if(iScoreDisp < 0)
			str = insertChar(str, 0, '-');

		str = insertChar(str, 0, '\\');

		if(iScoreDisp < 0)
		{
			if(onBattle)
				iro = GetColor(255, 0, 0);
			else
				iro = GetColor(255, 255, 0);
		}
		else
			iro = GetColor(255, 255, 255);

		DrawStringByFont_XCenter(
			SCREEN_W / 2,
			1,
			str,
			APP_COMMON_FONT_HANDLE,
			0,
			iro
			);

		memFree(str);
	}

	if(1 <= GDcNV.DeficitFrame) // 赤字カウンタ
	{
		int frm = GDcNV.DeficitFrame; // 1～
		int counter = DEFICIT_SEC_MAX - frm / 60;
		m_range(counter, 0, DEFICIT_SEC_MAX);

		char *str = xcout("%d", counter);
		int iro;

		if(onBattle)
			iro = GetColor(255, 0, 0);
		else
			iro = GetColor(255, 255, 0);

		DrawStringByFont_XCenter(
			SCREEN_W / 2,
			30,
			str,
			GetFontHandle(APP_COMMON_FONT, 48, 6),
			0,
			iro
			);

		memFree(str);
	}
}
static void PlayerDamaged(void)
{
	GDc.Player.HP--;

	if(0 < GDc.Player.HP)
	{
		SEPlay(SE_DAMAGE);

		GDc.Player.DamagedFrame = 1;
	}
	else
	{
		SEPlay(SE_DAMAGE);

		GDc.Player.DeadFrame = 1;
	}
	GDcNV.NoDamage = 0;
}
void GameMain(void)
{
/*
LOGPOS();
GetEnemyInfo(EK_EYE_1); // test
LOGPOS();
GetStageCount(); // test
LOGPOS();
*/

	SetCurtain();
	FreezeInput();

	int messagePicId = D_CG_MESSAGE_00 + m_01(GDc.StageIndex) | DTP;

	forscene(10)
	{
		DrawWall();

		for(int xSft = -1; xSft <= 1; xSft += 2)
		for(int ySft = -1; ySft <= 1; ySft += 2)
		{
			double x = SCREEN_W / 2.0 + xSft * 40.0 * (1.0 - sc_rate);
			double y = SCREEN_H / 2.0 + ySft * 40.0 * (1.0 - sc_rate);

			DPE_SetAlpha(0.5);
			DrawCenter(messagePicId, x, y);
			DPE_Reset();
		}

		if(GDc.StageIndex) // ? 前のステージからこのステージへ来た。
		{
			DrawBegin(D_CHARA_PLAYER_00 | DTP, GDcNV.X, GDcNV.Y);
			DrawRotate(sc_rate * PI * 2.0);
			DrawEnd();
		}

		DrawScore(0);

		EachFrame();
	}
	sceneLeave();

#if 1
	AddEnemyByStageIndex(GDc.StageIndex);
#else // 敵の配置テスト
	{
		GDc.EnemyList->AddElement(CreateEnemy(EK_EYE_1, 100, 100));
		GDc.EnemyList->AddElement(CreateEnemy(EK_EYE_1, 240, 200));
		GDc.EnemyList->AddElement(CreateEnemy(EK_EYE_1, 380, 100));
	}
#endif

	FreezeInput();

	// start...

	RebornPlayer();
	GDc.Player.HiSpeed = GDcNV.HiSpeed;

	errorCase(!m_isRange(GDcNV.HP, 0, PLAYER_HP_MAX));
	LOG("GDcNV.HP=%d\n", GDcNV.HP);
	if(GDcNV.HP != 0)
		GDc.Player.HP = GDcNV.HP;

	goto start;

restart:
	RebornPlayer();

start:
	for(; ; )
	{
		if(!GDc.BattleStarted)
		{
			GDc.BattleNotStartedFrame++;

			if(BATTLE_START_FRAME < GDc.BattleNotStartedFrame)
			/*
			if(BATTLE_STARTABLE_FRAME < GDc.BattleNotStartedFrame) // いきなりスタートしてしまわないように。
			if(
				GetInput(INP_PAUSE) == 1 ||
//				GetInput(INP_A) == 1 || // 高速移動は反応させない。
				GetInput(INP_B) == 1 ||
				GetInput(INP_C) == 1 ||
				GetInput(INP_D) == 1 ||
				GetInput(INP_E) == 1 ||
				GetInput(INP_F) == 1
				)
				*/
			{
				GDc.BattleStarted = 1;

				for(int xSft = -1; xSft <= 1; xSft += 2)
				for(int ySft = -1; ySft <= 1; ySft += 2)
				{
					AddCommonEffect(
						Gnd.EL,
						1,
						messagePicId,
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
			}
		}
		else
		{
			if(GetInput(INP_PAUSE) == 1)
			{
				PauseMain();
			}
		}

		// デバッグ用
		{
			if(GetKeyInput(KEY_INPUT_ADD) == 1)
			{
				GDcNV.Score += 10000000;
			}
		}

		double playerRealXYApproachRate = 0.0;

		if(GDc.Player.BornFrame)
		{
			int frm = GDc.Player.BornFrame++ - 1; // 0～
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

		if(GDc.Player.DamagedFrame)
		{
			int frm = GDc.Player.DamagedFrame++ - 1; // 0～
			const int FRM_MAX = 120;
			double frmRate = (double)frm / FRM_MAX;
			double frmRevRate = 1.0 - frmRate;

			if(frm == FRM_MAX)
			{
				GDc.Player.DamagedFrame = 0;
				goto endDamagedPlayer;
			}
			// ダメージ中の処理ここへ追加
		}
endDamagedPlayer:

		double playerDeadRate = 0.0;
		double playerDeadRevRate = 0.0;

		if(GDc.Player.DeadFrame)
		{
			int frm = GDc.Player.DeadFrame++ - 1; // 0～
			const int FRM_MAX = 120;
			double frmRate = (double)frm / FRM_MAX;
			double frmRevRate = 1.0 - frmRate;

			playerDeadRate = frmRate;
			playerDeadRevRate = frmRevRate;

			if(frm == FRM_MAX)
			{
				GDc.Player.DeadFrame = 0;

				if(GDc.GameOver)
					break;

				GDcNV.Score -= 2000000; // 経費_再戦
				goto restart;
			}
			// 被弾中の処理ここへ追加
		}

		int uncontrollable = GDc.Player.DamagedFrame || GDc.Player.DeadFrame;

		if(!uncontrollable)
		{
			double speed = 2.0;
			int moved = 0;

			if(GDc.Player.HiSpeed)
				speed *= 3.0;

			if(1 <= GetInput(INP_DIR_2))
			{
				GDc.Player.Y += speed;
				moved = 1;
			}
			if(1 <= GetInput(INP_DIR_4))
			{
				GDc.Player.X -= speed;
				moved = 1;
			}
			if(1 <= GetInput(INP_DIR_6))
			{
				GDc.Player.X += speed;
				moved = 1;
			}
			if(1 <= GetInput(INP_DIR_8))
			{
				GDc.Player.Y -= speed;
				moved = 1;
			}
			if(1 <= GetInput(INP_F)) // 自爆
			{
				SEPlay(SE_DAMAGE);

				GDc.Player.DeadFrame = 1;
				GDc.GameOver = 1;
			}

			if(moved)
			{
				if(GDc.Player.HiSpeed)
					GDcNV.Score -= 10000 / 60; // 経費_移動
				else
					GDcNV.Score -= 50000 / 60; // 経費_高速移動
			}
		}

		m_range(GDc.Player.X, 0.0, SCREEN_W);
		m_range(GDc.Player.Y, 0.0, SCREEN_H);

		m_approach(GDc.Player.RealX, GDc.Player.X, playerRealXYApproachRate);
		m_approach(GDc.Player.RealY, GDc.Player.Y, playerRealXYApproachRate);

		for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
		{
			PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

			int frm = plTama->Frame++; // frm == 0～
			plTama->Y -= 10.0;

			if(plTama->Y < 0.0) // ? 画面外に出た。-> 開放
			{
				ReleasePlayerTama(plTama);
				GDc.PlayerTamaList->FastDesertElement(index);
				index--;
			}
		}
		if(!uncontrollable && GDc.BattleStarted && GetInput(INP_B) == 1) // Shot
		{
			GDc.PlayerTamaList->AddElement(CreatePlayerTama(GDc.Player.X, GDc.Player.Y - 16.0));
			SEPlay(SE_SHOT);
			GDcNV.Score -= 20000; // 経費_弾丸
		}

		for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
		{
			PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

			int frm = plMissile->Frame++; // frm == 0～

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
		if(!uncontrollable && GDc.BattleStarted && GetInput(INP_E) == 1) // Missile
		{
			GDc.PlayerMissileList->AddElement(CreatePlayerMissile(GDc.Player.X, GDc.Player.Y - 16.0));
			SEPlay(SE_MISSILE);
			GDcNV.Score -= 100000; // 経費_誘導ミサイル
		}

		if(!uncontrollable && GDc.BattleStarted && 1 <= GetInput(INP_C)) // Laser
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
			int frm = GDc.LaserFrame - 1; // frm == 0～

			if(frm % 65 == 0)
			{
				SEPlay(SE_LASER);
			}
			GDcNV.Score -= 500000 / 60; // 経費_レーザー光線
		}
		else if(GDc.LaserFrame == -1)
		{
			SEStop(SE_LASER);
		}

		if(1 <= GDc.FlashFrame) // Flash(Laser_B)
		{
			int frm = GDc.FlashFrame++ - 1; // frm == 0～

			if(frm == 0) // 照射開始
			{
				AllEnemy_AntiHaritsuki();
				GDcNV.Score -= 500000; // 経費_目潰しレーザー
			}
			if(frm == 300) // 照射終了
			{
				GDc.FlashFrame = 0;
			}
		}
		else
		{
			if(!uncontrollable && GDc.BattleStarted && GetInput(INP_D) == 1) // 照射開始
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

		if(!uncontrollable && GetInput(INP_A) == 1) // 高速移動
		{
			GDc.Player.HiSpeed = m_10(GDc.Player.HiSpeed);
		}

		if(!GDc.BattleStarted)
			goto startDraw;

		if(GDc.EnemyList->GetCount() || GDc.Player.DeadFrame)
			GDc.NoEnemyFrame = 0;
		else
			GDc.NoEnemyFrame++;

		if(90 < GDc.NoEnemyFrame)
		{
			GDc.WillNextStage = 1;
			break;
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

#if 0 // 敵_出現
		if(dRnd() < 0.01)
		{
			GDc.EnemyList->AddElement(CreateEnemy(EK_EYE_1, dRnd() * SCREEN_W, -10.0));
		}
#endif

		// 敵弾_処理

		for(int index = 0; index < GDc.EnemyTamaList->GetCount(); index++)
		{
			EnemyTama_t *i = GDc.EnemyTamaList->GetElement(index);

			if(EnemyTamaEachFrame(i)) // ? 消滅
			{
				ReleaseEnemyTama(i);
				GDc.EnemyTamaList->SetElement(index, NULL);
			}
		}
		GDc.EnemyTamaList->MultiDiscard(isPointNull);

		// 敵弾爆風_処理

		for(int index = 0; index < GDc.EnemyTamaBlastList->GetCount(); index++)
		{
			EnemyTamaBlast_t *i = GDc.EnemyTamaBlastList->GetElement(index);

			if(EnemyTamaBlastEachFrame(i)) // ? 消滅
			{
				ReleaseEnemyTamaBlast(i);
				GDc.EnemyTamaBlastList->SetElement(index, NULL);
			}
		}
		GDc.EnemyTamaBlastList->MultiDiscard(isPointNull);

		// Crash ここから

		for(int enemyIndex = 0; enemyIndex < GDc.EnemyList->GetCount(); enemyIndex++)
		{
			Enemy_t *enemy = GDc.EnemyList->GetElement(enemyIndex);
			int enemyDamaged = 0;

			// Crash -- Shot / 敵

			for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
			{
				PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

				if(IsCrashed_Circle_Rect(
					plTama->X, plTama->Y, PLAYER_SHOT_CRASH_R,
					GetEnemyAtari_L(enemy), GetEnemyAtari_T(enemy), GetEnemyAtari_R(enemy), GetEnemyAtari_B(enemy)
					))
				{
					SEPlay(SE_DAMAGE_E);

					enemy->HP -= 10;
					enemyDamaged = 1;

					ReleasePlayerTama(plTama);
					GDc.PlayerTamaList->FastDesertElement(index);
					index--;
				}
			}

			// Crash -- Missile / 敵

			for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
			{
				PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

				if(IsCrashed_Circle_Rect(
					plMissile->X, plMissile->Y, PLAYER_MISSILE_CRASH_R,
					GetEnemyAtari_L(enemy), GetEnemyAtari_T(enemy), GetEnemyAtari_R(enemy), GetEnemyAtari_B(enemy)
					))
				{
					SEPlay(SE_BOMB);

					enemy->HP -= 50;
					enemyDamaged = 1;

					ReleasePlayerMissile(plMissile);
					GDc.PlayerMissileList->FastDesertElement(index);
					index--;
				}
			}

			// Crash -- Laser / 敵

			if(1 <= GDc.LaserFrame)
			{
				double l = GDc.Player.X - 1.0;
				double r = GDc.Player.X + 1.0;
				double t = 0.0; // -1000.0;
				double b = GDc.Player.Y - 16.0;

				if(IsCrashed_Rect_Rect(
					l, t, r, b,
					GetEnemyAtari_L(enemy), GetEnemyAtari_T(enemy), GetEnemyAtari_R(enemy), GetEnemyAtari_B(enemy)
					))
				{
					enemy->HP -= 3 + GDc.LaserFrame % 3 / 2;
					enemyDamaged = 1;
				}
			}

			// Crash -- Flash(Laser_B) / 敵

			if(1 <= GDc.FlashFrame)
			{
				// noop
			}

			// Crash -- 自機 / 敵

			while(IsCrashed_Circle_Rect(
				GDc.Player.X, GDc.Player.Y, PLAYER_CRASH_R,
					GetEnemyAtari_L(enemy), GetEnemyAtari_T(enemy), GetEnemyAtari_R(enemy), GetEnemyAtari_B(enemy)
				))
			{
				double MOVE_SPAN = 0.25;
				double eToPlX;
				double eToPlY;

				MakeXYSpeed(enemy->X, enemy->Y, GDc.Player.X, GDc.Player.Y, MOVE_SPAN, eToPlX, eToPlY);

				GDc.Player.X += eToPlX;
				GDc.Player.Y += eToPlY;
			}
			m_range(GDc.Player.X, 0, SCREEN_W);
			m_range(GDc.Player.Y, 0, SCREEN_H);

			// ---- ループ内 Crash ここまで ----

			// EnemyEachFrame ???

			if(enemyDamaged && enemy->DamagedFrame == 0)
			{
				SEPlay(SE_VOICE_00 + rnd(8));

				enemy->Y -= 16.0; // 敵_ヒットバック
				m_maxim(enemy->Y, 0.0); // 画面上部に引っ込まないように、

				enemy->DamagedFrame = ENEMY_DAMAGED_FRAME_MAX;
			}

			if(enemy->HP <= 0) // 敵_死亡
			{
				SEPlay(SE_EXPLOSION_E);

				GDcNV.Score += GetEnemyInfo(enemy->Kind)->Score;

				CEE.ModPicId = 2;
				CEE.PicIdFrmPerInc = 6;

				AddCommonEffect(
					Gnd.EL,
					1,
					GetEnemyDeadPicId(enemy->Kind),
					enemy->X,
					enemy->Y,
					0.0, 1.0, 1.0,
					0.0, 0.0, 0.0, 0.0, -0.02
					);

				CEE_Reset();

				ReleaseEnemy(enemy);
				GDc.EnemyList->FastDesertElement(enemyIndex);
				enemyIndex--;
			}
		}

		// Crash -- 自機 / 敵弾

		if(GDc.Player.DamagedFrame || GDc.Player.DeadFrame)
			goto endCrash_Player_EnemyTama;

		for(int index = 0; index < GDc.EnemyTamaList->GetCount(); index++)
		{
			EnemyTama_t *i = GDc.EnemyTamaList->GetElement(index);

			if(IsCrashed_Circle_Point(GDc.Player.X, GDc.Player.Y, PLAYER_CRASH_R + ENEMY_TAMA_CRASH_R, i->X, i->Y)) // 自機_被弾
			{
				PlayerDamaged();
			}
		}

		// Crash -- 自機 / 敵弾爆風

		for(int index = 0; index < GDc.EnemyTamaBlastList->GetCount(); index++)
		{
			EnemyTamaBlast_t *i = GDc.EnemyTamaBlastList->GetElement(index);

			if(IsCrashed_Circle_Point(GDc.Player.X, GDc.Player.Y, PLAYER_CRASH_R + ENEMY_TAMA_BLAST_CRASH_R, i->X, i->Y)) // 自機_被弾
			{
				PlayerDamaged();
			}
		}

endCrash_Player_EnemyTama:

		// Crash ここまで

		if(GDcNV.Score < 0)
		{
			int frm = GDcNV.DeficitFrame++ - 1; // 0～

			if(frm == DEFICIT_FRAME_MAX) // 破産
			{
				// FIXME 自爆と同じでいいか。

				SEPlay(SE_DAMAGE);

				GDc.Player.DeadFrame = 1;
				GDc.GameOver = 1;
			}
		}
		else
			GDcNV.DeficitFrame = 0;

startDraw:
		// ★★★ ここから描画 ★★★

		DrawWall();

		if(!GDc.BattleStarted)
		{
			DrawCenter(messagePicId, SCREEN_W / 2, SCREEN_H / 2);

			{
				int frm = GDc.BattleNotStartedFrame;
				double remaining = (BATTLE_START_FRAME - frm) / 60.0;
				m_range(remaining, 0.0, (double)IMAX);

				char *str = xcout("%.2f", remaining);
				int iro;

				iro = GetColor(255, 255, 255);

				DrawStringByFont_XCenter(
					SCREEN_W / 2,
					390,
					str,
					GetFontHandle(APP_COMMON_FONT, 55, 9),
					0,
					iro
					);

				memFree(str);
			}
		}

		// 敵弾爆風_描画

		for(int index = 0; index < GDc.EnemyTamaBlastList->GetCount(); index++)
		{
			EnemyTamaBlast_t *i = GDc.EnemyTamaBlastList->GetElement(index);

			DrawEnemyTamaBlast(i);
		}

		// 自弾_描画

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

		// Player_描画
		{
			double x = GDc.Player.RealX;
			double y = GDc.Player.RealY;

			int iX = d2i(x);
			int iY = d2i(y);

			if(GDc.Player.DeadFrame)
			{
				DPE_SetAlpha(playerDeadRevRate);
				DrawCenter((D_CHARA_PLAYER_00 + 4 + (ProcFrame / 6) % 2) | DTP, iX, iY);
				DPE_Reset();
			}
			else if(GDc.Player.DamagedFrame)
			{
				DrawCenter((D_CHARA_PLAYER_00 + 2 + (ProcFrame / 6) % 2) | DTP, iX, iY);
			}
			else
			{
				if(GDc.Player.BornFrame)
					DPE_SetAlpha(0.5);

				DrawCenter((D_CHARA_PLAYER_00 + (ProcFrame / 6) % 2) | DTP, iX, iY);
				DPE_Reset();
			}
		}

		// 敵_描画

		for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
		{
			DrawEnemy(GDc.EnemyList->GetElement(index));
		}

		// 敵弾_描画

		for(int index = 0; index < GDc.EnemyTamaList->GetCount(); index++)
		{
			DrawEnemyTama(GDc.EnemyTamaList->GetElement(index));
		}

		DrawScore(m_01(GDc.BattleStarted));

		// ★★★ EachFrame ★★★

		EachFrame();
	}

	SEStop(SE_LASER);

	if(GDc.WillNextStage)
	{
		//MusicFade(); // ステージ間で音楽を止めない。
	}
	else
	{
//		MusicFade(); // 同じ曲なので

		forscene(20)
		{
			DrawWall();
			EachFrame();
		}
		sceneLeave();
	}
	FreezeInput();

	GDcNV.HiSpeed = GDc.Player.HiSpeed;
	GDcNV.X = d2i(GDc.Player.X);
	GDcNV.Y = d2i(GDc.Player.Y);
	GDcNV.HP = GDc.Player.HP;
}
