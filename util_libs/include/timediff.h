/*
 * timediff.h
 *
 *  Created on: Oct 4, 2014
 *      Author: gstide
 */

#ifndef TIMEDIFF_H_
#define TIMEDIFF_H_

#include <cinttypes>

template<class T>
uint64_t time_diff(const T& from, const T& to)
{
	uint64_t rv = 0;

	if (from > to) {
		uint64_t unsigned_type_max = std::numeric_limits<T>::max();
		if (std::is_signed<T>::value) {
			unsigned_type_max *= 2;
			unsigned_type_max += 1;
		}
		uint64_t unsigned_from = from + unsigned_type_max+1;
		uint64_t unsigned_to = to + unsigned_type_max+1;
		rv = unsigned_type_max+1 - unsigned_from + unsigned_to;
	} else {
		if (to < 0) {
			rv = to - from;
		} else {
			rv = to;
			rv -= from;
		}
	}
	return rv;
}

#endif /* TIMEDIFF_H_ */
