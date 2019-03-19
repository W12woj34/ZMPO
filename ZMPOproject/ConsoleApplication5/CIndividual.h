#pragma once
#include <utility>
#include "CKnapsackProblem.h"
//#include <iostream>

template<class T>
class CIndividual
{
public:
	CIndividual(int iGenotypeLength, T* ptGenotype, CKnapsackProblem<T>* pcProblem);
	CIndividual(CIndividual &pcOther);
	~CIndividual();
	double dCalcuateFitness();
	int iGetGenotypeLength();
	double dGetFitness();
	T* ptGetGenotype();
	void vMutation();
	std::pair<CIndividual*, CIndividual*> cCross(CIndividual& pcOther);
	bool operator>(CIndividual &pcOther);
	bool operator>=(CIndividual& pcOther);
	bool operator<(CIndividual &pcOther);
	bool operator<=(CIndividual& pcOther);
	CIndividual * operator+(CIndividual &pcOther);
	CIndividual * operator^(CIndividual &pcOther);
	CIndividual & operator++(int);

private:
	double d_fitness;
	T* pt_genotype;
	int i_genotypeLength;
	CKnapsackProblem<T>* pc_problem;


};

//#include "CIndividual.cpp"

