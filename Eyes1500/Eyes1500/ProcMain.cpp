#include "all.h"

void ProcMain(void)
{
#if !LOG_ENABLED
	TitleMenu();
#elif 0 // test
	GameInit();
	GameMain();
	GameFnlz();
#elif 1 // test
	TitleMenu();
#elif 0 // test
	error(); // todo
#else
	error(); // todo
#endif
}

/*
	�f�t�H���g�̑���

	INP_DIR_2,
	INP_DIR_4,
	INP_DIR_6,
	INP_DIR_8,
	INP_A, // HIGH SPEED (�����ړ�)
	INP_B, // SHOT (�e��)
	INP_C, // LASER BEAM (���[�U�[����)
	INP_D, // BLAND LASER LIGHT (�ڒׂ����[�U�[)
	INP_E, // GUIDED MISSILE (�U���~�T�C��)
	INP_F, // SUICIDE (����)
	INP_L,
	INP_R,
	INP_PAUSE, // DECISION / PAUSE (���� / �ꎞ��~)
	INP_START,

	INP_MAX, // num of member
*/
