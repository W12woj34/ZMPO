#include "pch.h"
#include "CIndividual.h"


template<class T>
CIndividual<T>::CIndividual(int iGenotypeLength, T* ptGenotype, CKnapsackProblem<T>* pcProblem)
{
	i_genotypeLength = iGenotypeLength;
	pt_genotype = ptGenotype;
	pc_problem = pcProblem;
	d_fitness = dCalcuateFitness();

}
template<class T>
CIndividual<T>::CIndividual(CIndividual<T> &pcOther)
{
	i_genotypeLength = pcOther.i_genotypeLength;
	pt_genotype = new T[i_genotypeLength];
	for (int i = 0; i < i_genotypeLength; i++)
	{
		pt_genotype[i] = pcOther.pt_genotype[i];
	}
	pc_problem = pcOther.pc_problem;
	d_fitness =pcOther.d_fitness;

}

template<class T>
CIndividual<T>::~CIndividual()
{
	delete pt_genotype;
}

template<class T>
double CIndividual<T>::dCalcuateFitness()
{
	return pc_problem->dCalculateResult(this->ptGetGenotype());

}

template<class T>
int CIndividual<T>::iGetGenotypeLength()
{
	return i_genotypeLength;
}

template<class T>
double CIndividual<T>::dGetFitness()
{
	return d_fitness;
}

template<class T>
T* CIndividual<T>::ptGetGenotype()
{
	return pt_genotype;
}

template<>
void CIndividual<int>::vMutation()
{
	double i_probability;

	for(int i = 0; i < i_genotypeLength; i++)
	{
		i_probability = (std::rand() % c_MAX_PERCENTAGE_INT + 1) / c_MAX_PERCENTAGE_DOUBLE;
		if(i_probability <= c_MUT_PROB)
		{
			int i_maxItems = (int)pc_problem->dGetMaxItems(i);
			pt_genotype[i] = std::rand() % ((int)i_maxItems + 1);

		}
	}

	d_fitness = dCalcuateFitness();
}

template<>
void CIndividual<bool>::vMutation()
{
	double i_probability;

	for (int i = 0; i < i_genotypeLength; i++)
	{
		i_probability = (std::rand() % c_MAX_PERCENTAGE_INT + 1) / c_MAX_PERCENTAGE_DOUBLE;
		if (i_probability <= c_MUT_PROB)
		{
			if (pt_genotype[i] == 1)
			{
				pt_genotype[i] = 0;
			}
			else
			{
				pt_genotype[i] = 1;
			}
		}
	}

	d_fitness = dCalcuateFitness();
}

template<>
void CIndividual<double>::vMutation()
{
	double i_probability;

	for (int i = 0; i < i_genotypeLength; i++)
	{
		i_probability = (std::rand() % c_MAX_PERCENTAGE_INT + 1) / c_MAX_PERCENTAGE_DOUBLE;
		if (i_probability <= c_MUT_PROB)
		{
			double d_maxItems = pc_problem->dGetMaxItems(i);
			do
			{
				pt_genotype[i] = std::rand() % ((int)d_maxItems + 1) + (d_maxItems - (int)d_maxItems) - ((std::rand() % 101) / 100.0);
			} while (pt_genotype[i] <= 0);
	
		}
	}

	d_fitness = dCalcuateFitness();
}

template<class T>
std::pair<CIndividual<T>*, CIndividual<T>*> CIndividual<T>::cCross(CIndividual<T>& pcOther)
{
//	int i_size = pc_problem->iGetSize();
	std::pair<CIndividual*, CIndividual*> p_res;
	//for (int i = 0; i < i_size; i++)
	//{
	//	std::cout << pt_genotype[i];
	//}
	//std::cout << c_SPACE;
	//for (int i = 0; i < i_size; i++)
	//{
	//	std::cout << pcOther.pt_genotype[i];
	//}

	if(i_genotypeLength == 1)
	{
		CIndividual* c_child1 = new CIndividual(*this);
		CIndividual* c_child2 = new CIndividual(pcOther);
		p_res = std::make_pair(c_child1, c_child2);
	}
	else
	{
		T* pi_genotypeCopy1 = new T[i_genotypeLength];
		T* pi_genotypeCopy2 = new T[i_genotypeLength];

		int i_crossPoint = (std::rand() % (i_genotypeLength - 1)) + 1;

		for(int i = 0; i < i_crossPoint; i++)
		{
			pi_genotypeCopy1[i] = this->pt_genotype[i];
			pi_genotypeCopy2[i] = pcOther.pt_genotype[i];
		}

		for (int i = i_crossPoint; i < i_genotypeLength; i++)
		{
			pi_genotypeCopy1[i] = pcOther.pt_genotype[i];
			pi_genotypeCopy2[i] = this->pt_genotype[i];
		}

		CIndividual* c_child1 = new CIndividual(i_genotypeLength, pi_genotypeCopy1, pc_problem);
		CIndividual* c_child2 = new CIndividual(i_genotypeLength, pi_genotypeCopy2, pc_problem);
		p_res = std::make_pair(c_child1, c_child2);
	}
	
	return p_res;
}


template<class T>
bool CIndividual<T>::operator>(CIndividual<T>& pcOther)
{
	return (d_fitness > pcOther.d_fitness);
}

template<class T>
bool CIndividual<T>::operator>=(CIndividual<T>& pcOther)
{
	return (d_fitness >= pcOther.d_fitness);
}

template<class T>
bool CIndividual<T>::operator<(CIndividual<T>& pcOther)
{
	return (d_fitness < pcOther.d_fitness);
}

template<class T>
bool CIndividual<T>::operator<=(CIndividual<T>& pcOther)
{
	return (d_fitness <= pcOther.d_fitness);
}

template<class T>
CIndividual<T> * CIndividual<T>::operator+(CIndividual<T> &pcOther)
{
	std::pair<CIndividual*, CIndividual*> p_pair = this->cCross(pcOther);
	CIndividual* pc_res = p_pair.first;
	delete p_pair.second;
	return pc_res;
}

template <>
CIndividual<bool>* CIndividual<bool>::operator^(CIndividual& pcOther)
{
	bool* pb_newGenotype = new bool[this->iGetGenotypeLength()];
	for(int i = 0; i<this->iGetGenotypeLength(); i++)
	{
		if(this->ptGetGenotype()[i] == pcOther.ptGetGenotype()[i])
		{
			pb_newGenotype[i] = false;
		}
		else
		{
			pb_newGenotype[i] = true;
		}
	}

	return new CIndividual<bool>(this->i_genotypeLength, pb_newGenotype, this->pc_problem);
}

template <>
CIndividual<int>* CIndividual<int>::operator^(CIndividual& pcOther)
{
	int* pi_newGenotype = new int[this->iGetGenotypeLength()];
	for(int i = 0; i < i_genotypeLength; i++)
	{
		pi_newGenotype[i] = (this->pt_genotype[i] + pcOther.pt_genotype[i]) / 2;
	}

	return new CIndividual<int>(this->i_genotypeLength, pi_newGenotype, this->pc_problem);
}

template <>
CIndividual<double>* CIndividual<double>::operator^(CIndividual& pcOther)
{
	double* pd_newGenotype = new double[this->iGetGenotypeLength()];
	for (int i = 0; i < i_genotypeLength; i++)
	{
		pd_newGenotype[i] = (this->pt_genotype[i] + pcOther.pt_genotype[i]) / 2.0;
	}

	return new CIndividual<double>(this->i_genotypeLength, pd_newGenotype, this->pc_problem);
}

template<class T>
CIndividual<T>& CIndividual<T>::operator++(int)
{
	this->vMutation();
	return *this;
}

template class CIndividual<int>;
template class CIndividual<double>;
template class CIndividual<bool>;