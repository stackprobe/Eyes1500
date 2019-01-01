#include "all.h"

static int KeyStatus[KEY_MAX];

void KeyEachFrame(void)
{
	if(WindowIsActive)
	{
		static uchar statusMap[KEY_MAX];

		errorCase(GetHitKeyStateAll((char *)statusMap)); // ? ���s

		for(int keyId = 0; keyId < KEY_MAX; keyId++)
		{
			updateInput(KeyStatus[keyId], statusMap[keyId]);
		}
	}
	else // ? ��A�N�e�B�u -> ������
	{
		for(int keyId = 0; keyId < KEY_MAX; keyId++)
		{
			updateInput(KeyStatus[keyId], 0);
		}
	}
}
int GetKeyInput(int keyId)
{
	KEY_INPUT_BACK; // keyId, ���̃L�[�� F12 �Ŕ��ł����Ċm�F���ĂˁB

	errorCase(keyId < 0 || KEY_MAX <= keyId);

	return FreezeInputFrame ? 0 : KeyStatus[keyId];
}
int GetKeyPound(int keyId)
{
	return isPound(GetKeyInput(keyId));
}
