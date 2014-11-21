/*
 * node.h
 *
 *  Created on: Sep 26, 2014
 *      Author: sgao
 */

#ifndef NODE_H_
#define NODE_H_

namespace sg {

template<class DataType>
class Node {
public:
typedef DataType data_type;

public:
    Node()
    : _prev(), _next()
    , _data()
    {}

    void data(DataType data) {_data = data;}
    DataType& data() {return _data;}
    const DataType& data() const {return _data;}

    void prev(Node<DataType>* prev) {_prev = prev;}
    Node<DataType>* prev() {return _prev;}
    const Node<DataType>* prev() const {return _prev;}

    void next(Node<DataType>* next) {_next = next;}
    Node<DataType>* next() {return _next;}
    const Node<DataType>* next() const {return _next;}

    void append(Node<DataType>* prev)
    {
        if (!prev) return;

        _prev = prev;
        _next = prev->_next;
        prev->_next = this;
        if (_next) {
            _next->prev(this);
        }
    }
    void detach()
    {
        if (_prev) _prev->next(_next);
        if (_next) _next->prev(_prev);
        _prev = NULL; _next = NULL;
    }
private:
    Node<DataType>* _prev;
    Node<DataType>* _next;
    DataType _data;
};


} /* namespace sg */




#endif /* NODE_H_ */
