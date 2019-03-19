#include "pch.h"
#include "CProblem.h"

template<class T>
CProblem<T>::CProblem(int iProblemSize, int* piError)
{
	if(iProblemSize <= 0)
	{
		*piError = c_ERROR_NEGATIVE_NUMBER_PROBLEM;
	}
	i_problemSize = iProblemSize;
}

template<class T>
CProblem<T>::~CProblem()
{
}

template<class T>
int CProblem<T>::iGetSize()
{
	return i_problemSize;
}

template class CProblem<int>;
template class CProblem<double>;
template class CProblem<bool>;