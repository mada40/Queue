#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_QUEUE_SIZE = 100000000;


template<typename T>
class TDynamicQueue
{

protected:
	static const int COEFF = 2;
	size_t sz;
	size_t memSize;
	T* pMem;
	T* head, *tail;

public:
	TDynamicQueue() : memSize()
	{
		sz = 0;
		memSize = 2 * COEFF;
		pMem = new T[memSize]();// {}; // У типа T д.б. констуктор по умолчанию
		head = pMem;
		tail = pMem + 1;
	}

	TDynamicQueue(const TDynamicQueue& q)
	{
		sz = q.sz;
		pMem = new T[sz];
		head = pMem;
		tail = pMem + 1;
		std::copy(q.pMem, q.pMem + sz, pMem);
	}
	TDynamicQueue(TDynamicQueue&& v) noexcept
	{
		sz = v.sz;
		memSize = v.memSize;
		pMem = v.pMem;
		head = v.head;
		tail = v.tail;

		v.sz = 0;
		memSize = 0;
		v.pMem = v.head = v.tail = nullptr;
	}
	~TDynamicQueue()
	{
		if (pMem) delete[] pMem;
	}
	TDynamicQueue& operator=(const TDynamicQueue& v)
	{
		if (this == &v)
			return *this;

		TDynamicQueue tmp(v);
		swap(*this, tmp);
		return *this;
	}
	TDynamicQueue& operator=(TDynamicQueue&& v) noexcept
	{
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }


	
	// сравнение
	bool operator==(const TDynamicQueue& v) const noexcept
	{
		if (sz != v.sz)
			return false;

		for (size_t i = 0; i < sz; i++)
		{
			if (pMem[i] != v.pMem[i])
				return false;
		}

		return true;
	}
	bool operator!=(const TDynamicQueue& v) const noexcept
	{
		return !(*this == v);
	}

	friend void swap(TDynamicQueue& lhs, TDynamicQueue& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	const T& front() 
	{
		if (sz == 0)
			out_of_range("queue is empty");

		return *head;
	}
	void pop() 
	{ 
		if (sz == 0)
			out_of_range("queue is empty");

		head = pMem + (head - pMem + 1) % memSize;
		sz--; 
	}

	void push(const T& el)
	{

		if (tail == head)
		{
			size_t newSize = memSize * COEFF;
			T* tmp = new T[newSize];
			memSize = newSize;
			std::copy(pMem, pMem + sz, tmp);
			delete pMem;
			pMem = tmp;
			head = pMem;
			tail = pMem + sz;
		}

		*tail = el;
		tail = pMem + (tail - pMem + 1) % memSize;
		sz++;
	}


};


#endif
