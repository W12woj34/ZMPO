#include "pch.h"
#include "CCommand.h"

CCommand::CCommand()
{
}


CCommand::~CCommand()
{
}

void CCommand::vRunCommand()
{
	std::cout << c_DEFAULT_COMMAND_N;
}


int CCommand::iGetNumber()
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

int CCommand::iGetNumberWithoutNegatives()
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
			if (i_collectNumber < 0)
			{
				std::cout << c_ERROR_STRING;
				std::cin.ignore(c_ALOT, c_NCHAR);
			}
			else
			{
				std::cin.ignore(c_ALOT, c_NCHAR);
				return i_collectNumber;
			}

		}
	} while (true);

}

std::string CCommand::sGetString()

{

	std::string s_collectString;
	do
	{
		std::cout << c_GIVE_NAME;

		getline(std::cin, s_collectString);
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