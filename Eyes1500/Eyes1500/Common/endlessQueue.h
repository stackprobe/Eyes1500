//
// copied the source file by CopyLib.exe
//
template <class Element_t>
//
// copied the source file by CopyLib.exe
//
class endlessQueue
{
//
// copied the source file by CopyLib.exe
//
private:
	autoList<Element_t> *List;
	int RIndex;

	void Init(autoList<Element_t> *list)
	{
		this->List = list;
		this->RIndex = 0;
	}

//
// copied the source file by CopyLib.exe
//
public:
	endlessQueue()
	{
		this->Init(new autoList<Element_t>());
	}
	endlessQueue(autoList<Element_t> *list_bind)
	{
		this->Init(list_bind);
	}
	endlessQueue(const endlessQueue &source)
	{
		error();
	}
	~endlessQueue()
	{
		delete this->List;
	}

	void Enqueue(Element_t e)
	{
		this->List->AddElement(e);
	}
	Element_t Dequeue()
	{
		Element_t e = this->List->GetElement(this->RIndex); // this->List->GetCount() == 0 ならここでエラーになる。
		this->RIndex = (this->RIndex + 1) % this->List->GetCount();
		return e;
	}

	autoList<Element_t> *GetList_DIRECT()
	{
		return this->List;
	}
};

//
// copied the source file by CopyLib.exe
//
template <class Element_t>
//
// copied the source file by CopyLib.exe
//
void releaseQueue(endlessQueue<Element_t> *queue, void (*func)(Element_t e))
{
	errorCase(!queue);
	errorCase(!func);

	queue->GetList_DIRECT()->CallAllElement(func);
	delete queue;
}
