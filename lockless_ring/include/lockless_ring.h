/*
 * lockless_ring.h
 *
 *  Created on: Sep 26, 2014
 *      Author: sgao
 */

#ifndef LOCKLESS_RING_H_
#define LOCKLESS_RING_H_

#include <cinttypes>

#include "node.h"

namespace sg {

template<class DataType>
class LocklessRing {
public:
	static const uint32_t DEFAULT_CAP = 10;

public:
	LocklessRing(uint32_t size = DEFAULT_CAP)
	: _head(), _tail()
	, _size(0)
	{
		resize(size);
	}
	virtual ~LocklessRing()
	{}

	void resize(const uint32_t size)
	{
		while (_size < size) {
			_tail->append(new Node<DataType>());
			_size++;
		}
		while (_size > size) {
			auto new_tail = _tail->prev();
			_tail->detach();
			delete _tail;
			_tail = new_tail;
			_size--;
		}
	}
private:
	Node<DataType>* _head;
	Node<DataType>* _tail;

	uint32_t _size;
};

} /* namespace sg */

#endif /* LOCKLESS_RING_H_ */
