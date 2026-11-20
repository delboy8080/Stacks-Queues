#include <iostream>

template <class T>
class ArrayedStack
{
	T* arr;
	int topPos;
	int capacity;
	void grow();
public:
	ArrayedStack(int initialCapacity=20);
	T top();
	void pop();
	void push(T item);
	int size();
	bool isEmpty();

	template <class T>
	friend std::ostream& operator<<(std::ostream& out, ArrayedStack<T>& s);

};
template <class T>
bool ArrayedStack<T>::isEmpty()
{
	return topPos == 0;
}
template <class T>
void ArrayedStack<T>::grow()
{
	T* temp = new T[capacity * 2];
	for (int i = 0; i < capacity; i++)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = temp;
	capacity *= 2;
}

template <class T>
ArrayedStack<T>::ArrayedStack(int initialCapacity)
{
	arr = new T[initialCapacity];
	capacity = initialCapacity;
	topPos = 0;
}
template <class T>
T ArrayedStack<T>::top()
{
	return arr[topPos - 1];
}
template <class T>
void ArrayedStack<T>::pop()
{
	topPos--;
}
template <class T>
void ArrayedStack<T>::push(T item)
{
	if (topPos == capacity)
	{
		grow();
	}
	arr[topPos] = item;
	topPos++;
}
template <class T>
int ArrayedStack<T>::size()
{
	return topPos;
}


template <class T>
std::ostream& operator<<(std::ostream& out, ArrayedStack<T>& s)
{
	out << "Top->";
	for (int i = s.topPos-1; i >= 0; i--)
	{
		out << s.arr[i] << " ";
	}
	out << std::endl;
	return out;
}