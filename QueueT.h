#pragma once
#include <iostream>
#include <stdexcept>

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
	void enqueue(T in);
	T dequeue();
	void print();
	bool empty();
	int size() const;
	void concatenate(QueueT<T> &in, int n);
	QueueT<T> merge(const QueueT<T> &in);
	NodeT<T>* getFront();
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
	if (cur_size == 0)
	{
		front = nullptr;
		back = nullptr;
	}
	else
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
	if (&src != (const QueueT<T>*)this)
	{
		NodeT<T> *tmp;
		NodeT<T> *cur = front;

		while(cur != nullptr)
		{
			tmp = cur;
			cur = cur->next;
			delete tmp;
		}

		NodeT<T> *newFront = new NodeT<T>(src.front->data, src.front->next);
		NodeT<T> *newBack = newFront;
		cur = src.front->next;
		while (cur != nullptr)
		{
			newBack->next = new NodeT<T>(cur->data, cur->next);
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
void QueueT<T>::enqueue(T in)
{
	NodeT<T> *tmp;
	tmp = new NodeT<T>(in);
	if (cur_size == 0)
	{
		front = tmp;
		back = tmp;
	}
	else
	{
		back->next = tmp;
		back = tmp;
	}
	cur_size++;
	return ;
}

template <typename T>
T QueueT<T>::dequeue()
{
	NodeT<T> *tmp = front;
	if (nullptr == tmp)
	{
		throw std::runtime_error("queue is empty.");
	}
	T out = front->data;
	front = front->next;
	delete tmp;
	cur_size--;
	return (out);
}

template <typename T>
void QueueT<T>::print()
{
	NodeT<T> *tmp = front;
	while(tmp != nullptr)
	{
		std::cout << std::to_string(tmp->data) << std::endl;
		tmp = tmp->next;
	}
	return ;
}

template <typename T>
bool QueueT<T>::empty()
{
	return (cur_size == 0);
}

template <typename T>
int QueueT<T>::size() const
{
	return cur_size;
}

template <typename T>
void QueueT<T>::concatenate(QueueT<T> &in, int n)
{
	if (in.size() < n)
	{
		throw std::runtime_error("Queue size is smaller than given n");
	}
	for (int i = 0; i < n; ++i)
	{
		enqueue(in.dequeue());
	}
	return ;
}

template <typename T>
QueueT<T> QueueT<T>::merge(const QueueT<T> &in)
{
	NodeT<T> *tmp1 = front;
	NodeT<T> *tmp2 = in.front;
	QueueT<T> out = QueueT();
	while(nullptr != tmp1 && nullptr != tmp2)
	{
		out.enqueue(tmp1->data);
		out.enqueue(tmp2->data);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	while(nullptr != tmp1)
	{
		out.enqueue(tmp1->data);
		tmp1 = tmp1->next;
	}
	while(nullptr != tmp2)
	{
		out.enqueue(tmp2->data);
		tmp2 = tmp2->next;
	}
	return out;
}

template <typename T>
NodeT<T>* QueueT<T>::getFront()
{
	return front;
};
