#include "pch.h"
#include "CKnapsackProblem.h"


template<class T>
CKnapsackProblem<T>::CKnapsackProblem(double dKnapsackCapacity, std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems, int* piError)
{

	if (cValues.size() <= 0)
	{
		*piError = c_ERROR_NEGATIVE_NUMBER_PROBLEM;
	}
	i_problemSize = cValues.size();

	if(i_problemSize != cValues.size() || i_problemSize != cWeights.size() || i_problemSize != cMaxItems.size())
	{
		*piError = c_ERROR_WRONG_TABLES_SIZE;
		return;
	}
	if(dKnapsackCapacity <= 0)
	{
		*piError = c_ERROR_NEGATIVE_KNAPSACK_CAPACITY;
		return;
	}
	d_knapsackCapacity = dKnapsackCapacity;

	vGenerateItems(cValues, cWeights, cMaxItems);
}

template<class T>
CKnapsackProblem<T>::~CKnapsackProblem()
{
	int i_itemNumber = pc_itemList.size();
	for(int i = 0; i < i_itemNumber; i++)
	{
		delete pc_itemList[i];
	}
	pc_itemList.clear();

}

template <class T>
int CKnapsackProblem<T>::iGetSize()
{
	return i_problemSize;
}

template <class T>
double CKnapsackProblem<T>::dGetMaxItems(int iItemNumber)
{
	return pc_itemList[iItemNumber]->dGetMaxItems();
}

template<class T>
double CKnapsackProblem<T>::dCalculateResult(T* ptGenotype)
{
	double dValue = 0;
	double dWeigth = 0;
	for (int i = 0; i < i_problemSize; i++)
	{
		if(ptGenotype[i] != 0)
		{
			dValue = dValue + pc_itemList[i]->dGetValue() * ptGenotype[i];
			dWeigth = dWeigth + pc_itemList[i]->dGetWeight() * ptGenotype[i];
		}	
	}

	if(dWeigth > d_knapsackCapacity)
	{
		dValue = 0;
	}

	return dValue;
}


template<class T>
void CKnapsackProblem<T>::vGenerateItems(std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems)
{
	for(int i = 0; i < i_problemSize; i++)
	{
		pc_itemList.push_back(new CItem(cValues[i], cWeights[i], cMaxItems[i]));
	}
}

template<class T>
CKnapsackProblem<T>::CItem::CItem(double dValue, double dWeight, double dMaxItems)
{
	d_value = dValue;
	d_weight = dWeight;
	d_maxItems = dMaxItems;

}

template<class T>
CKnapsackProblem<T>::CItem::~CItem()
{
}

template<class T>
double CKnapsackProblem<T>::CItem::dGetValue()
{
	return d_value;
}

template<class T>
double CKnapsackProblem<T>::CItem::dGetWeight()
{
	return d_weight;
}

template<class T>
double CKnapsackProblem<T>::CItem::dGetMaxItems()
{
	return d_maxItems;
}


template class CKnapsackProblem<int>;
template class CKnapsackProblem<double>;
template class CKnapsackProblem<bool>;
