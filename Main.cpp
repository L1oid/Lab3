#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct BookInfo
{
	string book;
	int price;
	int pages;
	double rating;
	void Out();
};

struct MyStack
{
	struct Node
	{
		BookInfo data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(BookInfo);
	bool Pop(BookInfo&);
	void Info();
};

bool MyStack::Push(BookInfo data)
{
	if (!Top)
	{
		Top = new Node;
		Top->prev = NULL;
		Count = 1;
	}
	else
	{
		Node* temp;
		temp = new Node;
		temp->prev = Top;
		Top = temp;
		Count++;
	}
	Top->data = data;
	return true;
}

bool MyStack::Pop(BookInfo& data)
{
	if (!Top) return false;
	Node* temp = Top->prev;
	data = Top->data; delete Top;
	Top = temp; Count--;
	return true;
}

void MyStack::Info()
{
	if (!Top)
	{
		cout << "Stack is empty" << endl << endl;
	}
	else 
	{
		cout << endl << "Stack info: " << endl;
		cout << "Stack size = " << Count << endl;
		Top->data.Out();
	}
}

void BookInfo::Out()
{
	cout << "Last book: " << book << "\t\t" << "Price: " << price << "\t" << "Pages: " << pages << "\t" << "Rating: " << rating << endl << endl;
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

struct Product
{
	int volume;
	double price;
	void Out();
};

void Product::Out()
{
	cout << "Volume = " << volume << ' ' << "Price = " << price << endl << endl;
}

struct MyQueue
{
	struct Node
	{
		Product data;
		Node* next;
	};
	int remain = 0;
	double cost = 0;
	double profit = 0;
	Node* First = NULL;
	int Count = 0;
	bool Push(Product);
	bool Pop(Product&);
	void Info();
	bool Sell(int, double, bool);
};

bool MyQueue::Push(Product data)
{
	if (!First)
	{
		First = new Node;
		First->next = NULL;
		First->data = data;
		Count = 1;
		remain = First->data.volume;
		for (int i = 0; i < data.volume; i++)
		{
			cost += First->data.price;
		}
	}
	else
	{
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		remain += temp->next->data.volume;
		for (int i = 0; i < data.volume; i++)
		{
			cost += temp->next->data.price;
		}
		temp->next->next = NULL;
		Count++;
	}
	return true;
}

bool MyQueue::Pop(Product& data)
{
	if (!First) return false;
	Node* temp = First->next;
	data = First->data;
	remain -= First->data.volume;
	for (int i = 0; i < data.volume; i++)
	{
		cost -= First->data.price;
	}
	delete First;
	First = temp;
	Count--;
	return true;
}



void MyQueue::Info()
{
	if (!First) cout << "Queue is empty" << endl << endl;
	else
	{
		cout << endl << "Queue info: " << endl;
		cout << "Queue size = " << Count << endl;
		First->data.Out();
	}
	cout << "Total cost = " << cost << endl << "Remain = " << remain << endl << "Profit = " << profit << endl << endl;
}

bool MyQueue::Sell(int volume, double price, bool fsell)
{
	Product temp;
	if (volume == 0) return true;
	if (Count == NULL)
	{
		cout << "Not enough product !" << endl << endl;
		return true;
	}
	if (price < First->data.price && fsell == true)
	{
		cout << endl << "Price too low !" << endl;
		return false;
	}
	else
	{
		if (volume > remain)
		{
			cout << endl << "Not enough product !" << endl << endl;
			return false;
		}
		if (First->data.volume > volume || First->data.volume == volume)
		{
			First->data.volume -= volume;
			profit += (price - First->data.price) * volume;
			remain -= volume;
			for (int i = 0; i < volume; i++)
			{
				cost -= First->data.price;
			}
			Pop(temp);
			return true;
		}
		else
		{
			profit += (price - First->data.price) * First->data.volume;
			volume -= First->data.volume;
			Pop(temp);
			Sell(volume, price, false);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

bool GetFile(MyStack&, BookInfo&);
void GetBook(MyStack&, BookInfo&);
bool RemoveBook(MyStack& sMain, BookInfo& k, string);

int main()
{
	setlocale(LC_ALL, "ru");
	BookInfo k;
	Product k1, k11, k22;
	MyStack S;
	MyStack Temp;
	MyQueue Q;
	string title;
	int key2 = 0, key1 = 0, key = 0, price, volume;
	GetFile(S, k);
	do
	{
		cout << "1) Stack" << endl
			<< "2) Queue" << endl
			<< "0) Exit" << endl;
		cout << endl << "Select an action: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			do
			{
				cout << "1) Add product" << endl
					<< "2) Pull out product" << endl
					<< "3) Empty Ñart" << endl
					<< "4) Ñart Info" << endl
					<< "0) Exit" << endl;
				cout << endl << "Select an action: ";
				cin >> key1;
				cout << endl;
				switch (key1)
				{
				case 1:
					GetBook(S, k);
					S.Info();
					break;
				case 2:
					cout << "Enter the title of the book: ";
					cin >> title;
					RemoveBook(S, k, title);
					S.Info();
					break;
				case 3:
					while (S.Pop(k))
					{
						k.Out();
					}
					S.Info();
					break;
				case 4:
					S.Info();
					break;
				default:
					if (key1 != 0)
					{
						cout << "There is no such action !" << endl << endl;
					}
					break;
				}
			} while (key1 != 0);
			break;
		case 2:
			do
			{
				cout << "1) Goods arriving" << endl
					<< "2) Goods selling" << endl
					<< "3) Product Report" << endl
					<< "0) Exit" << endl;
				cout << endl << "Select an action: ";
				cin >> key2;
				cout << endl;
				switch (key2)
				{
				case 1:
					cout << "Enter the volume: ";
					cin >> k1.volume;
					cout << endl << "Enter the price: ";
					cin >> k1.price;
					Q.Push(k1);
					Q.Info();
					break;
				case 2:
					cout << "Enter the volume: ";
					cin >> volume;
					cout << endl << "Enter the price: ";
					cin >> price;
					cout << endl;
					Q.Sell(volume, price, true);
					Q.Info();
					break;
				case 3:
					Q.Info();
					break;
				default:
					if (key2 != 0)
					{
						cout << "There is no such action !" << endl << endl;
					}
					break;
				}
			} while (key2 != 0);
			break;
		default:
			if (key != 0)
			{
				cout << "There is no such action !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
}

bool GetFile(MyStack& Stack, BookInfo& k)
{
	ifstream F("Books.txt");
	if (!F)
	{
		cout << "Cant find file" << endl;
		return false;
	}
	while (F >> k.book >> k.price >> k.pages >> k.rating)
	{
		Stack.Push(k);
	}
	F.close();
	return true;
}

void GetBook(MyStack& Stack, BookInfo& k)
{
	cout << "Enter the title: ";
	cin >> k.book;
	cout << endl;
	cout << "Enter the price: ";
	cin >> k.price;
	cout << endl;
	cout << "Enter the amount pages: ";
	cin >> k.pages;
	cout << endl;
	cout << "Enter the rating: ";
	cin >> k.rating;
	cout << endl;
	Stack.Push(k);
}

bool RemoveBook(MyStack& sMain, BookInfo& k, string title) 
{
	MyStack sTemp;
	bool stopFind = false, find = false;
	while (stopFind == false) 
	{
		sTemp.Push(sMain.Top->data);
		sMain.Pop(k);
		if (sTemp.Top->data.book == title)
		{
			find = true;
			stopFind = true;
			break;
		}
		if (sMain.Top == NULL) 
		{
			stopFind = true;
			break;
		}
	}
	if (find == true) 
	{
		sTemp.Pop(k);
		cout << endl << "Succesfuly remove " << title << " named object!" << endl;
	}
	else 
	{
		cout << endl << "Can't find " << title << " named object!" << endl;
	}
	stopFind = false;
	while (stopFind == false) 
	{
		if (find != true) 
		{
			sMain.Push(sTemp.Top->data);
			sTemp.Pop(k);
		}
		find = false;
		if (sTemp.Top == NULL) stopFind = true;
	}
	find = false;
	return true;
}