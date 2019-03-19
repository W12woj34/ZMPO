#include "pch.h"
#include "CCommandAlgorithm.h"


CCommandAlgorithm::CCommandAlgorithm(std::vector<double> cValues, std::vector<double> cWeights)
{
	c_values = cValues;
	c_weights = cWeights;
}

CCommandAlgorithm::~CCommandAlgorithm()
{
}

void CCommandAlgorithm::vRunCommand()
{
}

std::string CCommandAlgorithm::sGetError(int iError)
{
	switch (iError)
	{
	case c_ERROR_CPROBLEM_NULL:
		return c_ERROR_CPROBLEM_NULL_COMMAND;

	case c_ERROR_NEGATIVE_NUMBER_PROBLEM:
		return c_ERROR_NEGATIVE_NUMBER_PROBLEM_COMMAND;

	case c_ERROR_NEGATIVE_TOURNAMENT_SIZE:
		return c_ERROR_NEGATIVE_TOURNAMENT_SIZE_COMMAND;

	case c_ERROR_NEGATIVE_KNAPSACK_CAPACITY:
		return c_ERROR_NEGATIVE_KNAPSACK_CAPACITY_COMMAND;

	case c_ERROR_NEGATIVE_MAX_ITER:
		return c_ERROR_NEGATIVE_MAX_ITER_COMMAND;

	case c_ERROR_NEGATIVE_POP_SIZE:
		return c_ERROR_NEGATIVE_POP_SIZE_COMMAND;

	case c_ERROR_WRONG_MUT_PROB:
		return c_ERROR_WRONG_MUT_PROB_COMMAND;

	case c_ERROR_WRONG_CROSS_PROB:
		return c_ERROR_WRONG_CROSS_PROB_COMMAND;

	case c_ERROR_WRONG_TABLES_SIZE:
		return c_ERROR_WRONG_TABLES_SIZE_COMMAND;

	case c_ERROR_WRONG_TIME_LIMIT:
		return c_ERROR_WRONG_TIME_LIMIT_COMMAND;
	default:
		return c_UNDEFINED_ERROR;
	}
}

CCommandAlgorithmInt::CCommandAlgorithmInt(std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems):CCommandAlgorithm(cValues, cWeights)
{
	c_maxItems = cMaxItems;
}

CCommandAlgorithmInt::~CCommandAlgorithmInt()
{
}

void CCommandAlgorithmInt::vRunCommand()
{

	int i_error = c_NO_ERROR;

	CKnapsackProblem<int>* pc_problem = new CKnapsackProblem<int>(c_KNAPSACK_CAPACITY, c_values, c_weights, c_maxItems, &i_error);

	if (i_error != 0)
	{
		delete pc_problem;
		std::cout << sGetError(i_error);
		return;
	}

	CGeneticAlgorithm<int>* pc_algorithm = new CGeneticAlgorithm<int>(c_POP_SIZE, c_CROSS_PROB, c_MUT_PROB, c_MAX_TIME, c_TOURNAMENT_SIZE, &i_error, pc_problem);

	if (i_error != 0)
	{
		delete pc_problem;
		delete pc_algorithm;
		std::cout << sGetError(i_error);
		return;
	}

	std::pair<int*, double> p_winner = pc_algorithm->cSolveProblem();
	int i_size = pc_problem->iGetSize();
	for (int i = 0; i < i_size; i++)
	{
		std::cout << p_winner.first[i];
	}
	double d_result = p_winner.second;

	delete pc_problem;
	delete pc_algorithm;
	std::cout << c_NEW_LINE << d_result;

}

CCommandAlgorithmDouble::CCommandAlgorithmDouble(std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems) :CCommandAlgorithm(cValues, cWeights)
{
	c_maxItems = cMaxItems;
}

CCommandAlgorithmDouble::~CCommandAlgorithmDouble()
{
}

void CCommandAlgorithmDouble::vRunCommand()
{
	int i_error = c_NO_ERROR;

	CKnapsackProblem<double>* pc_problem = new CKnapsackProblem<double>(c_KNAPSACK_CAPACITY, c_values, c_weights, c_maxItems, &i_error);

	if (i_error != 0)
	{
		delete pc_problem;
		std::cout << sGetError(i_error);
		return;
	}

	CGeneticAlgorithm<double>* pc_algorithm = new CGeneticAlgorithm<double>(c_POP_SIZE, c_CROSS_PROB, c_MUT_PROB, c_MAX_TIME, c_TOURNAMENT_SIZE, &i_error, pc_problem);

	if (i_error != 0)
	{
		delete pc_problem;
		delete pc_algorithm;
		std::cout << sGetError(i_error);
		return;
	}

	std::pair<double*, double> p_winner = pc_algorithm->cSolveProblem();
	int i_size = pc_problem->iGetSize();
	for (int i = 0; i < i_size; i++)
	{
		std::cout << p_winner.first[i];
	}
	double d_result = p_winner.second;

	delete pc_problem;
	delete pc_algorithm;
	std::cout << c_NEW_LINE << d_result;


}

CCommandAlgorithmBool::CCommandAlgorithmBool(std::vector<double> cValues, std::vector<double> cWeights) :CCommandAlgorithm(cValues, cWeights)
{
	while (c_maxItems.size() != c_values.size())
	{
		c_maxItems.push_back(1);
	}
}

CCommandAlgorithmBool::~CCommandAlgorithmBool()
{
}

void CCommandAlgorithmBool::vRunCommand()
{


	int i_error = c_NO_ERROR;

	CKnapsackProblem<bool>* pc_problem = new CKnapsackProblem<bool>(c_KNAPSACK_CAPACITY, c_values, c_weights, c_maxItems, &i_error);

	if (i_error != 0)
	{
		delete pc_problem;
		std::cout << sGetError(i_error);
		return;
	}

	CGeneticAlgorithm<bool>* pc_algorithm = new CGeneticAlgorithm<bool>(c_POP_SIZE, c_CROSS_PROB, c_MUT_PROB, c_MAX_TIME, c_TOURNAMENT_SIZE, &i_error, pc_problem);

	if (i_error != 0)
	{
		delete pc_problem;
		delete pc_algorithm;
		std::cout << sGetError(i_error);
		return;
	}

	std::pair<bool*, double> p_winner = pc_algorithm->cSolveProblem();
	int i_size = pc_problem->iGetSize();
	for (int i = 0; i < i_size; i++)
	{
		std::cout << p_winner.first[i];
	}
	double d_result = p_winner.second;

	delete pc_problem;
	delete pc_algorithm;
	std::cout << c_NEW_LINE << d_result;

}
