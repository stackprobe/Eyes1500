/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
	JChar.bin
		CP932
		�A���A���p�X�y�[�X���܂܂Ȃ��B(ASCII�E���p�J�i���܂�)
*/
static bitList *GetBitList(void)
{
	static bitList *list;

	if(!list)
	{
		autoList<uchar> *fileData = GetEtcRes()->GetHandle(ETC_JCHAR);
		autoList<uint> *listData = new autoList<uint>(fileData->GetCount() / 4);

		for(int index = 0; index < fileData->GetCount(); index += 4)
		{
			listData->AddElement(
				(uint)fileData->GetElement(index + 0) <<  0 |
				(uint)fileData->GetElement(index + 1) <<  8 |
				(uint)fileData->GetElement(index + 2) << 16 |
				(uint)fileData->GetElement(index + 3) << 24
				);
		}
		list = new bitList();
#if 1
		list->SetList_DIRECT(listData);
#else // old
		list->Overwrite_DIRECT(listData);
		delete listData;
#endif

		GetEtcRes()->UnloadAllHandle(); // �e��S�~�J��
	}
	return list;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int isJChar(int chr)
{
	return m_isRange(chr, 1, 0xffff) && GetBitList()->RefBit(chr);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000095 $$$$ //	int isJChar(char *pChr) // ret: 0 == not JChar, 1-2 == �o�C�g��
// #### DELETED ==== 0000095 $$$$ //	{
// #### DELETED ==== 0000095 $$$$ //		if(isJChar(*pChr))
// #### DELETED ==== 0000095 $$$$ //			return 1;
// #### DELETED ==== 0000095 $$$$ //	
// #### DELETED ==== 0000095 $$$$ //		if(*pChr && isJChar(*pChr << 8 | pChr[1]))
// #### DELETED ==== 0000095 $$$$ //			return 2;
// #### DELETED ==== 0000095 $$$$ //	
// #### DELETED ==== 0000095 $$$$ //		return 0;
// #### DELETED ==== 0000095 $$$$ //	}
