#pragma once

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

class QueueT{
private:
	NodeT *front;
	NodeT *back;
	int size;

public:
	QueueT();
	QueueT(const QueueT &src);
	~QueueT();

	QueueT operator=(const QueueT &src);
//	 Enqueue
//	Deque
//	print
	bool empty();
	int size();
//	concatenate
//	merge
//	getFront
};

QueueT::QueueT()
{
	front = nullptr;
	back = nullptr;
	size = 0;
}

QueueT::~QueueT()
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

QueueT::QueueT(const QueueT &src)
{
	NodeT<T> *tmp;
	NodeT<T> *cur = front;
	while(cur != nullptr)
	{
		tmp = cur;
		cur = cur->next;
		delete tmp;
	}
	size = src.size;
	front = new NodeT<T>(src.front);
	back = front;
	NodeT<T> *cur = src.front->next;
	while (cur != nullptr)
	{
		back->next = new NodeT<T>(cur);
		back = back->next;
		cur = cur->next;
	}
}

QueueT QueueT::operator=(const QueueT &src)
{
	if (this != src)
	{
		size = src.size;
		front = new NodeT<T>(src.front);
		back = front;
		NodeT<T> *cur = src.front->next;
		while (cur != nullptr)
		{
			back->next = new NodeT<T>(cur);
			back = back->next;
			cur = cur->next;
		}
	}
	return *this; // need to check return &this or *this
}

bool QueueT::empty()
{
	return (size == 0);
}

int QueueT::size()
{
	return size;
}