// 設定項目 >

extern int Conf_DisplayIndex;

// < 設定項目

void LoadConfig(void);
char *neReadCfgLine(autoList<uchar> *fileData, int &rIndex);
