#include "all.h"

GDc_t GDc;

void GameInit(void)
{
	memset(&GDc, 0x00, sizeof(GDc));

	GDc.PlayerTamaList = new autoList<PlayerTama_t *>();
}
void GameFnlz(void)
{
	while(GDc.PlayerTamaList->GetCount())
	{
		ReleasePlayerTama(GDc.PlayerTamaList->UnaddElement());
	}
	delete GDc.PlayerTamaList;

	memset(&GDc, 0x00, sizeof(GDc));
}
