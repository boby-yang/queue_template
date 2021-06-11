#pragma once
#include <iostream>

template <typename T>
class NodeT{
public:
	T data;
	NodeT *next;

	NodeT(T d){
		data = d;
		next = nullptr;
	}
	NodeT(T d, NodeT *n){
		data = d;
		next = n;
	}
};

template <typename T>
class QueueT{
private:
	NodeT<T> *front;
	NodeT<T> *back;
	int cur_size;

public:
	QueueT();
	QueueT(const QueueT<T> &src);
	~QueueT();

	QueueT operator=(const QueueT<T> &src);
//	 Enqueue
//	Deque
//	Print
	bool empty();
	int size();
//	concatenate
//	merge
//	getFront
};

template <typename T>
QueueT<T>::QueueT()
{
	front = nullptr;
	back = nullptr;
	cur_size = 0;
}

template <typename T>
QueueT<T>::QueueT(const QueueT<T> &src)
{
	cur_size = src.cur_size;
	if (cur_size > 0)
	{
		front = new NodeT<T>(src.front->data, src.front->next);
		back = front;
		NodeT<T> *cur = src.front->next;
		while (cur != nullptr)
		{
			back->next = new NodeT<T>(cur->data);
			back = back->next;
			cur = cur->next;
		}
	}
}

template <typename T>
QueueT<T>::~QueueT()
{
	NodeT<T> *tmp;
	NodeT<T> *cur = front;
	while(cur != nullptr)
	{
		tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

// what if this is not instantiated?
template <typename T>
QueueT<T> QueueT<T>::operator=(const QueueT<T> &src)
{
	if (this != src)
	{
		NodeT<T> *tmp;
		NodeT<T> *cur = front;

		while(cur != nullptr)
		{
			tmp = cur;
			cur = cur->next;
			delete tmp;
		}

		NodeT<T> newFront = new NodeT<T>(src.front);
		NodeT<T> newBack = newFront;
		cur = src.front->next;
		while (cur != nullptr)
		{
			newBack->next = new NodeT<T>(cur);
			newBack = newBack->next;
			cur = cur->next;
		}
		cur_size = src.cur_size;
		front = newFront;
		back = newBack;
	}
	return *this; // need to check return &this or *this
}

template <typename T>
bool QueueT<T>::empty()
{
	return (cur_size == 0);
}

template <typename T>
int QueueT<T>::size()
{
	return cur_size;
}