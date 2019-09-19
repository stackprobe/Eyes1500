class bitTable
{
private:
	bitList *List;
	int Width;

public:
	~bitTable()
	{
		delete this->List;
	}

};
