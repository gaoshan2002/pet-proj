/*
 * queue.h
 *
 *  Created on: Nov 4, 2014
 *      Author: gstide
 */

#ifndef INCLUDE_QUEUE_QUEUE_H_
#define INCLUDE_QUEUE_QUEUE_H_

#include <stddef.h>

namespace sg {

class Node {
public:

	Node* _next;
};
class Buffer {

};

class MemoryManager {
public:
	Buffer* GetBuffer();
	void ReturnBuffer(Buffer* buf);

};

class Queue {
public:
	Queue(): _head(NULL), _tail(NULL)
	{}
	virtual ~Queue();


	void SendData(Buffer* buf);
	Buffer* ReceiveData();


private:
	Node* _head;
	Node* _tail;

};

} /* namespace sg */

#endif /* INCLUDE_QUEUE_QUEUE_H_ */
