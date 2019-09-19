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
// #### DELETED ==== 0000010 $$$$ //		autoTable(const autoTable &source)
// #### DELETED ==== 0000010 $$$$ //		{
// #### DELETED ==== 0000010 $$$$ //			error();
// #### DELETED ==== 0000010 $$$$ //		}
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
// #### DELETED ==== 0000011 $$$$ //		void SetCallBack(Element_t (*createCellFunc)(void), void (*releaseCellFunc)(Element_t) = NULL)
// #### DELETED ==== 0000011 $$$$ //		{
// #### DELETED ==== 0000011 $$$$ //			if(createCellFunc)
// #### DELETED ==== 0000011 $$$$ //				this->CreateCellFunc = createCellFunc;
// #### DELETED ==== 0000011 $$$$ //	
// #### DELETED ==== 0000011 $$$$ //			if(releaseCellFunc)
// #### DELETED ==== 0000011 $$$$ //				this->ReleaseCellFunc = releaseCellFunc;
// #### DELETED ==== 0000011 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000012 $$$$ //		void Change(autoTable<Element_t> *otherTable, int withCallBack = 0)
// #### DELETED ==== 0000012 $$$$ //		{
// #### DELETED ==== 0000012 $$$$ //			m_swap(this->Rows, otherTable->Rows, void *);
// #### DELETED ==== 0000012 $$$$ //	
// #### DELETED ==== 0000012 $$$$ //			if(withCallBack)
// #### DELETED ==== 0000012 $$$$ //			{
// #### DELETED ==== 0000012 $$$$ //				m_swap(this->CreateCellFunc, otherTable->CreateCellFunc, void *);
// #### DELETED ==== 0000012 $$$$ //				m_swap(this->ReleaseCellFunc, otherTable->ReleaseCellFunc, void *);
// #### DELETED ==== 0000012 $$$$ //			}
// #### DELETED ==== 0000012 $$$$ //		}

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
// #### DELETED ==== 0000013 $$$$ //		void SetSmallestSize(int w, int h)
// #### DELETED ==== 0000013 $$$$ //		{
// #### DELETED ==== 0000013 $$$$ //			m_maxim(w, this->GetWidth());
// #### DELETED ==== 0000013 $$$$ //			m_maxim(h, this->GetHeight());
// #### DELETED ==== 0000013 $$$$ //	
// #### DELETED ==== 0000013 $$$$ //			this->Resize(w, h);
// #### DELETED ==== 0000013 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000014 $$$$ //		Element_t *RefCellAt(int x, int y)
// #### DELETED ==== 0000014 $$$$ //		{
// #### DELETED ==== 0000014 $$$$ //			this->SetMinimal(x + 1, y + 1);
// #### DELETED ==== 0000014 $$$$ //			return this->CellAt(x, y);
// #### DELETED ==== 0000014 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000015 $$$$ //		Element_t RefCell(int x, int y, Element_t dummyElement)
// #### DELETED ==== 0000015 $$$$ //		{
// #### DELETED ==== 0000015 $$$$ //			if(
// #### DELETED ==== 0000015 $$$$ //				x < 0 || this->GetWidth() <= x ||
// #### DELETED ==== 0000015 $$$$ //				y < 0 || this->GetHeight() <= y
// #### DELETED ==== 0000015 $$$$ //				)
// #### DELETED ==== 0000015 $$$$ //			{
// #### DELETED ==== 0000015 $$$$ //				return dummyElement;
// #### DELETED ==== 0000015 $$$$ //			}
// #### DELETED ==== 0000015 $$$$ //			return this->GetCell(x, y);
// #### DELETED ==== 0000015 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000016 $$$$ //		Element_t RefCellEx(int x, int y)
// #### DELETED ==== 0000016 $$$$ //		{
// #### DELETED ==== 0000016 $$$$ //			this->SetSmallestSize(x + 1, y + 1);
// #### DELETED ==== 0000016 $$$$ //			return this->GetCell(x, y);
// #### DELETED ==== 0000016 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000017 $$$$ //		void PutCell(int x, int y, Element_t e)
// #### DELETED ==== 0000017 $$$$ //		{
// #### DELETED ==== 0000017 $$$$ //			this->SetSmallestSize(x + 1, y + 1);
// #### DELETED ==== 0000017 $$$$ //			return this->SetCell(x, y, e);
// #### DELETED ==== 0000017 $$$$ //		}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000018 $$$$ //		void Reset(int x, int y)
// #### DELETED ==== 0000018 $$$$ //		{
// #### DELETED ==== 0000018 $$$$ //			this->ReleaseCellFunc(this->GetCell(x, y));
// #### DELETED ==== 0000018 $$$$ //			this->SetCell(x, y, this->CreateCellFunc());
// #### DELETED ==== 0000018 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000019 $$$$ //		void Reset(int l, int t, int w, int h)
// #### DELETED ==== 0000019 $$$$ //		{
// #### DELETED ==== 0000019 $$$$ //			for(int x = 0; x < w; x++)
// #### DELETED ==== 0000019 $$$$ //			for(int y = 0; y < h; y++)
// #### DELETED ==== 0000019 $$$$ //			{
// #### DELETED ==== 0000019 $$$$ //				this->Reset(l + x, t + y);
// #### DELETED ==== 0000019 $$$$ //			}
// #### DELETED ==== 0000019 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000020 $$$$ //		void Reset()
// #### DELETED ==== 0000020 $$$$ //		{
// #### DELETED ==== 0000020 $$$$ //			this->Reset(0, 0, this->GetWidth(), this->GetHeight());
// #### DELETED ==== 0000020 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000021 $$$$ //		void Clear(int w, int h)
// #### DELETED ==== 0000021 $$$$ //		{
// #### DELETED ==== 0000021 $$$$ //			this->Resize(w, h);
// #### DELETED ==== 0000021 $$$$ //			this->Reset(
// #### DELETED ==== 0000021 $$$$ //				0,
// #### DELETED ==== 0000021 $$$$ //				0,
// #### DELETED ==== 0000021 $$$$ //				m_min(w, this->GetWidth()),
// #### DELETED ==== 0000021 $$$$ //				m_min(h, this->GetHeight())
// #### DELETED ==== 0000021 $$$$ //				);
// #### DELETED ==== 0000021 $$$$ //		}

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
