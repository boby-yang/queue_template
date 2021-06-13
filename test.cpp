#include "QueueT.h"
#include <iostream>
using std::cout;
using std::endl;

void extraTest()
{
	QueueT<int> q1;

	q1.enqueue(2);
	q1.enqueue(2);
	q1.enqueue(-2);
	cout << "q1 print: {2,2,-2} = ";
	q1.print();

//	q1.dequeue();
//	cout << "print: {2,-2} = ";
//	q1.print();
//
//	q1.dequeue();
//	q1.dequeue();
//	cout << "print: {} = ";
//	q1.print();
//	cout << "empty: 1 = " << q1.empty() << endl;

//	cout << "Runtime error" << endl;
//	q1.dequeue();
	QueueT<int> q2;

	q2.enqueue(1);
	q2.enqueue(1);
	q2.enqueue(-1);

	cout << "q2 print: {1,1,-1} = ";
	q2.print();

//	q1.concatenate(q2, 0);
//	cout << endl << "q1 (concatenate): {2,2,-2} = ";
//	q1.print();
//	cout << endl << "q2 (concatenate): {1, 1,-1} = ";
//	q2.print();
//
//	q1.concatenate(q2, 1);
//	cout << endl << "q1 (concatenate): {2,2,-2,1} = ";
//	q1.print();
//	cout << endl << "q2 (concatenate): {1,-1} = ";
//	q2.print();
//
//	q1.concatenate(q2, 2);
//	cout << endl << "q1 (concatenate): {2,2,-2, 1, 1, -1} = ";
//	q1.print();
//	cout << endl << "q2 (concatenate): {} = ";
//	q2.print();
//
//	q2.concatenate(q1, 2);
//	cout << endl << "q1 (concatenate): {-2,1,1,-1} = ";
//	q1.print();
//	cout << endl << "q2 (concatenate): {2,2} = ";
//	q2.print();

	QueueT<int> q4 = q1.merge(q2);
	cout << endl << "q1,2 (merge): {2,1,2,1,-2,-1} = ";
	q4.print();

	QueueT<int> q5 = q2.merge(q1);
	cout << endl << "q2,1 (merge): {1,2,1,2,-1,-2} = ";
	q5.print();

	q1.enqueue(0);
	q1.enqueue(3);
	q1.enqueue(-3);
	QueueT<int> q7 = q1.merge(q2);
	cout << endl << "q1,2 (merge): {2,1,2,1,-2,-1,0,3,-3} = ";
	q7.print();

	QueueT<int> q8 = q2.merge(q1);
	cout << endl << "q2,1 (merge): {1,2,1,2,-1,-2,0,3,-3} = ";
	q8.print();

	QueueT<int> q9;
	QueueT<int> q10 = q1.merge(q9);
	cout << endl << "q1,{} (merge): {2,2,-2,0,3,-3} = ";
	q10.print();

	QueueT<int> q11 = q9.merge(q1);
	cout << endl << "{},q1 (merge): {2,2,-2,0,3,-3} = ";
	q11.print();

//	QueueT<int> q3;
//	QueueT<int> q4;
//	QueueT<int> q5 = q3.merge(q4);
//	cout << endl << "{},{} (merge): {} = ";
//	q5.print();

}

void simpleTest()
{
	 cout << "SIMPLE TEST" << endl;
	 QueueT<int> q1;

	 q1.enqueue(2);
	 q1.enqueue(4);
	 q1.enqueue(6);

	 cout << "empty: 0 = " << q1.empty() << endl;
	 cout << "print: {2,4,6} = ";
	 q1.print();
	 cout << endl << "size: 3 = " << q1.size() << endl;

	 QueueT<int> q2(q1);
	 QueueT<int> q3;
	 q3 = q1;

	 q1.dequeue();

	 cout << "q1 post copy: {4,6} = ";
	 q1.print();
	 cout << endl << "q2 (copy): {2,4,6} = ";
	 q2.print();
	 cout << endl << "q3 (op=): {2,4,6} = ";
	 q3.print();

	 QueueT<int> q4;
	 q4.enqueue(5);

	 QueueT<int> q5(q1.merge(q4));
	 cout << endl << "q5 (merge): {4,5,6} = ";
	 q5.print();

	 q1.concatenate(q4, 1);
	 cout << endl << "q1 (concatenate): {4,6,5} = ";
	 q1.print();

	 NodeT<int>* front = q1.getFront();
	 cout << endl << "front->next->data: 6 = " << front->next->data << endl;
	 cout << "END SIMPLE TEST" << endl;

}

void testBasicFunctions()
{
	const QueueT<int> test1;
	QueueT<int> test2 = QueueT<int>();
	cout << "Size of test2: " << std::to_string(test2.size()) << endl;
	QueueT<int> test3 = QueueT<int>(test2);
	cout << "Size of test3: " << std::to_string(test3.size()) << endl;
}

int main()
{
//	testBasicFunctions();
//	simpleTest();
	extraTest();
	while (true)
		;
	return 0;
}