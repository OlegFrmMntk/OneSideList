#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class List
{
public:
	List();
	~List();

	void push_front(T data);
	void insert(T data, int index);
	void push_back(T data);

	void pop_front();
	void removeAt(int index);
	void pop_back();

	void clear();

	int GetSize() { return Size; }
	T& operator[](const int index);

private:

	template <typename T>
	class Node
	{
	public:
		Node *pNext;
		T data;

		Node(T data=T(), Node *pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T> *head;
};

template <typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;

}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void List<T>::pop_front()
{
	Node<T> *temp = head;

	head = head->pNext;
	delete temp;

	Size--;
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T> *previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T> *ToDel = previous->pNext;
		previous->pNext = ToDel->pNext;

		delete ToDel;
		Size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (!index)
	{
		push_front(data); 
	}
	else
	{
		Node<T> *previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T> *NewNode = new Node<T>(data, previous->pNext);
		previous->pNext = NewNode;
		Size++;
	}

}

template<typename T>
void List<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node <T>(data);
	}
	else
	{
		Node<T> *current = this->head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}

		current->pNext = new Node<T>(data);
	}

	Size++;
}

template<typename T>
T & List<T>::operator[](const int index)
{
	int counter = 0;
	Node <T> *current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
			
	List < int > spisok;

	spisok.push_back(5);
	spisok.push_back(7);
	spisok.push_back(9);
	spisok.push_back(11);

	cout << "Количество элементов списка: " << spisok.GetSize() << endl;

	for (int i = 0; i < spisok.GetSize(); i++) {

		cout << spisok[i] << " ";
	}

	cout << endl << "Удаляем элемент под номером 2" << endl;

	spisok.removeAt(1);

	cout << "Количество элементов списка: " << spisok.GetSize() << endl;

	for (int i = 0; i < spisok.GetSize(); i++) {

		cout << spisok[i] << " ";
	}
	return 0;
}