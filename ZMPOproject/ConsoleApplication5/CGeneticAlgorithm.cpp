#include "pch.h"
#include "CGeneticAlgorithm.h"

template<class T>
CGeneticAlgorithm<T>::CGeneticAlgorithm(int iPopSize, double iCrossProb, double iMutProb, int iMaxTime, int iTournamentSize, int* piError, CKnapsackProblem<T>* pcProblem)
{
	if (iPopSize <= 0)
	{
		*piError = c_ERROR_NEGATIVE_POP_SIZE;
		return;
	}
	if(iCrossProb < 0 || iCrossProb > 1)
	{
		*piError = c_ERROR_WRONG_CROSS_PROB;
		return;
	}
	if (iMutProb < 0 || iMutProb > 1)
	{
		*piError = c_ERROR_WRONG_MUT_PROB;
		return;
	}
	if (iMaxTime <=0)
	{
		*piError = c_ERROR_WRONG_TIME_LIMIT;
		return;
	}
	if (iTournamentSize <= 0)
	{
		*piError = c_ERROR_NEGATIVE_TOURNAMENT_SIZE;
		return;
	}
	if (pcProblem == nullptr)
	{
		*piError = c_ERROR_CPROBLEM_NULL;
		return;
	}

	i_popSize = iPopSize;
	i_crossProb = iCrossProb;
	i_mutProb = iMutProb;
	i_maxTime = iMaxTime * c_MILI_TO_NORMAL;
	i_tournamentSize = iTournamentSize;
	i_genotypeLength = pcProblem->iGetSize();
	pc_problem = pcProblem;
	pc_bestResault = nullptr;
}

template<class T>
CGeneticAlgorithm<T>::~CGeneticAlgorithm()
{
	vDeletePopulation();
	delete pc_bestResault;
}


template<>
void CGeneticAlgorithm<int>::vGeneratePoputation()
{
	int i_gene;

	for(int i = 0; i < i_popSize; i++)
	{
		int* pi_genotype = new int[i_genotypeLength];

		for (int j = 0; j < i_genotypeLength; j++)
		{

			int i_maxItems = (int)pc_problem->dGetMaxItems(j);
			i_gene = std::rand() % ((int)i_maxItems + 1);
			pi_genotype[j] = i_gene;
		}
		pc_populationList.push_back(new CIndividual<int>(i_genotypeLength, pi_genotype, pc_problem));
	}

	std::sort(pc_populationList.begin(), pc_populationList.end(), bOrder);
	pc_bestResault = new CIndividual<int>(*pc_populationList[0]);
}

template<>
void CGeneticAlgorithm<double>::vGeneratePoputation()
{
	double d_gene;

	for (int i = 0; i < i_popSize; i++)
	{
		double* pd_genotype = new double[i_genotypeLength];

		for (int j = 0; j < i_genotypeLength; j++)
		{
			double d_maxItems = pc_problem->dGetMaxItems(j);
			do
			{
				d_gene = std::rand() % ((int)d_maxItems + 1) + (d_maxItems - (int)d_maxItems) - ((std::rand() % 101) / 100.0);
			} while (d_gene <= 0);
			pd_genotype[j] = d_gene;
		}
		pc_populationList.push_back(new CIndividual<double>(i_genotypeLength, pd_genotype, pc_problem));
	}

	std::sort(pc_populationList.begin(), pc_populationList.end(), bOrder);
	pc_bestResault = new CIndividual<double>(*pc_populationList[0]);
}

template<>
void CGeneticAlgorithm<bool>::vGeneratePoputation()
{
	bool b_gene;

	for (int i = 0; i < i_popSize; i++)
	{
		bool* pb_genotype = new bool[i_genotypeLength];

		for (int j = 0; j < i_genotypeLength; j++)
		{
			b_gene = std::rand() % 2;
			pb_genotype[j] = b_gene;
		}
		pc_populationList.push_back(new CIndividual<bool>(i_genotypeLength, pb_genotype, pc_problem));
	}

	std::sort(pc_populationList.begin(), pc_populationList.end(), bOrder);
	pc_bestResault = new CIndividual<bool>(*pc_populationList[0]);
}

template<class T>
void CGeneticAlgorithm<T>::vRunIteration()
{
	CIndividual<T>* test = *pc_populationList[0] + *pc_populationList[1];
	delete test;

	std::vector<CIndividual<T>*> pc_newPopulationList;
	std::pair<CIndividual<T>*, CIndividual<T>*> p_childs;
	CIndividual<T>* pc_parent1;
	CIndividual<T>* pc_parent2;
	double d_probability;


	if(i_popSize % 2 == 1)
	{
		pc_newPopulationList.push_back(new CIndividual<T>(*pc_populationList[0]));
		(*pc_newPopulationList[0])++;
	}


	while(pc_newPopulationList.size() != i_popSize)
	{

		pc_parent1 = pcTournament(i_tournamentSize);
		pc_parent2 = pcTournament(i_tournamentSize);

		while(pc_parent1 == pc_parent2)
		{
			pc_parent2 = pcTournament(i_tournamentSize);
		}

	/*	std::cout << pc_parent1 << c_SPACE << pc_parent2 << c_SPACE;
		std::cout << std::distance(pc_populationList.begin(), std::find(pc_populationList.begin(), pc_populationList.end(), pc_parent1)) << c_SPACE
			<< std::distance(pc_populationList.begin(), std::find(pc_populationList.begin(), pc_populationList.end(), pc_parent2)) << c_SPACE;*/

		d_probability = (std::rand() % c_MAX_PERCENTAGE_INT + 1) / c_MAX_PERCENTAGE_DOUBLE;
		if(d_probability <= c_CROSS_PROB)
		{
			p_childs = pc_parent1->cCross(*pc_parent2);
		/*	std::cout << c_SPACE << c_SPACE << c_CROSS << std::endl;*/
		}
		else
		{
			CIndividual<T>* c_child1 = new CIndividual<T>(*pc_parent1);
			CIndividual<T>* c_child2 = new CIndividual<T>(*pc_parent2);
			p_childs = std::make_pair(c_child1, c_child2);

			int i_size = pc_problem->iGetSize();
			/*for (int i = 0; i < i_size; i++)
			{
				std::cout << pc_parent1->ptGetGenotype()[i];
			}
			std::cout << c_SPACE;
			for (int i = 0; i < i_size; i++)
			{
				std::cout << pc_parent2->ptGetGenotype()[i];
			}
			std::cout << c_SPACE << c_SPACE << c_COPY << std::endl;*/
			
		}

		(*p_childs.first)++;
		(*p_childs.second)++;
		//p_childs.first->vMutation();
		//p_childs.second->vMutation();
		pc_newPopulationList.push_back(p_childs.first);
		pc_newPopulationList.push_back(p_childs.second);

	}

	vDeletePopulation();


	pc_populationList = pc_newPopulationList;

	std::sort(pc_populationList.begin(), pc_populationList.end(), bOrder);
	/*std::cout << pc_bestResault->dGetFitness() << c_SPACE << pc_populationList[0]->dGetFitness() << std::endl;*/
	if(pc_bestResault->dGetFitness() < pc_populationList[0]->dGetFitness())
	{
		delete pc_bestResault;
		pc_bestResault = new CIndividual<T>(*pc_populationList[0]);
	}

}

template<class T>
int CGeneticAlgorithm<T>::iGetMaxTime()
{
	return i_maxTime;
}

template<class T>
CIndividual<T>* CGeneticAlgorithm<T>::pcGetBestResult()
{
	return pc_bestResault;
}

template<class T>
CIndividual<T>* CGeneticAlgorithm<T>::pcTournament(int iNumber)
{
	std::vector<CIndividual<T>*> pc_tournamentCountenders;
	CIndividual<T>* pc_contender;
	int i_countenderIndex;
	if(iNumber > i_popSize)
	{
		iNumber = i_popSize;
	}

	for(int i = 0; i < iNumber; i++)
	{
		i_countenderIndex = std::rand() % i_popSize;
		pc_tournamentCountenders.push_back(pc_populationList[i_countenderIndex]);
	}

	std::sort(pc_tournamentCountenders.begin(), pc_tournamentCountenders.end(), bOrder);
	pc_contender = pc_tournamentCountenders[0];

	return pc_contender;
}

template<class T>
void CGeneticAlgorithm<T>::vDeletePopulation()
{
	for (int i = 0; i < i_popSize; i++)
	{
		delete pc_populationList[i];
	}
	pc_populationList.clear();

}

template<class T>
std::pair<T*, double> CGeneticAlgorithm<T>::cSolveProblem()
{
	int i_time = clock();
	this->vGeneratePoputation();

	while (i_maxTime >= clock() - i_time)
	{
		this->vRunIteration();
	}

	std::pair<T*, double> c_res = std::make_pair(this->pcGetBestResult()->ptGetGenotype(), this->pcGetBestResult()->dGetFitness());
	return c_res;
}


template<class T>
bool CGeneticAlgorithm<T>::bOrder(CIndividual<T>* pcFirst, CIndividual<T>* pcSecond)
{
	return pcFirst->dGetFitness() > pcSecond->dGetFitness();
}

template class CGeneticAlgorithm<int>;
template class CGeneticAlgorithm<double>;
template class CGeneticAlgorithm<bool>;