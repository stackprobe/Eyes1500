/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#include "all.h"

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000103 $$$$ //	autoList<char *> *tokenize(char *line, char *delimiters)
// #### DELETED ==== 0000103 $$$$ //	{
// #### DELETED ==== 0000103 $$$$ //		autoList<char *> *tokens = new autoList<char *>();
// #### DELETED ==== 0000103 $$$$ //		autoList<char> *token = new autoList<char>();
// #### DELETED ==== 0000103 $$$$ //	
// #### DELETED ==== 0000103 $$$$ //		for(char *p = line; *p; p++)
// #### DELETED ==== 0000103 $$$$ //		{
// #### DELETED ==== 0000103 $$$$ //			char *d;
// #### DELETED ==== 0000103 $$$$ //	
// #### DELETED ==== 0000103 $$$$ //			for(d = delimiters; *d; d++)
// #### DELETED ==== 0000103 $$$$ //				if(*d == *p)
// #### DELETED ==== 0000103 $$$$ //					break;
// #### DELETED ==== 0000103 $$$$ //	
// #### DELETED ==== 0000103 $$$$ //			if(*d)
// #### DELETED ==== 0000103 $$$$ //				tokens->AddElement(unbindBlock2Line_NR(token));
// #### DELETED ==== 0000103 $$$$ //			else
// #### DELETED ==== 0000103 $$$$ //				token->AddElement(*p);
// #### DELETED ==== 0000103 $$$$ //		}
// #### DELETED ==== 0000103 $$$$ //		tokens->AddElement(unbindBlock2Line_NR(token));
// #### DELETED ==== 0000103 $$$$ //	
// #### DELETED ==== 0000103 $$$$ //		delete token;
// #### DELETED ==== 0000103 $$$$ //		return tokens;
// #### DELETED ==== 0000103 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000104 $$$$ //	char *untokenize(autoList<char *> *tokens, char *separator)
// #### DELETED ==== 0000104 $$$$ //	{
// #### DELETED ==== 0000104 $$$$ //		autoList<char> *buffer = new autoList<char>();
// #### DELETED ==== 0000104 $$$$ //	
// #### DELETED ==== 0000104 $$$$ //		for(int index = 0; index < tokens->GetCount(); index++)
// #### DELETED ==== 0000104 $$$$ //		{
// #### DELETED ==== 0000104 $$$$ //			if(index)
// #### DELETED ==== 0000104 $$$$ //				buffer->AddElements(separator, strlen(separator));
// #### DELETED ==== 0000104 $$$$ //	
// #### DELETED ==== 0000104 $$$$ //			char *token = tokens->GetElement(index);
// #### DELETED ==== 0000104 $$$$ //			buffer->AddElements(token, strlen(token));
// #### DELETED ==== 0000104 $$$$ //		}
// #### DELETED ==== 0000104 $$$$ //		return unbindBlock2Line(buffer);
// #### DELETED ==== 0000104 $$$$ //	}
