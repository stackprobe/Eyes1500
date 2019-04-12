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

		// ��������`��

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

	if(!GDc.BattleStarted && GDc.StageIndex) // ? �O�̃X�e�[�W���炱�̃X�e�[�W�֗����Ƃ���B
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
				iro = GetColor(255, 0, 0);
//				iro = GetColor(255, 255, 0); // old
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

	if(1 <= GDcNV.DeficitFrame) // �Ԏ��J�E���^
	{
		int frm = GDcNV.DeficitFrame; // 1�`
		int counter = DEFICIT_SEC_MAX - frm / 60;
		m_range(counter, 0, DEFICIT_SEC_MAX);

		char *str = xcout("%d", counter);
		int iro;

		if(onBattle)
			iro = GetColor(255, 0, 0);
		else
			iro = GetColor(255, 0, 0);
//			iro = GetColor(255, 255, 0); // old

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
static void DestroyEnemyTama(int index)
{
	ReleaseEnemyTama(GDc.EnemyTamaList->FastDesertElement(index));
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

	int messagePicId = D_CG_MESSAGE_00 | DTP;
//	int messagePicId = D_CG_MESSAGE_00 + m_01(GDc.StageIndex) | DTP; // old

	int fromPrevStage = m_01(GDc.StageIndex);

	if(!fromPrevStage)
	{
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

			if(GDc.StageIndex) // ? �O�̃X�e�[�W���炱�̃X�e�[�W�֗����B
			{
				DrawBegin(D_CHARA_PLAYER_00 | DTP, GDcNV.X, GDcNV.Y);
				DrawRotate(sc_rate * PI * 2.0);
				DrawEnd();
			}

			DrawScore(0);

			EachFrame();
		}
		sceneLeave();
	}

#if 1
	AddEnemyByStageIndex(GDc.StageIndex);
#else // �G�̔z�u�e�X�g
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

			if(!fromPrevStage)
			{
				if(BATTLE_START_FRAME_FIRST_STAGE < GDc.BattleNotStartedFrame)
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
			else // fromPrevStage
			{
				if(BATTLE_START_FRAME < GDc.BattleNotStartedFrame)
				{
					GDc.BattleStarted = 1;
//					FreezeInput(); // �v��́H
				}
			}
		}
		else
		{
			if(GetInput(INP_PAUSE) == 1)
			{
				PauseMain();
			}
		}

		// �f�o�b�O�p TODO ����������B
		{
			if(GetKeyInput(KEY_INPUT_ADD) == 1)
			{
				GDcNV.Score += 10000000;
			}
			if(GetKeyInput(KEY_INPUT_SUBTRACT) == 1)
			{
				for(int x = 0; x <= 10; x++)
				for(int y = 0; y <= 10; y++)
				{
					if(GDc.PlayerMissileList->GetCount() < 300)
					{
						GDc.PlayerMissileList->AddElement(CreatePlayerMissile(x * SCREEN_W / 10.0, y * SCREEN_H / 10.0, PI * 3.0 / 2.0));
					}
				}
			}
		}

		double playerRealXYApproachRate = 0.0;

		if(GDc.Player.BornFrame)
		{
			int frm = GDc.Player.BornFrame++ - 1; // 0�`
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
			int frm = GDc.Player.DamagedFrame++ - 1; // 0�`
			const int FRM_MAX = 120;
			double frmRate = (double)frm / FRM_MAX;
			double frmRevRate = 1.0 - frmRate;

			if(frm == FRM_MAX)
			{
				GDc.Player.DamagedFrame = 0;
				goto endDamagedPlayer;
			}
			// �_���[�W���̏��������֒ǉ�
		}
endDamagedPlayer:

		double playerDeadRate = 0.0;
		double playerDeadRevRate = 0.0;

		if(GDc.Player.DeadFrame)
		{
			int frm = GDc.Player.DeadFrame++ - 1; // 0�`
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

				GDcNV.Score -= 2000000; // �o��_�Đ�
				goto restart;
			}
			// ��e���̏��������֒ǉ�
		}

		int uncontrollable = GDc.Player.DamagedFrame || GDc.Player.DeadFrame;

		if(!uncontrollable)
		{
			double speed = ENEMY_MOVE_SPEED_CONV(GetEnemyInfo(EK_EYE_1)->MoveSpeed);
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
			if(1 <= GetInput(INP_F)) // ����
			{
				SEPlay(SE_DAMAGE);

				GDc.Player.DeadFrame = 1;
				GDc.GameOver = 1;
				GDcNV.EndCause = 'J';
			}

			if(moved)
			{
				if(GDc.Player.HiSpeed)
					GDcNV.Score -= 10000 / 60; // �o��_�ړ�
				else
					GDcNV.Score -= 50000 / 60; // �o��_�����ړ�
			}
		}

		m_range(GDc.Player.X, 0.0, SCREEN_W);
		m_range(GDc.Player.Y, 0.0, SCREEN_H);

		m_approach(GDc.Player.RealX, GDc.Player.X, playerRealXYApproachRate);
		m_approach(GDc.Player.RealY, GDc.Player.Y, playerRealXYApproachRate);

		for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
		{
			PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

			int frm = plTama->Frame++; // frm == 0�`
			plTama->Y -= 10.0;

			if(plTama->Y < 0.0) // ? ��ʊO�ɏo���B-> �J��
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
			GDcNV.Score -= 20000; // �o��_�e��
		}

		for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
		{
			PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

			int frm = plMissile->Frame++; // frm == 0�`

			PlayerMissile_Move(plMissile);
			//plMissile->Y -= 5.0; // test

//			if(IsOutOfScreen(plMissile->X, plMissile->Y)) // ? ��ʊO�ɏo���B-> �J��
			if(plMissile->Y < 0.0 || SCREEN_H < plMissile->Y) // ? ��ʏ㉺����O�ɏo���B-> �J��
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
			GDcNV.Score -= 100000; // �o��_�U���~�T�C��
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
			int frm = GDc.LaserFrame - 1; // frm == 0�`

			if(frm % 65 == 0)
			{
				SEPlay(SE_LASER);
			}
			GDcNV.Score -= 500000 / 60; // �o��_���[�U�[����
		}
		else if(GDc.LaserFrame == -1)
		{
			SEStop(SE_LASER);
		}

		if(1 <= GDc.FlashFrame) // Flash(Laser_B)
		{
			int frm = GDc.FlashFrame++ - 1; // frm == 0�`

			if(frm == 0) // �ƎˊJ�n
			{
				AllEnemy_AntiHaritsuki();
				GDcNV.Score -= 500000; // �o��_�ڒׂ����[�U�[
			}
			if(frm == 300) // �ƎˏI��
			{
				GDc.FlashFrame = 0;
			}
		}
		else
		{
			if(!uncontrollable && GDc.BattleStarted && GetInput(INP_D) == 1) // �ƎˊJ�n
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

		if(!uncontrollable && GetInput(INP_A) == 1) // �����ړ�
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

		// �G_����

		for(int index = 0; index < GDc.EnemyList->GetCount(); index++) // �G_�ړ�
		{
			Enemy_t *i = GDc.EnemyList->GetElement(index);

			if(EnemyEachFrame(i)) // ? ����
			{
				ReleaseEnemy(i);
				GDc.EnemyList->SetElement(index, NULL);
			}
		}
		GDc.EnemyList->MultiDiscard(isPointNull);

#if 0 // �G_�o��
		if(dRnd() < 0.01)
		{
			GDc.EnemyList->AddElement(CreateEnemy(EK_EYE_1, dRnd() * SCREEN_W, -10.0));
		}
#endif

		// �G�e_����

		for(int index = 0; index < GDc.EnemyTamaList->GetCount(); index++)
		{
			EnemyTama_t *i = GDc.EnemyTamaList->GetElement(index);

			if(EnemyTamaEachFrame(i)) // ? ����
			{
				ReleaseEnemyTama(i);
				GDc.EnemyTamaList->SetElement(index, NULL);
			}
		}
		GDc.EnemyTamaList->MultiDiscard(isPointNull);

		// �G�e����_����

		for(int index = 0; index < GDc.EnemyTamaBlastList->GetCount(); index++)
		{
			EnemyTamaBlast_t *i = GDc.EnemyTamaBlastList->GetElement(index);

			if(EnemyTamaBlastEachFrame(i)) // ? ����
			{
				ReleaseEnemyTamaBlast(i);
				GDc.EnemyTamaBlastList->SetElement(index, NULL);
			}
		}
		GDc.EnemyTamaBlastList->MultiDiscard(isPointNull);

		// Crash ��������

		for(int enemyIndex = 0; enemyIndex < GDc.EnemyList->GetCount(); enemyIndex++)
		{
			Enemy_t *enemy = GDc.EnemyList->GetElement(enemyIndex);
			int enemyDamaged = 0;

			// Crash -- Shot / �G

			for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
			{
				PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

				if(1 <= enemy->HP) // anti over-kill
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

			// Crash -- Missile / �G

			for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
			{
				PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

				if(1 <= enemy->HP) // anti over-kill
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

			// Crash -- Laser / �G

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

			// Crash -- Flash(Laser_B) / �G

			if(1 <= GDc.FlashFrame)
			{
				// noop
			}

			// Crash -- ���@ / �G

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

			// ---- ���[�v�� Crash �����܂� ----

			// EnemyEachFrame ???

			if(enemyDamaged && enemy->DamagedFrame == 0)
			{
				SEPlay(SE_VOICE_00 + rnd(8));

				enemy->Y -= 16.0; // �G_�q�b�g�o�b�N
				m_maxim(enemy->Y, 0.0); // ��ʏ㕔�Ɉ������܂Ȃ��悤�ɁA

				enemy->DamagedFrame = ENEMY_DAMAGED_FRAME_MAX;
			}

			if(enemy->HP <= 0) // �G_���S
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
		for(int enemyTamaIndex = 0; enemyTamaIndex < GDc.EnemyTamaList->GetCount(); enemyTamaIndex++)
		{
			EnemyTama_t *enemyTama = GDc.EnemyTamaList->GetElement(enemyTamaIndex);

			// Crash -- Shot / �G�e

			for(int index = 0; index < GDc.PlayerTamaList->GetCount(); index++)
			{
				PlayerTama_t *plTama = GDc.PlayerTamaList->GetElement(index);

				if(IsCrashed_Circle_Circle(
					plTama->X, plTama->Y, PLAYER_SHOT_CRASH_R,
					enemyTama->X, enemyTama->Y, ENEMY_TAMA_CRASH_R_BY_PLAYER_ATTACK
					))
				{
					DestroyEnemyTama(enemyTamaIndex);
					enemyTamaIndex--;
					goto crash_enemyTamaPlayerAttack_tail;
				}
			}

			// Crash -- Missile / �G�e

			for(int index = 0; index < GDc.PlayerMissileList->GetCount(); index++)
			{
				PlayerMissile_t *plMissile = GDc.PlayerMissileList->GetElement(index);

				if(IsCrashed_Circle_Circle(
					plMissile->X, plMissile->Y, PLAYER_MISSILE_CRASH_R,
					enemyTama->X, enemyTama->Y, ENEMY_TAMA_CRASH_R_BY_PLAYER_ATTACK
					))
				{
					DestroyEnemyTama(enemyTamaIndex);
					enemyTamaIndex--;
					goto crash_enemyTamaPlayerAttack_tail;
				}
			}

			// Crash -- Laser / �G�e

			if(1 <= GDc.LaserFrame)
			{
				double l = GDc.Player.X - 1.0;
				double r = GDc.Player.X + 1.0;
				double t = 0.0; // -1000.0;
				double b = GDc.Player.Y - 16.0;

				if(IsCrashed_Circle_Rect(
					enemyTama->X, enemyTama->Y, ENEMY_TAMA_CRASH_R_BY_PLAYER_ATTACK,
					l, t, r, b
					))
				{
					DestroyEnemyTama(enemyTamaIndex);
					enemyTamaIndex--;
					goto crash_enemyTamaPlayerAttack_tail;
				}
			}

			// Crash -- Flash(Laser_B) / �G�e

			if(1 <= GDc.FlashFrame)
			{
				// noop
			}

		crash_enemyTamaPlayerAttack_tail:;
		}

		// Crash -- ���@ / �G�e

		if(GDc.Player.DamagedFrame || GDc.Player.DeadFrame)
			goto endCrash_Player_EnemyTama;

		for(int index = 0; index < GDc.EnemyTamaList->GetCount(); index++)
		{
			EnemyTama_t *i = GDc.EnemyTamaList->GetElement(index);

			if(IsCrashed_Circle_Point(GDc.Player.X, GDc.Player.Y, PLAYER_CRASH_R + ENEMY_TAMA_CRASH_R, i->X, i->Y)) // ���@_��e
			{
				PlayerDamaged();

				DestroyEnemyTama(index);
				index--;
			}
		}

		// Crash -- ���@ / �G�e����

		for(int index = 0; index < GDc.EnemyTamaBlastList->GetCount(); index++)
		{
			EnemyTamaBlast_t *i = GDc.EnemyTamaBlastList->GetElement(index);

			if(IsCrashed_Circle_Point(GDc.Player.X, GDc.Player.Y, PLAYER_CRASH_R + ENEMY_TAMA_BLAST_CRASH_R, i->X, i->Y)) // ���@_��e
			{
				PlayerDamaged();

				DestroyEnemyTama(index);
				index--;
			}
		}

endCrash_Player_EnemyTama:

		// Crash �����܂�

		if(GDcNV.Score < 0)
		{
			int frm = GDcNV.DeficitFrame++; // 0�`

			if(frm == DEFICIT_FRAME_MAX) // �j�Y
			{
				// �����Ɠ����B

				SEPlay(SE_DAMAGE);

				GDc.Player.DeadFrame = 1;
				GDc.GameOver = 1;
				GDcNV.EndCause = 'A';
			}
			if(frm == 0)
			{
				SEPlayLoop(SE_SIREN);
			}
		}
		else
		{
			if(GDcNV.DeficitFrame != 0)
			{
				SEStop(SE_SIREN);
			}
			GDcNV.DeficitFrame = 0;
		}

startDraw:
		// ������ ��������`�� ������

		DrawWall();

		if(!fromPrevStage)
		if(!GDc.BattleStarted)
		{
			DrawCenter(messagePicId, SCREEN_W / 2, SCREEN_H / 2);

			{
				int frm = GDc.BattleNotStartedFrame;
				double remaining = (BATTLE_START_FRAME_FIRST_STAGE - frm) / 60.0;
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

		// �G�e����_�`��

		for(int index = 0; index < GDc.EnemyTamaBlastList->GetCount(); index++)
		{
			EnemyTamaBlast_t *i = GDc.EnemyTamaBlastList->GetElement(index);

			DrawEnemyTamaBlast(i);
		}

		// ���e_�`��

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

		// Player_�`��
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

		// �G_�`��

		for(int index = 0; index < GDc.EnemyList->GetCount(); index++)
		{
			DrawEnemy(GDc.EnemyList->GetElement(index));
		}

		// �G�e_�`��

		for(int index = 0; index < GDc.EnemyTamaList->GetCount(); index++)
		{
			DrawEnemyTama(GDc.EnemyTamaList->GetElement(index));
		}

		DrawScore(m_01(GDc.BattleStarted));

		// ������ EachFrame ������

		EachFrame();
	}

	SEStop(SE_LASER);

	if(GDc.WillNextStage)
	{
		//MusicFade(); // �X�e�[�W�Ԃŉ��y���~�߂Ȃ��B
	}
	else
	{
//		MusicFade(); // �����ȂȂ̂�

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
