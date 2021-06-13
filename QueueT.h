#pragma once

#include <iostream>
#include <stdexcept>

template<typename T>
class NodeT
{
public:
	T data;
	NodeT *next;


	/*
	 * Constructor of the NodeT that takes a template type parameter
	 * Param: template type parameter
	 * Post: initial next pointer will be set to nullptr,
	 * 		data will be set according to the given data parameter
	 */
	NodeT(T d)
	{
		data = d;
		next = nullptr;
	}

	/*
	 * Constructor of the NodeT that takes a template type parameter
	 * and a NodeT pointer
	 * Param: template type parameter and NodeT pointer
	 * Post: initial next pointer will be set to the pointer parameter,
	 * 		data will be set according to the given data parameter
	 */
	NodeT(T d, NodeT *n)
	{
		data = d;
		next = n;
	}
};

template<typename T>
class QueueT
{
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

	NodeT<T> *getFront();
};

/*
 * Default constructor of the QueueT
 * Param: None
 * Post: initial curSize will be set to 0
 * 		front and back pointers will be
 * 		set to nullptr
 */
template<typename T>
QueueT<T>::QueueT()
{
	front = nullptr;
	back = nullptr;
	curSize = 0;
}

/*
 * Copy constructor of the QueueT
 * Param: constant reference of a Queue<T> object
 * Post: curSize will be set to parameter's curSize;
 * 		front and back pointers will point to copies
 * 		of the parameter's front and back;
 * 		all NodeT will be copied in order
 */
template<typename T>
QueueT<T>::QueueT(const QueueT<T> &src)
{
	curSize = src.curSize;
	if (curSize == 0)
	{
		front = nullptr;
		back = nullptr;
	} else
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

/*
 * Destructor of the QueueT
 * Param: none
 * Post: all NodeT will be deleted in order
 */
template<typename T>
QueueT<T>::~QueueT()
{
	NodeT<T> *tmp;
	NodeT<T> *cur = front;
	while (cur != nullptr)
	{
		tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

/*
 * Overridden assignment operation of the QueueT
 * Param: constant reference of a Queue<T> object
 * Post:(parameter != this) all NodeT in the queue will deleted;
 * 		curSize will be set to parameter's curSize;
 * 		front and back pointers will point to copies
 * 		of the parameter's front and back;
 * 		all NodeT in parameter will be copied in order
 */
template<typename T>
QueueT<T> QueueT<T>::operator=(const QueueT<T> &src)
{
	if (&src != (const QueueT<T> *) this)
	{
		NodeT<T> *tmp;
		NodeT<T> *cur = front;

		while (cur != nullptr)
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
		curSize = src.curSize;
		front = newFront;
		back = newBack;
	}
	return *this;
}

/*
 * Pre: QueueT obj need to be created.
 * Param: template type parameter to add
 * Post: add new NodeT to the Queue
 */
template<typename T>
void QueueT<T>::enqueue(T in)
{
	NodeT<T> *tmp;
	tmp = new NodeT<T>(in);
	if (curSize == 0)
	{
		front = tmp;
		back = tmp;
	} else
	{
		back->next = tmp;
		back = tmp;
	}
	curSize++;
	return;
}

/*
 * Pre: QueueT obj need to be created.
 * Param: none
 * Post: remove NodeT in the front of the QueueT and return its data;
 *  throws runtime error if this QueueT is empty
 */
template<typename T>
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
	curSize--;
	return (out);
}

/*
 * Pre: QueueT obj need to be created.
 * Param: none
 * Post: prints all NodeT in the QueueT in order
 */
template<typename T>
void QueueT<T>::print()
{
	NodeT<T> *tmp = front;
	while (tmp != nullptr)
	{
		std::cout << std::to_string(tmp->data) << std::endl;
		tmp = tmp->next;
	}
	return;
}

/*
 * Pre: QueueT obj need to be created.
 * Param: none
 * Post: returns true if QueueT is empty;
 * 		false otherwise
 */
template<typename T>
bool QueueT<T>::empty()
{
	return (curSize == 0);
}

/*
 * Pre: QueueT obj need to be created.
 * Param: none
 * Post: returns size of the QueueT
 */
template<typename T>
int QueueT<T>::size() const
{
	return curSize;
}

/*
 * Pre: QueueT obj and parameter need to be created.
 * Param: reference to another QueueT and
 * 		number of NodeT to append
 * Post: remove n NodeT from in and add them
 * 		to this QueueT; throws runtime error if
 * 		n exceeds input QueueT size
 */
template<typename T>
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
	return;
}

/*
 * Pre: QueueT obj and parameter need to be created.
 * Param: reference to another QueueT
 * Post: merges NodeT in the two QueueT in alternative
 * 		order, starting from first NodeT in this QueueT
 */
template<typename T>
QueueT<T> QueueT<T>::merge(const QueueT<T> &in)
{
	NodeT<T> *tmp1 = front;
	NodeT<T> *tmp2 = in.front;
	QueueT<T> out = QueueT();
	while (nullptr != tmp1 && nullptr != tmp2)
	{
		out.enqueue(tmp1->data);
		out.enqueue(tmp2->data);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	while (nullptr != tmp1)
	{
		out.enqueue(tmp1->data);
		tmp1 = tmp1->next;
	}
	while (nullptr != tmp2)
	{
		out.enqueue(tmp2->data);
		tmp2 = tmp2->next;
	}
	return out;
}

/*
 * Pre: QueueT obj need to be created.
 * Param: none
 * Post: return NodeT in the front of the QueueT
 */
template<typename T>
NodeT<T> *QueueT<T>::getFront()
{
	return front;
};
