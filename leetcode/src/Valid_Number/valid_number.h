/*
 * valid_number.h
 *
 *  Created on: Nov 19, 2014
 *      Author: gstide
 */

#ifndef SRC_VALID_NUMBER_VALID_NUMBER_H_
#define SRC_VALID_NUMBER_VALID_NUMBER_H_

class ValidNumber {
public:
	ValidNumber();
	virtual ~ValidNumber();

	bool isNumber(const char* s);
};

#endif /* SRC_VALID_NUMBER_VALID_NUMBER_H_ */
