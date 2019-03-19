#pragma once
#include "CCommand.h"
#include <vector>
#include "CKnapsackProblem.h"
#include "CGeneticAlgorithm.h"

class CCommandAlgorithm :
	public CCommand
{
public:
	CCommandAlgorithm(std::vector<double> cValues, std::vector<double> cWeights);
	~CCommandAlgorithm();
	virtual void vRunCommand();
	

protected:
	std::vector<double> c_values{};
	std::vector<double> c_weights{};
	std::vector<double> c_maxItems{};
	std::string sGetError(int iError);
};

class CCommandAlgorithmInt :
	public CCommandAlgorithm
{
public:
	CCommandAlgorithmInt(std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems);
	~CCommandAlgorithmInt();
	void vRunCommand();

	

};

class CCommandAlgorithmDouble :
	public CCommandAlgorithm
{
public:
	CCommandAlgorithmDouble(std::vector<double> cValues, std::vector<double> cWeights, std::vector<double> cMaxItems);
	~CCommandAlgorithmDouble();
	void vRunCommand();

};

class CCommandAlgorithmBool :
	public CCommandAlgorithm
{
public:
	CCommandAlgorithmBool(std::vector<double> cValues, std::vector<double> cWeights);
	~CCommandAlgorithmBool();
	void vRunCommand();

	
};

