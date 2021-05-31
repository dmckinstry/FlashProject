void TestBytItGet()
{
	bool var[1000];
	for (int i = 0; i < 1000; i++)
	{
		var[i]=1;
	}
	cout<<"Testing Get() on BytIt formed with all 1s:\n";
	strBytIt buddy = strBytIt(var);
	cout<<buddy.getNext()<<'\n';
	for (int i = 0; i < 1000; i++)
	{
		var[i]=0;
	}
	cout<<"Testing Get() on BytIt formed with all 0s:\n";
	buddy = strBytIt(var);
	cout<<buddy.getNext()<<'\n';
	//buddy might be a data leak?
}
