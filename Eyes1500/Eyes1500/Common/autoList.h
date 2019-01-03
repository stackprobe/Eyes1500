/*
 * copied the source file by CopyLib.exe
 *
 */
template <class Element_t>
/*
 * copied the source file by CopyLib.exe
 *
 */
class autoList
{
/*
 * copied the source file by CopyLib.exe
 *
 */
private:
	int Count;
	int ListSize;
	Element_t *List;

	void Init(Element_t *list, int listSize, int count)
	{
		this->Count = count;
		this->ListSize = listSize;
		this->List = list;
	}

/*
 * copied the source file by CopyLib.exe
 *
 */
public:
	autoList()
	{
		this->Init((Element_t *)memAlloc(0), 0, 0);
	}
	autoList(int buffer_size)
	{
		errorCase(buffer_size < 0 || IMAX / sizeof(Element_t) < buffer_size);

		this->Init((Element_t *)memAlloc(buffer_size * sizeof(Element_t)), buffer_size, 0);
	}
	autoList(Element_t *list_bind, int count)
	{
		errorCase(!list_bind);
		errorCase(count < 0 || IMAX < count);

		this->Init(list_bind, count, count);
	}
	autoList(const autoList &source)
	{
		error();
	}
	~autoList()
	{
		memFree(this->List);
	}

	autoList<Element_t> *GetClone()
	{
		autoList<Element_t> *list_ret = new autoList<Element_t>();

		list_ret->Count = this->Count;
		list_ret->ListSize = this->Count;
		list_ret->List = (Element_t *)memClone(this->List, this->Count * sizeof(Element_t));

		return list_ret;
	}
	autoList<Element_t> *Ecdysis()
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
	Element_t *UnbindBuffer()
	{
		Element_t *list_ret = this->List;

		this->Count = 0;
		this->ListSize = 0;
		this->List = (Element_t *)memAlloc(0);

		return list_ret;
	}

	void Clear()
	{
		this->Count = 0;
	}
	void SetCount(int count)
	{
		errorCase(count < 0 || this->Count < count);
		this->Count = count;
	}
	int GetCount()
	{
		return this->Count;
	}

	Element_t *ElementAt(int index)
	{
		if(index == 0) // this->List をダイレクトに参照するための特例
			return this->List;

		errorCase(index < 0 || this->Count <= index);

		return this->List + index;
	}
	void SetElement(int index, Element_t element)
	{
		errorCase(index < 0 || this->Count <= index);

		this->List[index] = element;
	}
	Element_t GetElement(int index)
	{
		errorCase(index < 0 || this->Count <= index);

		return this->List[index];
	}

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

	void AddElement(Element_t element)
	{
		if(this->ListSize <= this->Count)
		{
			errorCase(this->ListSize != this->Count); // 2bs

			if(this->ListSize < 16)
				this->ListSize += 2;
			else
				this->ListSize *= 2;

			errorCase(this->ListSize < this->Count + 1); // 2bs
			errorCase(IMAX / sizeof(Element_t) < this->ListSize);

			this->List = (Element_t *)memRealloc(this->List, this->ListSize * sizeof(Element_t));
		}
		this->List[this->Count] = element;
		this->Count++;
	}
	Element_t UnaddElement()
	{
		errorCase(this->Count < 1);

		this->Count--;
		return this->List[this->Count];
	}
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
	Element_t FastDesertElement(int index)
	{
		errorCase(index < 0 || this->Count <= index);

		Element_t element = this->List[index];

		this->Count--;
		this->List[index] = this->List[this->Count];

		return element;
	}
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

	void CallAllElement(void (*func)(Element_t e))
	{
		for(int index = 0; index < this->Count; index++)
		{
			func(this->GetElement(index));
		}
	}
	void Clear(void (*func)(Element_t e))
	{
		this->CallAllElement(func);
		this->Clear();
	}

	void AddElements(Element_t *list, int count)
	{
		this->BufferExtend(count);

		for(int index = 0; index < count; index++)
		{
			this->AddElement(list[index]);
		}
	}
	void AddElements(autoList<Element_t> *list)
	{
		this->AddElements(list->ElementAt(0), list->GetCount());
	}
	void Overwrite(autoList<Element_t> *list)
	{
		this->Clear();
		this->AddElements(list);
	}

	void Swap(int index1, int index2)
	{
		errorCase(index1 < 0 || this->Count <= index1);
		errorCase(index2 < 0 || this->Count <= index2);

		Element_t tmp = this->List[index1];

		this->List[index1] = this->List[index2];
		this->List[index2] = tmp;
	}
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
	Element_t RefElement(int index, Element_t defaultElement)
	{
		if(m_isRange(index, 0, this->Count - 1))
		{
			return this->GetElement(index);
		}
		return defaultElement;
	}

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
	void AddRepeat(Element_t e, int num)
	{
		for(int c = 0; c < num; c++)
		{
			this->AddElement(e);
		}
	}

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

	void GnomeSort(int (*compFunc)(Element_t, Element_t), int start, int count)
	{
		for(int index = 1; index < count; index++)
		{
			for(int nearPos = index - 1; 0 <= nearPos; nearPos--)
			{
				if(compFunc(this->List[start + nearPos], this->List[start + nearPos + 1]) <= 0)
					break;

				this->Swap(start + nearPos, start + nearPos + 1);
			}
		}
	}
	void Sort(int (*compFunc)(Element_t, Element_t), int start, int count)
	{
		int span = count;

		for(; ; )
		{
			span *= 10;
			span /= 13;

			if(span < 2)
				break;

			if(span == 9 || span == 10)
				span = 11;

			for(int index = 0; index + span < count; index++)
				if(0 < compFunc(this->List[start + index], this->List[start + index + span]))
					this->Swap(start + index, start + index + span);
		}
		this->GnomeSort(compFunc, start, count);
	}
	void Sort(int (*compFunc)(Element_t, Element_t))
	{
		this->Sort(compFunc, 0, this->Count);
	}
};

/*
 * copied the source file by CopyLib.exe
 *
 */
template <class Element_t>
/*
 * copied the source file by CopyLib.exe
 *
 */
void releaseList(autoList<Element_t> *list, void (*func)(Element_t e))
{
	errorCase(!func);

	if(!list)
		return;

	list->CallAllElement(func);
	delete list;
}
