/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
template <class Element_t>
class autoList
{
private:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int Count;
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int ListSize;
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t *List;

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Init(Element_t *list, int listSize, int count)
	{
		this->Count = count;
		this->ListSize = listSize;
		this->List = list;
	}

public:
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	autoList()
	{
		this->Init((Element_t *)memAlloc(0), 0, 0);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	autoList(int buffer_size)
	{
		errorCase(buffer_size < 0 || IMAX / sizeof(Element_t) < buffer_size);

		this->Init((Element_t *)memAlloc(buffer_size * sizeof(Element_t)), buffer_size, 0);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	autoList(Element_t *list_bind, int count)
	{
		errorCase(!list_bind);
		errorCase(count < 0 || IMAX < count);

		this->Init(list_bind, count, count);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000002 $$$$ //		autoList(const autoList &source)
// #### DELETED ==== 0000002 $$$$ //		{
// #### DELETED ==== 0000002 $$$$ //			error();
// #### DELETED ==== 0000002 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	~autoList()
	{
		memFree(this->List);
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000003 $$$$ //		autoList<Element_t> *GetClone()
// #### DELETED ==== 0000003 $$$$ //		{
// #### DELETED ==== 0000003 $$$$ //			autoList<Element_t> *list_ret = new autoList<Element_t>();
// #### DELETED ==== 0000003 $$$$ //	
// #### DELETED ==== 0000003 $$$$ //			list_ret->Count = this->Count;
// #### DELETED ==== 0000003 $$$$ //			list_ret->ListSize = this->Count;
// #### DELETED ==== 0000003 $$$$ //			list_ret->List = (Element_t *)memClone(this->List, this->Count * sizeof(Element_t));
// #### DELETED ==== 0000003 $$$$ //	
// #### DELETED ==== 0000003 $$$$ //			return list_ret;
// #### DELETED ==== 0000003 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	autoList<Element_t> *Eject()
	{
		autoList<Element_t> *list_ret = new autoList<Element_t>();

		list_ret->Count = this->Count;
		list_ret->ListSize = this->ListSize;
		list_ret->List = this->List;

		this->Count = 0;
		this->ListSize = 0;
		this->List = (Element_t *)memAlloc(0);

		return list_ret;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t *UnbindBuffer()
	{
		Element_t *list_ret = this->List;

		this->Count = 0;
		this->ListSize = 0;
		this->List = (Element_t *)memAlloc(0);

		return list_ret;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Clear()
	{
		this->Count = 0;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000004 $$$$ //		void SetCount(int count)
// #### DELETED ==== 0000004 $$$$ //		{
// #### DELETED ==== 0000004 $$$$ //			errorCase(count < 0 || this->Count < count);
// #### DELETED ==== 0000004 $$$$ //			this->Count = count;
// #### DELETED ==== 0000004 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int GetCount()
	{
		return this->Count;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t *ElementAt(int index)
	{
		if(index == 0) // this->List をダイレクトに参照するための特例
			return this->List;

		errorCase(index < 0 || this->Count <= index);

		return this->List + index;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void SetElement(int index, Element_t element)
	{
		errorCase(index < 0 || this->Count <= index);

		this->List[index] = element;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t GetElement(int index)
	{
		errorCase(index < 0 || this->Count <= index);

		return this->List[index];
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	/*
		今から count 回 AddElement() してもバッファの拡張が起こらないようにバッファを拡張する。
	*/
	void BufferExtend(int count)
	{
		errorCase(count < 0 || IMAX - this->Count < count);

		int reqListSize = this->Count + count;

		if(this->ListSize < reqListSize)
		{
			errorCase(IMAX / sizeof(Element_t) < reqListSize);

			this->ListSize = reqListSize;
			this->List = (Element_t *)memRealloc(this->List, this->ListSize * sizeof(Element_t));
		}
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void AddElement(Element_t element)
	{
		if(this->ListSize <= this->Count)
		{
			errorCase(this->ListSize != this->Count); // 2bs

			if(this->ListSize < 16)
				this->ListSize += 2;
			else
				this->ListSize *= 2;

			errorCase(this->ListSize <= this->Count); // 2bs
			errorCase(IMAX / sizeof(Element_t) < this->ListSize);

			this->List = (Element_t *)memRealloc(this->List, this->ListSize * sizeof(Element_t));
		}
		this->List[this->Count] = element;
		this->Count++;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t UnaddElement()
	{
		errorCase(this->Count < 1);

		this->Count--;
		return this->List[this->Count];
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void InsertElement(int index, Element_t element)
	{
		errorCase(index < 0 || this->Count < index);

		this->AddElement(element); // dummy

		for(int i = this->Count - 1; index < i; i--)
		{
			this->List[i] = this->List[i - 1];
		}
		this->List[index] = element;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t DesertElement(int index)
	{
		errorCase(index < 0 || this->Count <= index);

		Element_t element = this->List[index];

		this->Count--;

		for(int i = index; i < this->Count; i++)
		{
			this->List[i] = this->List[i + 1];
		}
		return element;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t FastDesertElement(int index)
	{
		errorCase(index < 0 || this->Count <= index);

		Element_t element = this->List[index];

		this->Count--;
		this->List[index] = this->List[this->Count];

		return element;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void RemoveElements(int start, int count)
	{
		errorCase(start < 0 || this->Count < start);
		errorCase(count < 0 || this->Count - start < count);

		int index;

		for(index = start; index + count < this->Count; index++)
		{
			this->List[index] = this->List[index + count];
		}
		this->Count = index;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void CallAllElement(void (*func)(Element_t e))
	{
		for(int index = 0; index < this->Count; index++)
		{
			func(this->GetElement(index));
		}
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Clear(void (*func)(Element_t e))
	{
		this->CallAllElement(func);
		this->Clear();
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void AddElements(Element_t *list, int count)
	{
		this->BufferExtend(count);

		for(int index = 0; index < count; index++)
		{
			this->AddElement(list[index]);
		}
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void AddElements(autoList<Element_t> *list)
	{
		this->AddElements(list->ElementAt(0), list->GetCount());
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Overwrite(autoList<Element_t> *list)
	{
		this->Clear();
		this->AddElements(list);
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Swap(int index1, int index2)
	{
		errorCase(index1 < 0 || this->Count <= index1);
		errorCase(index2 < 0 || this->Count <= index2);

		Element_t tmp = this->List[index1];

		this->List[index1] = this->List[index2];
		this->List[index2] = tmp;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void Reverse()
	{
		int i = 0;
		int j = this->Count - 1;

		while(i < j)
		{
			this->Swap(i, j);
			i++;
			j--;
		}
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void PutElement(int index, Element_t element, Element_t defaultElement)
	{
		errorCase(index < 0 || IMAX < index);

		if(this->Count <= index)
		{
			while(this->Count < index)
			{
				this->AddElement(defaultElement);
			}
			this->AddElement(element);
		}
		else
			this->SetElement(index, element);
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	Element_t RefElement(int index, Element_t defaultElement)
	{
		if(m_isRange(index, 0, this->Count - 1))
		{
			return this->GetElement(index);
		}
		return defaultElement;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	int UnaddRepeat(Element_t e)
	{
		int num = 0;

		while(this->Count && this->List[this->Count - 1] == e)
		{
			this->Count--;
			num++;
		}
		return num;
	}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void AddRepeat(Element_t e, int num)
	{
		for(int c = 0; c < num; c++)
		{
			this->AddElement(e);
		}
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
	void MultiDiscard(int (*isDiscardPosFunc)(Element_t *ePos))
	{
		int start;

		for(start = 0; start < this->Count; start++)
			if(isDiscardPosFunc(this->List + start))
				break;

		if(start == this->Count)
			return;

		int rPos = start + 1;
		int wPos = start;

		while(rPos < this->Count)
		{
			if(!isDiscardPosFunc(this->List + rPos))
			{
				this->List[wPos] = this->List[rPos];
				wPos++;
			}
			rPos++;
		}
		this->Count = wPos;
	}

	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000005 $$$$ //		void GnomeSort(int (*compFunc)(Element_t, Element_t), int start, int count)
// #### DELETED ==== 0000005 $$$$ //		{
// #### DELETED ==== 0000005 $$$$ //			for(int index = 1; index < count; index++)
// #### DELETED ==== 0000005 $$$$ //			{
// #### DELETED ==== 0000005 $$$$ //				for(int nearPos = index - 1; 0 <= nearPos; nearPos--)
// #### DELETED ==== 0000005 $$$$ //				{
// #### DELETED ==== 0000005 $$$$ //					if(compFunc(this->List[start + nearPos], this->List[start + nearPos + 1]) <= 0)
// #### DELETED ==== 0000005 $$$$ //						break;
// #### DELETED ==== 0000005 $$$$ //	
// #### DELETED ==== 0000005 $$$$ //					this->Swap(start + nearPos, start + nearPos + 1);
// #### DELETED ==== 0000005 $$$$ //				}
// #### DELETED ==== 0000005 $$$$ //			}
// #### DELETED ==== 0000005 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000006 $$$$ //		void Sort(int (*compFunc)(Element_t, Element_t), int start, int count)
// #### DELETED ==== 0000006 $$$$ //		{
// #### DELETED ==== 0000006 $$$$ //			int span = count;
// #### DELETED ==== 0000006 $$$$ //	
// #### DELETED ==== 0000006 $$$$ //			for(; ; )
// #### DELETED ==== 0000006 $$$$ //			{
// #### DELETED ==== 0000006 $$$$ //				span *= 10;
// #### DELETED ==== 0000006 $$$$ //				span /= 13;
// #### DELETED ==== 0000006 $$$$ //	
// #### DELETED ==== 0000006 $$$$ //				if(span < 2)
// #### DELETED ==== 0000006 $$$$ //					break;
// #### DELETED ==== 0000006 $$$$ //	
// #### DELETED ==== 0000006 $$$$ //				if(span == 9 || span == 10)
// #### DELETED ==== 0000006 $$$$ //					span = 11;
// #### DELETED ==== 0000006 $$$$ //	
// #### DELETED ==== 0000006 $$$$ //				for(int index = 0; index + span < count; index++)
// #### DELETED ==== 0000006 $$$$ //					if(0 < compFunc(this->List[start + index], this->List[start + index + span]))
// #### DELETED ==== 0000006 $$$$ //						this->Swap(start + index, start + index + span);
// #### DELETED ==== 0000006 $$$$ //			}
// #### DELETED ==== 0000006 $$$$ //			this->GnomeSort(compFunc, start, count);
// #### DELETED ==== 0000006 $$$$ //		}
	/*
		copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
	*/
// #### DELETED ==== 0000007 $$$$ //		void Sort(int (*compFunc)(Element_t, Element_t))
// #### DELETED ==== 0000007 $$$$ //		{
// #### DELETED ==== 0000007 $$$$ //			this->Sort(compFunc, 0, this->Count);
// #### DELETED ==== 0000007 $$$$ //		}
};

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
template <class Element_t>
void releaseList(autoList<Element_t> *list, void (*func)(Element_t e))
{
	errorCase(!func);

	if(!list)
		return;

	list->CallAllElement(func);
	delete list;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
template <class Element_t>
Element_t *unbindBlock(autoList<Element_t> *list)
{
	Element_t *block = list->UnbindBuffer();
	delete list;
	return block;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *unbindBlock2Line(autoList<char> *list);
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
char *unbindBlock2Line_NR(autoList<char> *list);
