#pragma once

#include <vector>
#include <iostream>
#include "InputException.h"
const int MAX_ALLOWED_VALUE = 1024;
const int MIN_ALLOWED_VALU = -1024;
const int MAX_MAT_SIZE = 5;

template <typename T>
class SquareMatrix
{
public:
	SquareMatrix(const SquareMatrix&) = default;
	SquareMatrix(SquareMatrix&&) = default;
	SquareMatrix& operator=(const SquareMatrix&) = default;
	SquareMatrix& operator=(SquareMatrix&&) = default;
	~SquareMatrix() = default;
	//SquareMatrix(const std::vector<std::vector<T>>& matrix);
	//SquareMatrix(std::vector<std::vector<T>>&& matrix);
	SquareMatrix(int size, const T& value);
	SquareMatrix(int size);// i don't know why he did this strange c-tor !!!!!
	int size() const
	{
		return m_size;
	};
	T& operator()(int i, int j);
	const T& operator()(int i, int j) const;
	SquareMatrix& operator+=(const SquareMatrix& rhs);
	SquareMatrix& operator-=(const SquareMatrix& rhs);
	//SquareMatrix& operator*=(const SquareMatrix& rhs);
	//SquareMatrix& operator*=(const T& scalar);
	SquareMatrix operator+(const SquareMatrix& rhs) const;
	SquareMatrix operator-(const SquareMatrix& rhs) const;
	//SquareMatrix operator*(const SquareMatrix& rhs) const;
	SquareMatrix operator*(const T& scalar) const;
	//bool operator==(const SquareMatrix& rhs) const;
	//bool operator!=(const SquareMatrix& rhs) const;
	SquareMatrix Transpose() const;
	//void print(std::ostream& ostr) const;

	bool isValueValid(T) const;

private:
	int m_size;
	std::vector<std::vector<T>> m_matrix;
};

template <typename T>
const T& SquareMatrix<T>::operator()(int i, int j) const
{
	return m_matrix[i][j];
}

template <typename T>
T& SquareMatrix<T>::operator()(int i, int j)
{
	return m_matrix[i][j];
}

inline std::ostream& operator<<(std::ostream& ostr, const SquareMatrix<int>& matrix)
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			ostr << matrix(i, j) << ' ';
		}
		ostr << '\n';
	}
	return ostr;
}

inline std::istream& operator>>(std::istream& istr, SquareMatrix<int>& matrix)// mayby the input will be from file, if yes that will be good ?? 
{
	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)
		{
			int val;
			istr >> val;
			if (matrix.isValueValid(val))
				matrix(i, j) = val;
	/*	  istr >> matrix(i, j);*/

		}
	}
	return istr;
}

// Implementation must be in .h file for the compiler to see it and instantiate
// the relevant function
template <typename T>
SquareMatrix<T>::SquareMatrix(int size, const T& value)
	: m_size(size), m_matrix(size, std::vector<T>(size, value))//to check the valu of size and itch valu in the vector
{
	if()

	for (int i = 0; i < size * size; ++i)
	{
		m_matrix[i / size][i % size] = value;
	}
}

template <typename T>
SquareMatrix<T>::SquareMatrix(int size)
	: m_size(size), m_matrix(size, std::vector<T>(size))
{
	for (int i = 0; i < size * size; ++i)
	{
		m_matrix[i / size][i % size] = i;
	}
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix& rhs) const
{
	SquareMatrix result(m_size); // יצירת מטריצה בגודל נכון

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			T sum = m_matrix[i][j] + rhs.m_matrix[i][j];
			if (isValueValid(sum))
				result(i, j) = sum;
		}
	}
	return result;
}


template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator-(const SquareMatrix& rhs) const
{
	SquareMatrix result(m_size); // יצירת מטריצה בגודל נכון

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			T sum = m_matrix[i][j] - rhs.m_matrix[i][j];
			if (isValueValid(sum))
				result(i, j) = sum;
		}
	}
	return result;
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator+=(const SquareMatrix& rhs)
{
	return *this = *this + rhs;
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::operator-=(const SquareMatrix& rhs)
{
	
	return *this = *this - rhs;
}

template <typename T>
SquareMatrix<T> SquareMatrix<T>::Transpose() const
{
	SquareMatrix result(m_size);
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			result(i, j) = m_matrix[j][i];
		}
	}
	return result;
}


template <typename T>
SquareMatrix<T> SquareMatrix<T>::operator*(const T& scalar) const
{
	SquareMatrix result(*this);
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			T sum = m_matrix[i][j] * scalar;
			if(isValueValid(sum))
			result(i, j) = sum;
		}
	}
	return result;
}

template<typename T>
inline bool SquareMatrix<T>::isValueValid(T val) const
{
	if (val > MIN_ALLOWED_VALU && val < MAX_ALLOWED_VALUE)
		return true;
	else
		throw InputException("the value: " + std::to_string(val) + " ,is invalid value");

}
