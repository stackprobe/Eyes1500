//
// copied the source file by CopyLib.exe
//
class finalizers
{
//
// copied the source file by CopyLib.exe
//
private:
	autoList<void (*)(void)> *Finalizers;

//
// copied the source file by CopyLib.exe
//
public:
	finalizers()
	{
		this->Finalizers = new autoList<void (*)(void)>();
	}
	finalizers(const finalizers &source)
	{
		error();
	}
	~finalizers()
	{
		delete this->Finalizers;
	}

	void AddFunc(void (*func)(void))
	{
		errorCase(!func);
		this->Finalizers->AddElement(func);
	}
	void RemoveFunc(void (*func)(void))
	{
		for(int index = this->Finalizers->GetCount() - 1; 0 <= index; index--) // LIFO
		{
			if(this->Finalizers->GetElement(index) == func)
			{
				this->Finalizers->DesertElement(index);
				break;
			}
		}
	}
	void Flush(void)
	{
		while(this->Finalizers->GetCount()) // LIFO
		{
			this->Finalizers->UnaddElement()();
		}
	}
};
