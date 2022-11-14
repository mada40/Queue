﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
///////

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
	size_t sz;
	T* pMem;
public:
	TDynamicVector(size_t size = 1) : sz(size)
	{
		if (sz == 0)
			throw out_of_range("Vector size should be greater than zero");

		if (sz > MAX_VECTOR_SIZE)
			throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");

		pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
	}
	TDynamicVector(T* arr, size_t s) : sz(s)
	{
		assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
		pMem = new T[sz];
		std::copy(arr, arr + sz, pMem);
	}
	TDynamicVector(const TDynamicVector& v)
	{
		sz = v.sz;
		pMem = new T[sz];
		std::copy(v.pMem, v.pMem + sz, pMem);
	}
	TDynamicVector(TDynamicVector&& v) noexcept
	{
		sz = v.sz;
		pMem = v.pMem;
		v.sz = 0;
		v.pMem = nullptr;
	}
	~TDynamicVector()
	{
		if (pMem) delete[] pMem;
	}
	TDynamicVector& operator=(const TDynamicVector& v)
	{
		if (this == &v)
			return *this;

		TDynamicVector tmp(v);
		swap(*this, tmp);
		return *this;
	}
	TDynamicVector& operator=(TDynamicVector&& v) noexcept
	{
		swap(*this, v);
		return *this;
	}

	size_t size() const noexcept { return sz; }

	// индексация
	T& operator[](size_t ind)
	{
		return pMem[ind];
	}
	const T& operator[](size_t ind) const
	{
		return pMem[ind];
	}
	// индексация с контролем
	T& at(size_t ind)
	{
		if (ind < 0 || ind >= sz)
			throw out_of_range("index should be greater than zero and less size vector");

		return pMem[ind];
	}
	const T& at(size_t ind) const
	{
		if (ind < 0 || ind >= sz)
			throw out_of_range("index should be greater than zero and less size vector");

		return pMem[ind];
	}

	// сравнение
	bool operator==(const TDynamicVector& v) const noexcept
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
	bool operator!=(const TDynamicVector& v) const noexcept
	{
		return !(*this == v);
	}

	// скалярные операции
	TDynamicVector operator+(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + val;
		}
		return tmp;
	}
	TDynamicVector operator-(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - val;
		}
		return tmp;
	}
	TDynamicVector operator*(T val)
	{
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] * val;
		}
		return tmp;
	}

	// векторные операции
	TDynamicVector operator+(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw length_error("the lengths of the vectors should be equal");
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] + v.pMem[i];
		}
		return tmp;
	}
	TDynamicVector operator-(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw length_error("the lengths of the vectors should be equal");
		TDynamicVector tmp(sz);
		for (size_t i = 0; i < sz; i++)
		{
			tmp.pMem[i] = pMem[i] - v.pMem[i];
		}
		return tmp;
	}
	T operator*(const TDynamicVector& v)
	{
		if (sz != v.sz)
			throw length_error("the lengths of the vectors should be equal");
		T ans = T();
		for (size_t i = 0; i < sz; i++)
		{
			ans += pMem[i] * v.pMem[i];
		}
		return ans;
	}

	friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
	{
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs.pMem, rhs.pMem);
	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			istr >> v.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
	{
		for (size_t i = 0; i < v.sz; i++)
			ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
		return ostr;
	}
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
	using TDynamicVector<TDynamicVector<T>>::pMem;
	using TDynamicVector<TDynamicVector<T>>::sz;
public:
	TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
	{
		if (s == 0)
			throw out_of_range("Matrix size should be greater than zero");

		if (s > MAX_MATRIX_SIZE)
			throw out_of_range("Matrix size should be less than MAX_MATRIX_SIZE");


		for (size_t i = 0; i < sz; i++)
			pMem[i] = TDynamicVector<T>(sz);
	}


	using TDynamicVector<TDynamicVector<T>>::operator[];

	size_t size() const noexcept { return sz; }

	const T& at(size_t row, size_t col) const 
	{
		if (row < 0 || row >= sz || col < 0 || col >= sz)
			throw out_of_range("index should be greater than zero and less size matrix");

		return pMem[row][col];
	}

	T& at(size_t row, size_t col) 
	{
		if (row < 0 || row >= sz || col < 0 || col >= sz)
			throw out_of_range("index should be greater than zero and less size matrix");

		return pMem[row][col];
	}

	// сравнение
	bool operator==(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator==(m);
	}

	bool operator!=(const TDynamicMatrix& m) const noexcept
	{
		return TDynamicVector<TDynamicVector<T>>::operator!=(m);
	}



	// матрично-скалярные операции
	TDynamicVector<T> operator*(const T& val)
	{
		return TDynamicVector<TDynamicVector<T>>::operator*(val);
	}

	// матрично-векторные операции
	TDynamicVector<T> operator*(const TDynamicVector<T>& v)
	{
		if (sz != v.sz)
			throw length_error("the lengths of the vectors should be equal");

		TDynamicVector<T> res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res[i] = pMem[i] * v[i];
		}
		return res;
	}

	// матрично-матричные операции
	TDynamicMatrix operator+(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw length_error("the lengths of the vectors should be equal");

		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res[i] = pMem[i] + m[i];
		}
		return res;

	}
	TDynamicMatrix operator-(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw length_error("the lengths of the vectors should be equal");

		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			res[i] = pMem[i] - m[i];
		}
		return res;
	}
	TDynamicMatrix operator*(const TDynamicMatrix& m)
	{
		if (sz != m.sz)
			throw length_error("the lengths of the vectors should be equal");

		TDynamicMatrix<T> res(sz);
		for (size_t i = 0; i < sz; i++)
		{
			for (size_t j = 0; j < sz; j++)
			{
				for (size_t k = 0; k < sz; k++)
				{
					res[i][j] += pMem[i][k] * m[k][j];
				}
			}
		}

		return res;

	}

	// ввод/вывод
	friend istream& operator>>(istream& istr, TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			istr >> m.pMem[i]; // требуется оператор>> для типа T
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
	{
		for (size_t i = 0; i < m.sz; i++)
			ostr << m.pMem[i] << '\n'; // требуется оператор<< для типа T
		return ostr;
	}
};

#endif