#define DEAD_COUNT_MAX 1024

//
// copied the source file by CopyLib.exe
//
template <class Element_t>
//
// copied the source file by CopyLib.exe
//
class autoQueue
{
//
// copied the source file by CopyLib.exe
//
private:
	autoList<Element_t> *List;
	int TopIndex;

//
// copied the source file by CopyLib.exe
//
public:
	autoQueue()
	{
		this->List = new autoList<Element_t>();
		this->TopIndex = 0;
	}
	autoQueue(const autoQueue &source)
	{
		error();
	}
	~autoQueue()
	{
		delete this->List;
	}

	void Clear()
	{
		this->List->Clear();
		this->TopIndex = 0;
	}
	void Trim()
	{
		if(1 <= this->TopIndex)
		{
			this->List->RemoveElements(0, this->TopIndex);
			this->TopIndex = 0;
		}
	}
	void Clear(void (*func)(Element_t))
	{
		this->Trim();
		this->List->Clear(func);
		this->TopIndex = 0;
	}

	void Enqueue(Element_t e)
	{
		this->List->AddElement(e);
	}
	void Enqueue(Element_t e, int repeat_num)
	{
		for(int c = 0; c < repeat_num; c++)
		{
			this->Enqueue(e);
		}
	}
	Element_t Dequeue()
	{
		Element_t e = this->List->GetElement(this->TopIndex);

		this->TopIndex++;

		if(this->TopIndex == this->List->GetCount())
		{
			this->List->Clear();
			this->TopIndex = 0;
		}
		else if(DEAD_COUNT_MAX < this->TopIndex)
		{
			this->List->RemoveElements(0, this->TopIndex);
			this->TopIndex = 0;
		}
		return e;
	}
	Element_t Dequeue(Element_t default_e)
	{
		if(this->TopIndex < this->List->GetCount())
		{
			return this->Dequeue();
		}
		return default_e;
	}

	autoList<Element_t> *GetList_DIRECT()
	{
		return this->List;
	}
	int GetTopIndex_DIRECT()
	{
		return this->TopIndex;
	}
};

//
// copied the source file by CopyLib.exe
//
template <class Element_t>
//
// copied the source file by CopyLib.exe
//
void releaseQueue(autoQueue<Element_t> *queue, void (*func)(Element_t e))
{
	errorCase(!queue);
	errorCase(!func);

	queue->Trim();
	queue->GetList_DIRECT()->CallAllElement(func);
	delete queue;
}
