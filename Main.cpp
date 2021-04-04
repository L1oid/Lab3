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
		cout << "--->Stack is empty" << endl;
	else {
		cout << endl << "Stack info: " << endl;
		cout << "\tStack size =" << Count << endl;
		Top->data.Out();
	}
}

void BookInfo::Out()
{
	cout << "Book: " << book << "\t" << "Price: " << price << "\t" << "Pages: " << pages << "\t" << "Rating: " << rating << endl;
}

bool GetFile(MyStack&, string);

int main()
{
	setlocale(LC_ALL, "ru");
	BookInfo k;
	MyStack S;
	string title;
	int key = 0;
	do
	{
		cout << "1) Add product" << endl
			<< "2) Pull out product" << endl
			<< "3) Empty trash" << endl
			<< "0) Exit" << endl;
		cout << endl << "Select an action: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			cout << "Enter the title of the book: ";
			cin >> title;
			GetFile(S, title);
			S.Info();
			break;
		case 2:
			cout << "Enter the title of the book: ";
			cin >> title;
			S.Pop(k);
			k.Out();
			S.Info();
			break;
		case 3:

			break;
		default:
			if (key != 0)
			{
				cout << "LOL !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
}

bool GetFile(MyStack& Stack, string title)
{
	ifstream F("Books.txt");
	string check;
	if (!F)
	{
		cout << "Cant find file" << endl;
		return false;
	}
	BookInfo k;
	while (F >> check)
	{
		if (check == title)
		{
			cout << "Book finded!" << endl << endl;
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
















/*
struct Product
{
	int volume;
	double price;
	void Out();
};
void Product::Out()
{
	cout << "\nVolume = " << volume << ' ' << "Price = " << price << endl;
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
	if (!First) cout << "--->Queue is empty" << endl;
	else
	{
		cout << endl << "Queue info: " << endl;
		cout << "\tQueue size = " << Count << endl;
		//cout << "YeFirst data" << First->data << endl << endl;
		First->data.Out();

		cout << "\nRemain = " << remain << "\nProfit = " << profit;
	}
}

bool MyQueue::Sell(int volume, double price, bool fsell)
{
	//cout << "\nDebugging:\n" << volume << endl;
	Product temp;

	if (volume == 0) return true;


	if (price < First->data.price && fsell == true)
	{
		cout << "\nError >> price too low\n";
		return false;
	}
	else
	{
		if (volume > remain)
		{
			cout << "\nError >> not enough product\n";
			return false;
		}
		if (First->data.volume > volume)
		{
			First->data.volume -= volume;
			profit += (price - First->data.price) * volume;
			//profit += price * volume;
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




int main()
{
	int n = 10;
	Product k;
	Product k1 = { 100, 10.0 }, k2 = { 10, 20.0 };
	MyQueue Q;

	Q.Info();
	Q.Push(k1);
	Q.Push(k2);
	Q.Info();
	cout << "\n__________________\n";

	Q.Sell(101, 15, true);
	Q.Info();

	cout << "\n__________________\n";
	while (Q.Pop(k)) k.Out();
	cout << endl;
	Q.Info();

	return 0;
}*/