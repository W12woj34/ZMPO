#include "pch.h"
#include "CMenu.h"


CMenu::CMenu()
{

}

CMenu::CMenu(std::string sName, std::string sCommand, std::string sPath, CMenuItem * pcParent) :CMenuItem(sName, sCommand, sPath)
{
	s_instance = c_MENU;
	pc_parent = pcParent;
}


CMenu::~CMenu()
{

	int i_listSize = c_CMenuItemList.size();
	for (int i = 0; i < i_listSize; i++)
	{
		delete c_CMenuItemList[i];
	}
	c_CMenuItemList.clear();

}

void CMenu::vRun()
{
	std::string s_task;
	int i_ignore;
	int i_ListSize;
	do
	{
		i_ignore = 0;
		std::cout << c_MENU_INFO;
		std::cout << c_N;
		std::cout << c_N;
		std::cout << s_path;
		std::cout << c_N;
		std::cout << c_MENU_NAME;
		std::cout << s_name;
		std::cout << c_MENU_COMMAND;
		std::cout << s_command;
		std::cout << c_NN;

		i_ListSize = c_CMenuItemList.size();
		for (int i = 0; i < i_ListSize; i++)
		{
			std::cout << c_MENU_NAME;
			std::cout << c_CMenuItemList[i]->sGetName();
			std::cout << c_MENU_COMMAND;
			std::cout << c_CMenuItemList[i]->sGetCommand();
			std::cout << c_N;
		}
		std::cout << c_N;
		s_task = sGetString();
		std::string s_tmpCommand = s_task;

		if (s_tmpCommand.size() > c_HELP_LENGTH_SPACE)
		{
			s_tmpCommand.erase(s_tmpCommand.begin() + c_HELP_LENGTH_SPACE, s_tmpCommand.end());
			if (s_tmpCommand == c_HELP)
			{
				s_task.erase(s_task.begin(), s_task.begin() + c_HELP_LENGTH_SPACE);
				vHelp(s_task);
				i_ignore = 1;
			}
			else
			{
				s_tmpCommand = s_task;
				if (s_tmpCommand.size() > c_SEEK_LENGTH_SPACE)
				{
					s_tmpCommand.erase(s_tmpCommand.begin() + c_SEEK_LENGTH_SPACE, s_tmpCommand.end());
					if (s_tmpCommand == c_SEARCH)
					{
						s_task.erase(s_task.begin(), s_task.begin() + c_SEEK_LENGTH_SPACE);
						vSearch(s_task, this);
						i_ignore = 1;
					}

				}
			}
		}

		if (i_ignore == 0)
		{

			if (s_task == c_BACK)
			{
				return;
			}

			if (s_task == c_ADD_ELEMENT)
			{
				i_ignore = 1;
				vAddCMenuItem();
			}
			if (s_task == c_DELETE_ELEMENT)
			{
				i_ignore = 1;
				vDelCMenuItem();
			}

			i_ListSize = c_CMenuItemList.size();
			for (int i = 0; i < i_ListSize; i++)
			{
				if (c_CMenuItemList[i]->sGetCommand() == s_task)
				{
					i_ignore = 1;
					c_CMenuItemList[i]->vRun();
				}
			}
			if (i_ignore == 0)
			{
				std::cout << c_ERROR_N;
			}
		}

	} while (true);





}

void CMenu::vAddCMenuItem()
{
	std::cout << c_WHICH_OBJECT_ADD;
	std::string s_task = sGetString();
	std::string s_name;
	std::string s_command;
	if (s_task == c_CMENU)
	{
		std::cout << c_GIVE_NAME_POSITION;
		s_name = sGetString();
		std::cout << c_GIVE_NAME_COMMAND;
		s_command = sGetString();

		if (s_name == c_BACK || s_name == c_ADD_ELEMENT || s_name == c_DELETE_ELEMENT || s_name == c_HELP || s_name == c_SEARCH ||
			s_command == c_BACK || s_command == c_ADD_ELEMENT || s_command == c_DELETE_ELEMENT || s_command == c_HELP || s_command == c_SEARCH ||
			s_name.find(c_APOSTROPHE) != std::string::npos || s_command.find(c_APOSTROPHE) != std::string::npos)
		{
			std::cout << c_ERROR_N;
			return;

		}

		int i_menuSize = c_CMenuItemList.size();
		for (int i = 0; i < i_menuSize; i++)
		{
			if (s_name == c_CMenuItemList[i]->sGetName() || s_command == c_CMenuItemList[i]->sGetCommand())
			{
				std::cout << c_ERROR_N;
				return;
			}
		}

		c_CMenuItemList.push_back(new CMenu(s_name, s_command, s_path, this));
	}
	else if (s_task == c_CMENU_COMMAND)
	{
		std::string s_help;
		std::cout << c_GIVE_NAME_POSITION;
		s_name = sGetString();
		std::cout << c_GIVE_NAME_COMMAND;
		s_command = sGetString();
		std::cout << c_GIVE_DESCRIPTION_CCOMMAND;
		s_help = sGetString();

		if (s_name == c_BACK || s_name == c_ADD_ELEMENT || s_name == c_DELETE_ELEMENT || s_name == c_HELP || s_name == c_SEARCH ||
			s_command == c_BACK || s_command == c_ADD_ELEMENT || s_command == c_DELETE_ELEMENT || s_command == c_HELP || s_command == c_SEARCH ||
			s_name.find(c_APOSTROPHE) != std::string::npos || s_command.find(c_APOSTROPHE) != std::string::npos)
		{
			std::cout << c_ERROR_N;
			return;

		}

		int i_menuSize = c_CMenuItemList.size();
		for (int i = 0; i < i_menuSize; i++)
		{
			if (s_name == c_CMenuItemList[i]->sGetName() || s_command == c_CMenuItemList[i]->sGetCommand())
			{
				std::cout << c_ERROR_N;
				return;
			}
		}
		c_CMenuItemList.push_back(new CMenuCommand(s_name, s_command, s_path, s_help, this));
	}
	else
	{
		std::cout << c_ERROR_N;
	}

}

void CMenu::vAddCMenuItem(CMenuItem* cObject)
{

	if (cObject->sGetName() == c_BACK || cObject->sGetName() == c_ADD_ELEMENT || cObject->sGetName() == c_DELETE_ELEMENT || cObject->sGetName() == c_HELP || cObject->sGetName() == c_SEARCH ||
		cObject->sGetCommand() == c_BACK || cObject->sGetCommand() == c_ADD_ELEMENT || cObject->sGetCommand() == c_DELETE_ELEMENT || cObject->sGetCommand() == c_HELP || cObject->sGetCommand() == c_SEARCH ||
		cObject->sGetName().find(c_APOSTROPHE) != std::string::npos || cObject->sGetCommand().find(c_APOSTROPHE) != std::string::npos)
	{
		std::cout << c_ERROR_N;
		delete cObject;
		return;
	}

	if (cObject->sGetInstance() == c_COMMAND)
	{
		if (((CMenuCommand*)cObject)->sGetHelp().find(c_APOSTROPHE) != std::string::npos)
		{
			std::cout << c_ERROR_N;
			delete cObject;
			return;
		}
	}

	int i_menuSize = c_CMenuItemList.size();
	for (int i = 0; i < i_menuSize; i++)
	{
		if (cObject->sGetName() == c_CMenuItemList[i]->sGetName() || cObject->sGetCommand() == c_CMenuItemList[i]->sGetCommand())
		{
			std::cout << c_ERROR_N;
			delete cObject;
			return;
		}
	}
	c_CMenuItemList.push_back(cObject);

}

void CMenu::vDelCMenuItem()
{
	if (c_CMenuItemList.empty() != true)
	{
		std::string s_command;
		int i_position = -1;
		std::cout << c_COMMAND_POSITION_TO_DELETE;
		s_command = sGetString();
		int i_ListSize = c_CMenuItemList.size();
		for (int i = 0; i < i_ListSize; i++)
		{
			if (c_CMenuItemList[i]->sGetCommand() == s_command)
			{
				i_position = i;
			}
		}

		if (i_position == -1)
		{
			std::cout << c_ERROR_N;
		}
		else
		{
			delete c_CMenuItemList[i_position];
			c_CMenuItemList.erase(c_CMenuItemList.begin() + i_position);
		}
	}
	else
	{
		std::cout << c_EMPTY_MENU;
	}

}

void CMenu::vHelp(std::string sName)
{
	int i_listSize = c_CMenuItemList.size();
	for (int i = 0; i < i_listSize; i++)
	{
		if (c_CMenuItemList[i]->sGetInstance() == c_COMMAND)
		{
			if (c_CMenuItemList[i]->sGetName() == sName)
			{
				std::cout << ((CMenuCommand*)c_CMenuItemList[i])->sGetHelp() << c_NN;
				return;
			}
		}
	}
	std::cout << c_COMMAND_ABSENCE << c_NN;
}

void CMenu::vSearch(std::string sCommand, CMenu* cMenu)
{
	while (cMenu->pc_parent != nullptr)
	{
		vSearch(sCommand, (CMenu*)cMenu->pc_parent);
		return;
	}

	vSearchMainMenu(sCommand, cMenu);
}

void CMenu::vSearchMainMenu(std::string sCommand, CMenu* cMenu)
{

	int i_listSize = cMenu->c_CMenuItemList.size();
	for (int i = 0; i < i_listSize; i++)
	{

		if (cMenu->c_CMenuItemList[i]->sGetCommand() == sCommand)
		{
			std::cout << cMenu->c_CMenuItemList[i]->sGetPath() << c_N;
		}

		if (cMenu->c_getCMenuList()->operator[](i)->sGetInstance() == c_MENU)
		{
			vSearchMainMenu(sCommand, (CMenu*)cMenu->c_CMenuItemList[i]);
		}
	}
}


void CMenu::vSaveTree(CMenu* cMenu)
{
	while (cMenu->pc_parent != nullptr)
	{
		vSaveTree((CMenu*)cMenu->pc_parent);
		return;
	}

	std::string s_tree = sCMenuToString(c_EMPTY, cMenu);
	std::fstream r_file;
	r_file.open(c_FILE_NAME, std::ios::out);

	if (r_file.is_open() == true && r_file.good() == true)
	{
		r_file << s_tree;
		std::cout << c_SAVED << c_NN;
		r_file.close();

	}
	else
	{
		std::cout << c_LACK_OF_FILE_ACCESS << c_NN;
		r_file.close();
	}
}

std::string CMenu::sCMenuToString(std::string sTree, CMenu* cMenu)
{
	sTree = sTree + c_MENU_START_SYMBOL_APOSTROPHE + cMenu->s_name + c_COMA_BETWEEN_APOSTROPHE + cMenu->s_command + c_APOSTROPHE_SEMICOLON;
	int i_listSize = cMenu->c_CMenuItemList.size();
	for (int i = 0; i < i_listSize; i++)
	{
		if (cMenu->c_CMenuItemList[i]->sGetInstance() == c_MENU)
		{
			sTree = sCMenuToString(sTree, (CMenu*)cMenu->c_CMenuItemList[i]);
		}
		if (cMenu->c_CMenuItemList[i]->sGetInstance() == c_COMMAND)
		{
			sTree = sCMenuCommandToString(sTree, (CMenuCommand*)cMenu->c_CMenuItemList[i]);
		}
		if (i < i_listSize - 1)
		{
			sTree = sTree + c_COMA;
		}
	}
	sTree = sTree + c_MENU_END_SYMBOL;

	return sTree;
}

std::string CMenu::sCMenuCommandToString(std::string sTree, CMenuCommand* cMenuCommand)
{
	sTree = sTree + c_COMMAND_START_SYMBOL_APOSTROPHE + cMenuCommand->sGetName() + c_COMA_BETWEEN_APOSTROPHE + cMenuCommand->sGetCommand() + c_COMA_BETWEEN_APOSTROPHE + cMenuCommand->sGetHelp() + c_COMMAND_END_SYMBOL_APOSTROPHE;

	return sTree;
}


CMenu* CMenu::cReadTree()
{
	if (this->pc_parent != nullptr)
	{

		std::cout << c_NO_ROOT;
		return this;
	}

	int pi_error = 0;
	std::string s_treeAnalised = c_EMPTY;
	std::string s_treeToAnalise;
	std::fstream r_file;

	r_file.open(c_FILE_NAME, std::ios::in);

	if (r_file.is_open() == true && r_file.good() == true)
	{
		std::getline(r_file, s_treeToAnalise);
		r_file.close();

	}
	else
	{
		std::cout << c_LACK_OF_FILE_ACCESS << c_NN;
		r_file.close();
		return this;
	}
	if (s_treeToAnalise.operator[](0) != c_MENU_START_SYMBOL)
	{
		std::cout << c_EXPECTED_MENU_START_SYMBOL_ON_BEGIN;
		return this;
	}
	s_treeAnalised = s_treeAnalised + s_treeToAnalise.operator[](0);
	s_treeToAnalise.erase(s_treeToAnalise.begin());

	CMenu* c_mainMenu = cReadCMenu(&s_treeAnalised, &s_treeToAnalise, &pi_error, nullptr);

	if (s_treeToAnalise.empty() != true && pi_error != c_ERROR)
	{
		std::cout << c_UNEXPECTED_SYMBOLS << s_treeAnalised;
		delete c_mainMenu;
		return this;
	}

	if (pi_error == c_ERROR)
	{
		delete c_mainMenu;
		return this;
	}

	std::cout << c_LOADED;
	delete this;
	return c_mainMenu;

}

CMenu* CMenu::cReadCMenu(std::string *psTreeAnalised, std::string *psTreeToAnalise, int *piError, CMenuItem *pcParent)
{
	char c_tmp;
	std::string s_name;
	std::string s_command;


	if (psTreeToAnalise->operator[](0) == c_APOSTROPHE)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

		while (psTreeToAnalise->operator[](0) != c_APOSTROPHE)
		{
			if (psTreeToAnalise->empty() == true)
			{
				std::cout << c_EXPECTED_SYMBOL_NAME_END_MENU << psTreeAnalised[0];
				*piError = c_ERROR;
				return nullptr;
			}
			c_tmp = psTreeToAnalise->operator[](0);
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());

			s_name = s_name + c_tmp;
		}

		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_NAME_BEGIN_MENU << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;
	}

	if (psTreeToAnalise->operator[](0) == c_COMA)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());
	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_NAME_MENU << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;

	}

	if (psTreeToAnalise->operator[](0) == c_APOSTROPHE)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

		while (psTreeToAnalise->operator[](0) != c_APOSTROPHE)
		{
			if (psTreeToAnalise->empty() == true)
			{
				std::cout << c_EXPECTED_SYMBOL_COMMAND_END_MENU << psTreeAnalised[0];
				*piError = c_ERROR;
				return nullptr;
			}
			c_tmp = psTreeToAnalise->operator[](0);
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());

			s_command = s_command + c_tmp;
		}

		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_COMMAND_BEGIN_MENU << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;
	}


	if (psTreeToAnalise->operator[](0) == c_SEMICOLON)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());
	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_DECLARATION << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;

	}
	CMenu *c_menu;
	if (pcParent == nullptr)
	{
		c_menu = new CMenu(s_name, s_command, c_EMPTY, pcParent);
	}
	else
	{
		c_menu = new CMenu(s_name, s_command, pcParent->sGetPath(), pcParent);
	}

	while (psTreeToAnalise->operator[](0) != c_SEMICOLON)
	{
		if (psTreeToAnalise->empty() == true)
		{
			std::cout << c_EXPECTED_END_MENU << psTreeAnalised[0];
			*piError = c_ERROR;
			return nullptr;
		}

		if (psTreeToAnalise->operator[](0) == c_MENU_START_SYMBOL)
		{
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());
			c_menu->c_getCMenuList()->push_back(cReadCMenu(psTreeAnalised, psTreeToAnalise, piError, c_menu));

			if (*piError == c_ERROR)
			{
				delete c_menu;
				return nullptr;
			}

		}
		else if (psTreeToAnalise->operator[](0) == c_COMMAND_START_SYMBOL)
		{
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());
			c_menu->c_getCMenuList()->push_back(cReadCMenuCommand(psTreeAnalised, psTreeToAnalise, piError, c_menu));

			if (*piError == c_ERROR)
			{
				delete c_menu;
				return nullptr;
			}
		}

		else
		{
			std::cout << c_EXPECTED_END_MENU << psTreeAnalised[0];
			*piError = c_ERROR;
			delete c_menu;
			return nullptr;
		}

		if (psTreeToAnalise->operator[](0) == c_COMA && (psTreeToAnalise->operator[](1) == c_MENU_START_SYMBOL || psTreeToAnalise->operator[](1) == c_COMMAND_START_SYMBOL))
		{
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());
		}
		else if (psTreeToAnalise->operator[](0) == c_MENU_START_SYMBOL || psTreeToAnalise->operator[](0) == c_COMMAND_START_SYMBOL)
		{
			std::cout << c_EXPECTED_SYMBOL_CHILD << psTreeAnalised[0];
			*piError = c_ERROR;
			delete c_menu;
			return nullptr;
		}

	}

	if (psTreeToAnalise->operator[](0) == c_SEMICOLON)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());
		std::string s_number;

		while (psTreeToAnalise->operator[](0) != c_MENU_END_SYMBOL)
		{
			s_number = s_number + psTreeToAnalise->operator[](0);
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());
		}

		int i_number;
		try
		{
			i_number = std::stoi(s_number);
			std::ostringstream s_stream;
			s_stream << i_number;
			std::string s_number2 = s_stream.str();

			if (s_number != s_number2)
			{
				std::cout << c_EXPECTED_INT << psTreeAnalised[0];
				*piError = c_ERROR;
				delete c_menu;
				return nullptr;
			}
		}
		catch (const std::exception&)
		{
			std::cout << c_EXPECTED_INT << psTreeAnalised[0];
			*piError = c_ERROR;
			delete c_menu;
			return nullptr;
		}


		if (i_number != c_menu->c_getCMenuList()->size())
		{
			std::cout << c_WRONG_CHILDREN_NUMBER << psTreeAnalised[0];
			*piError = c_ERROR;
			delete c_menu;
			return nullptr;
		}

	}
	psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
	psTreeToAnalise->erase(psTreeToAnalise->begin());

	return c_menu;
}

CMenuCommand* CMenu::cReadCMenuCommand(std::string *psTreeAnalised, std::string *psTreeToAnalise, int *piError, CMenuItem *pcParent)
{

	char c_tmp;
	std::string s_name;
	std::string s_command;
	std::string s_help;


	if (psTreeToAnalise->operator[](0) == c_APOSTROPHE)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

		while (psTreeToAnalise->operator[](0) != c_APOSTROPHE)
		{
			if (psTreeToAnalise->empty() == true)
			{
				std::cout << c_EXPECTED_SYMBOL_NAME_END_COMMAND << psTreeAnalised[0];
				*piError = c_ERROR;
				return nullptr;
			}
			c_tmp = psTreeToAnalise->operator[](0);
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());

			s_name = s_name + c_tmp;
		}

		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_NAME_BEGIN_COMMAND << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;
	}

	if (psTreeToAnalise->operator[](0) == c_COMA)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());
	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_NAME_COMMAND << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;

	}


	if (psTreeToAnalise->operator[](0) == c_APOSTROPHE)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

		while (psTreeToAnalise->operator[](0) != c_APOSTROPHE)
		{
			if (psTreeToAnalise->empty() == true)
			{
				std::cout << c_EXPECTED_SYMBOL_COMMAND_END_COMMAND << psTreeAnalised[0];
				*piError = c_ERROR;
				return nullptr;
			}
			c_tmp = psTreeToAnalise->operator[](0);
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());

			s_command = s_command + c_tmp;
		}

		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_COMMAND_BEGIN_COMMAND << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;
	}

	if (psTreeToAnalise->operator[](0) == c_COMA)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());
	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_COMMAND_COMMAND << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;

	}

	if (psTreeToAnalise->operator[](0) == c_APOSTROPHE)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

		while (psTreeToAnalise->operator[](0) != c_APOSTROPHE)
		{
			if (psTreeToAnalise->empty() == true)
			{
				std::cout << c_EXPECTED_SYMBOL_HELP_END_COMMAND << psTreeAnalised[0];
				*piError = c_ERROR;
				return nullptr;
			}
			c_tmp = psTreeToAnalise->operator[](0);
			psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
			psTreeToAnalise->erase(psTreeToAnalise->begin());

			s_help = s_help + c_tmp;
		}

		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());

	}
	else
	{
		std::cout << c_EXPECTED_SYMBOL_HELP_BEGIN_COMMAND << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;
	}

	if (psTreeToAnalise->operator[](0) == c_COMMAND_END_SYMBOL)
	{
		psTreeAnalised[0] = psTreeAnalised[0] + psTreeToAnalise->operator[](0);
		psTreeToAnalise->erase(psTreeToAnalise->begin());
	}
	else
	{
		std::cout << c_EXPECTED_END_COMMAND << psTreeAnalised[0];
		*piError = c_ERROR;
		return nullptr;
	}

	CMenuCommand *c_COMMAND = new CMenuCommand(s_name, s_command, pcParent->sGetPath(), s_help, pcParent);

	return c_COMMAND;
}

std::vector<CMenuItem*> *CMenu::c_getCMenuList()
{
	return &c_CMenuItemList;
}

std::string CMenu::sGetString()
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
