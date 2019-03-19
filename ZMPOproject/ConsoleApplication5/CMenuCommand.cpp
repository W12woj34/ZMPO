#include "pch.h"
#include "CMenuCommand.h"



CMenuCommand::CMenuCommand()
{
	s_instance = c_COMMAND;
	pc_command = nullptr;
}

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sPath, std::string sHelp, CMenuItem * pcParent) :CMenuItem(sName, sCommand, sPath)
{
	s_instance = c_COMMAND;
	pc_parent = pcParent;
	pc_command = nullptr;
	s_help = sHelp;
}

CMenuCommand::CMenuCommand(std::string sName, std::string sCommand, std::string sPath, std::string sHelp, CMenuItem * pcParent, CCommand* cCCommand) :CMenuItem(sName, sCommand, sPath)
{
	s_instance = c_COMMAND;
	pc_parent = pcParent;
	pc_command = cCCommand;
	s_help = sHelp;
}


CMenuCommand::~CMenuCommand()
{
	delete pc_command;
}

void CMenuCommand::vRun()
{
	std::cout << c_QUESTION_EDIT;
	std::string s_task = sGetString();
	if (s_task == c_YES)
	{
		std::cout << c_CCOMMAND_WHAT_TO_EDIT;
		s_task = sGetString();
		if (s_task == c_ADD)
		{
			vAddTask();
			if (pc_command != nullptr)
			{
				std::cout << c_QUEST_ADDED;
			}

		}
		else if (s_task == c_DELETE)
		{
			vDelTask();
			std::cout << c_QUEST_DELETED;
		}
		else
		{
			std::cout << c_ERROR_BACK;
		}
		return;
	}

	if (pc_command != nullptr)
	{
		pc_command->vRunCommand();
	}
	else
	{
		std::cout << c_EMPTY_COMMAND;
	}

}

void CMenuCommand::vAddTask()
{
	if (pc_command != nullptr)
	{
		delete pc_command;
		pc_command = nullptr;
	}
	pc_command = new CCommand();

}

void CMenuCommand::vDelTask()
{
	delete pc_command;
	pc_command = nullptr;
}

CCommand* CMenuCommand::pcGetCCommand()
{
	return pc_command;
}


std::string CMenuCommand::sGetString()
{

	std::string s_collectString;
	do
	{
		std::cout << c_GIVE_NAME;

		getline(std::cin, s_collectString);
		std::cout << s_collectString;
		if (std::cin.fail() == true)
		{
			std::cout << c_ERROR_STRING;
			std::cin.clear();
			std::cin.ignore(c_ALOT, c_NCHAR);
		}
		else
		{
			return s_collectString;
		}
	} while (true);

}

std::string CMenuCommand::sGetHelp()
{
	return s_help;
}

int CMenuCommand::iGetNumber()
{

	int i_collectNumber;
	do
	{
		std::cout << c_GIVE_NUMBER;

		std::cin >> i_collectNumber;
		if (std::cin.fail() == true)
		{
			std::cout << c_ERROR_STRING;
			std::cin.clear();
			std::cin.ignore(c_ALOT, c_NCHAR);
		}
		else
		{
			std::cin.ignore(c_ALOT, c_NCHAR);
			return i_collectNumber;

		}
	} while (true);

}
