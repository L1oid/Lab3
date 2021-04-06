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
		cout << "--->Stack is empty" << endl << endl;
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
	int remain;
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
	}
	else
	{
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->data = data;
		remain += temp->next->data.volume;
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
	delete First;
	First = temp;
	Count--;
	return true;
}



void MyQueue::Info()
{
	if (!First) cout << endl << "--->Queue is empty" << endl << endl;
	else
	{
		cout << "Queue info: " << endl;
		cout << "Queue size = " << Count << endl;
		First->data.Out();

		cout << "Remain = " << remain << "\nProfit = " << profit << endl << endl;
	}
}

bool MyQueue::Sell(int volume, double price, bool fsell)
{
	Product temp;
	if (volume == 0) return true;
	if (price < First->data.price && fsell == true)
	{
		cout << endl << "Price too low !" << endl << endl;
		return false;
	}
	else
	{
		if (volume > remain)
		{
			cout << endl << "Not enough product !" << endl << endl;
			return false;
		}
		if (First->data.volume > volume)
		{
			First->data.volume -= volume;
			profit += (price - First->data.price) * volume;
			remain -= volume;
			return true;
		}
		else
		{
			profit += (price - First->data.price) * volume;
			volume -= First->data.volume;
			Pop(temp);
			Sell(volume, price, false);
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------

bool GetFile(MyStack&, BookInfo&, string);
void PullOut(MyStack&, BookInfo&, string, int);

int main()
{
	setlocale(LC_ALL, "ru");
	BookInfo k;
	Product k1, k11, k22;
	MyStack S;
	MyQueue Q;
	string title;
	int key2 = 0, key1 = 0, key = 0, price, volume;
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
					<< "3) Empty trash" << endl
					<< "0) Exit" << endl;
				cout << endl << "Select an action: ";
				cin >> key1;
				cout << endl;
				switch (key1)
				{
				case 1:
					cout << "Enter the title of the book: ";
					cin >> title;
					GetFile(S, k, title);
					S.Info();
					break;
				case 2:
					cout << "Enter the title of the book: ";
					cin >> title;
					PullOut(S, k, title, S.Count);
					S.Info();
					break;
				case 3:
					while (S.Pop(k))
					{
						k.Out();
					}
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
					cout << endl;
					Q.Push(k1);
					Q.Info();
					break;
				case 2:
					cout << "Enter the volume: ";
					cin >> volume;
					cout << endl << "Enter the price: ";
					cin >> price;
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

bool GetFile(MyStack& Stack, BookInfo& k, string title)
{
	ifstream F("Books.txt");
	string check;
	if (!F)
	{
		cout << "Cant find file" << endl;
		return false;
	}
	while (F >> check)
	{
		if (check == title)
		{
			cout << endl << "Book finded!" << endl;
			k.book = check;
			F >> k.price >> k.pages >> k.rating;
			Stack.Push(k);
			F.close();
		}
	}
	if (check != title)
	{
		cout << endl << "Book not finded!" << endl << endl;
		F.close();
	}
	return true;
}

void PullOut(MyStack& Stack, BookInfo& k, string title, int count)
{
	for (int i = 0; i < count && k.book != title; i++)
	{
		Stack.Pop(k);
		if (k.book == title)
		{
			cout << "Book finded!" << endl << endl;
		}
	}
	if (k.book != title)
	{
		cout << endl << "Book not finded!" << endl << endl;
	}
}