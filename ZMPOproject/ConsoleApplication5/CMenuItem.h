#pragma once
#include <string>
#include <vector>
#include "Constants.h"
#include "CCommand.h"

class CMenuItem
{
public:

	CMenuItem();
	CMenuItem(std::string sName, std::string sCommand, std::string sPath);
	virtual ~CMenuItem();
	virtual void vRun() = 0;
	virtual std::string sGetName();
	virtual std::string sGetCommand();
	virtual std::string sGetPath();
	virtual std::string sGetInstance();

private:




protected:
	std::string s_command;
	std::string s_name;
	std::string s_path;
	std::string s_instance;
	CMenuItem * pc_parent;


};

