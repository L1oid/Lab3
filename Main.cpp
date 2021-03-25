#include <iostream>
#include <fstream>
using namespace std;

void BooksInfo(int number, struct MyStack S);

struct MyStack
{
	struct Node
	{
		string data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(string);
	bool Pop(string&);
	void Info();
};

bool MyStack::Push(string data)
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

bool MyStack::Pop(string& data)
{
	if (!Top)
	{
		return false;
	}
	Node* temp = Top->prev;
	data = Top->data;
	delete Top;
	Top = temp;
	Count--;
	return true;
}

void MyStack::Info()
{
	if (!Top)
	{
		cout << "Stack is empty" << endl;
	}
	else
	{
		cout << endl << "Stack info: " << endl;
		cout << "\tStack size = " << Count << endl;
		cout << "\tTop data = " << Top->data << endl << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");
	int key = 0;
	MyStack S;
	int n = 10, k;
	do
	{
		cout << "1) Добавить товар в корзину" << endl
			<< "2) Вытащить товар из корзины" << endl
			<< "3) Очистить корзину" << endl
			<< "0) Выход" << endl;
		cout << endl << "Выберите действие: ";
		cin >> key;
		cout << endl;
		switch (key)
		{
		case 1:
			S.Info();
			BooksInfo(3, S);
			S.Info();
			/*
			S.Info();
			for (int i = 1; i <= n; i++)
			{
				S.Push(i);
			}
			S.Info();
			while (S.Pop(k))
			{
				cout << k << " ";
			}
			cout << endl << endl;
			S.Info();
			break;
			*/
		case 2:

			break;
		case 3:

			break;
		default:
			if (key != 0)
			{
				cout << "Такого действия нет !" << endl << endl;
			}
			break;
		}
	} while (key != 0);
}

void BooksInfo(int number, struct MyStack S)
{
	ifstream f("Books.txt");
	string books_info;
	char check;
	int count = 0;
	/*
	while (f >> check)
	{
		count++;
	}*/
	for (int i = 0; i < 5; i++)
	{
		if (number - 1 == i)
		{
			f >> books_info;
			S.Push(books_info);
		}
	}
	f.close();
}