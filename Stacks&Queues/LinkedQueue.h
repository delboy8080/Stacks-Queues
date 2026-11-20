#pragma once
#include "DList.h"
template <class T>
class LinkedQueue : private DList<T>
{
public:
	void enqueue(T item)
	{
		this->append(item);
	}
	void dequeue()
	{
		this->removeHead();
	}
	T& front()
	{
		return this->head->data;
	}
	int size()
	{
		return DList<T>::size();
	}
};