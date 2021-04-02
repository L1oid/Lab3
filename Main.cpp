#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//Структуры
struct Kroc 
{
	string book;
	int price;
	void Out();
};

struct MyStack 
{
	struct Node 
	{
		Kroc data;
		Node* prev;
	};
	Node* Top = NULL;
	int Count;
	bool Push(Kroc);
	bool Pop(Kroc&);
	void Info();
};

bool MyStack::Push(Kroc data) 
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
	Top->data = data;//!!!Узкое место
	return true;
}

bool MyStack::Pop(Kroc& data) 
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
		//cout << "\tTop data =" << Top->data << endl << endl;
	}
}

void Kroc::Out() 
{
	cout << "Book: " << book << setw(15) << "Price: " << price << endl;
}

bool GetFile(MyStack&);

ifstream F("Books.txt");

int main()
{
	setlocale(LC_ALL, "ru");
	Kroc k;
	MyStack S;
	int key = 0;
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
			GetFile(S);
			S.Info();
			break;
		case 2:
			S.Pop(k);
			k.Out();
			S.Info();
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
	F.close();
}

/*
int main()
{
	Kroc k; //k1 = { "Gena",72 }, k2 = { "Kesha",52 };
	MyStack S;
	S.Info();
	//S.Push(k1);
	//S.Push(k2);
	GetFile(S);
	S.Info();
	cout << "___________________________" << endl;
	while (S.Pop(k))
		k.Out();
	//cout << " " << k;
	cout << endl;
	cout << "___________________________" << endl;
	S.Info();
}*/

bool GetFile(MyStack& Stack) 
{
	if (!F) 
	{
		cout << "Cant find file" << endl;
		return false;
	}
	Kroc k;
	F >> k.book >> k.price;
	Stack.Push(k);
	/*
	while (F >> k.name >> k.age) //Пока можем извлечь
	{
		Stack.Push(k);
	}*/
	return true;
}