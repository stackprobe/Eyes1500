	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
class bitTable
{
private:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	bitList *List;
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int Width;

public:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000026 $$$$ //		bitTable(int w)
// #### DELETED ==== 0000026 $$$$ //		{
// #### DELETED ==== 0000026 $$$$ //			errorCase(w < 1 || IMAX < w);
// #### DELETED ==== 0000026 $$$$ //	
// #### DELETED ==== 0000026 $$$$ //			this->List = new bitList();
// #### DELETED ==== 0000026 $$$$ //			this->Width = w;
// #### DELETED ==== 0000026 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000027 $$$$ //		bitTable(const bitTable &source)
// #### DELETED ==== 0000027 $$$$ //		{
// #### DELETED ==== 0000027 $$$$ //			error();
// #### DELETED ==== 0000027 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	~bitTable()
	{
		delete this->List;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000028 $$$$ //		void Clear()
// #### DELETED ==== 0000028 $$$$ //		{
// #### DELETED ==== 0000028 $$$$ //			this->List->Clear();
// #### DELETED ==== 0000028 $$$$ //		}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000029 $$$$ //		void PutBit(int x, int y, int value)
// #### DELETED ==== 0000029 $$$$ //		{
// #### DELETED ==== 0000029 $$$$ //			errorCase(x < 0);
// #### DELETED ==== 0000029 $$$$ //			errorCase(y < 0);
// #### DELETED ==== 0000029 $$$$ //			errorCase(this->Width <= x);
// #### DELETED ==== 0000029 $$$$ //			errorCase(IMAX / this->Width <= y);
// #### DELETED ==== 0000029 $$$$ //	
// #### DELETED ==== 0000029 $$$$ //			return this->List->PutBit(x + y * this->Width, value);
// #### DELETED ==== 0000029 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000030 $$$$ //		int RefBit(int x, int y)
// #### DELETED ==== 0000030 $$$$ //		{
// #### DELETED ==== 0000030 $$$$ //			errorCase(x < 0);
// #### DELETED ==== 0000030 $$$$ //			errorCase(y < 0);
// #### DELETED ==== 0000030 $$$$ //			errorCase(this->Width <= x);
// #### DELETED ==== 0000030 $$$$ //			errorCase(IMAX / this->Width <= y);
// #### DELETED ==== 0000030 $$$$ //	
// #### DELETED ==== 0000030 $$$$ //			return this->List->RefBit(x + y * this->Width);
// #### DELETED ==== 0000030 $$$$ //		}
};
