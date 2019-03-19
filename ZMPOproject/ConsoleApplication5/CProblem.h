#pragma once
#include "Constants.h"

template<class T>
class CIndividual;
template<class T>
class CGeneticAlgorithm;

template<class T>
class CProblem
{
public:
	CProblem(int iProblemSize, int* piError);
	virtual ~CProblem();
	int iGetSize();
	virtual double dCalculateResult(T* ptGenotype) = 0;
	virtual std::pair<T*, double> cSolveProblem(CGeneticAlgorithm<T>* pcGenAlgorithm) = 0;

protected:
	int i_problemSize;

};


//#include "CProblem.cpp"
