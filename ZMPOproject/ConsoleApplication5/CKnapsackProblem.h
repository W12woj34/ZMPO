#pragma once
#include <vector>
#include "Constants.h"

template<class T>
class CGeneticAlgorithm;


template<class T>
class CKnapsackProblem
{

	class CItem
	{
	public:
		CItem(double dValue, double dWeight, double dMaxItems);
		~CItem();
		double dGetValue();
		double dGetWeight();
		double dGetMaxItems();

	private:
		double d_value;
		double d_weight;
		double d_maxItems;
	};


public:
	CKnapsackProblem(double dKnapsackCapacity, std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems, int* piError);
	~CKnapsackProblem();
	int iGetSize();
	double dGetMaxItems(int iItemNumber);
	double dCalculateResult(T* ptGenotype);
	void vGenerateItems(std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems);


private:
	int i_problemSize;
	double d_knapsackCapacity;
	std::vector<CItem*> pc_itemList{};



};

//#include "CKnapsackProblem.cpp"

