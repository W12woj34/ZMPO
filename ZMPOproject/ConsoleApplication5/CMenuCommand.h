#pragma once
#include "CMenuItem.h"


class CMenuCommand :
	public CMenuItem
{
public:
	CMenuCommand();
	CMenuCommand(std::string sName, std::string sCommand, std::string sPath, std::string sHelp, CMenuItem * pcParent);
	CMenuCommand(std::string sName, std::string sCommand, std::string sPath, std::string sHelp, CMenuItem * pcParent, CCommand* cCCommand);
	~CMenuCommand();
	void vRun();
	void vAddTask();
	void vDelTask();
	std::string sGetHelp();
	CCommand *pcGetCCommand();



private:
	std::string s_help;
	CCommand * pc_command;
	std::string sGetString();
	int iGetNumber();
};
