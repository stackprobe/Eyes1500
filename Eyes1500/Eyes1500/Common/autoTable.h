/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
template <class Element_t>
class autoTable
{
private:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	autoList<autoList<Element_t> *> *Rows;
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t (*CreateCellFunc)(void);
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void (*ReleaseCellFunc)(Element_t);

public:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	autoTable(Element_t (*createCellFunc)(void), void (*releaseCellFunc)(Element_t), int w = 1, int h = 1)
	{
		errorCase(!createCellFunc);
		errorCase(!releaseCellFunc);

		this->Rows = new autoList<autoList<Element_t> *>();
		this->CreateCellFunc = createCellFunc;
		this->ReleaseCellFunc = releaseCellFunc;
		this->Resize(w, h);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	~autoTable()
	{
		while(this->Rows->GetCount())
		{
			autoList<Element_t> *row = this->Rows->UnaddElement();

			while(row->GetCount())
			{
				this->ReleaseCellFunc(row->UnaddElement());
			}
			delete row;
		}
		delete this->Rows;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Resize(int w, int h)
	{
		errorCase(w < 1 || IMAX < w);
		errorCase(h < 1 || IMAX / w < h);

		while(h < this->Rows->GetCount())
		{
			autoList<Element_t> *row = this->Rows->UnaddElement();

			while(row->GetCount())
			{
				this->ReleaseCellFunc(row->UnaddElement());
			}
			delete row;
		}
		while(this->Rows->GetCount() < h)
		{
			this->Rows->AddElement(new autoList<Element_t>());
		}
		for(int rowidx = 0; rowidx < h; rowidx++)
		{
			autoList<Element_t> *row = this->Rows->GetElement(rowidx);

			while(w < row->GetCount())
			{
				this->ReleaseCellFunc(row->UnaddElement());
			}
			while(row->GetCount() < w)
			{
				row->AddElement(this->CreateCellFunc());
			}
		}
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int GetWidth()
	{
		return this->Rows->GetElement(0)->GetCount();
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int GetHeight()
	{
		return this->Rows->GetCount();
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t *CellAt(int x, int y)
	{
		errorCase(x < 0 || this->GetWidth() <= x);
		errorCase(y < 0 || this->GetHeight() <= y);

		return this->Rows->GetElement(y)->ElementAt(x);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t GetCell(int x, int y)
	{
		return *this->CellAt(x, y);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void SetCell(int x, int y, Element_t e)
	{
		*this->CellAt(x, y) = e;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		ã‰º”½“]
	*/
	void Reverse()
	{
		this->Rows->Reverse();
	}
};
