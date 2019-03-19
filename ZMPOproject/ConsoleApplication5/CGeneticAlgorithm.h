#pragma once
#include <vector>
#include "CIndividual.h"
#include "Constants.h"
#include <algorithm>
#include <ctime>

template<class T> 
class CGeneticAlgorithm
{
public:
	CGeneticAlgorithm(int iPopSize, double iCrossProb, double iMutProb, int iMaxTime, int iTournamentSize, int* piError, CKnapsackProblem<T>* pcProblem);
	~CGeneticAlgorithm();

	void vGeneratePoputation();
	void vRunIteration();
	int iGetMaxTime();
	std::pair<T*, double> cSolveProblem();
	CIndividual<T>* pcGetBestResult();
	CIndividual<T>* pcTournament(int iNumber);

private:
	int i_popSize;
	int i_maxTime;
	int i_genotypeLength;
	int i_tournamentSize;
	double i_crossProb;
	double i_mutProb;
	void vDeletePopulation();
	std::vector<CIndividual<T>*> pc_populationList{};
	CIndividual<T>* pc_bestResault;
	CKnapsackProblem<T>* pc_problem;
	static bool bOrder(CIndividual<T>* pcFirst, CIndividual<T>* pcSecond);
};
