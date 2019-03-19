#pragma once
#include "CMenuCommand.h"
#include <fstream>
#include <sstream>

class CMenu :
	public CMenuItem
{
public:
	CMenu();
	CMenu(std::string sName, std::string sCommand, std::string sPath, CMenuItem * pcParent);
	~CMenu();
	void vRun();
	void vAddCMenuItem();
	void vAddCMenuItem(CMenuItem* cObject);
	void vDelCMenuItem();
	void vHelp(std::string sName);
	void vSearch(std::string sCommand, CMenu* cMenu);
	void vSaveTree(CMenu* cMenu);
	std::vector<CMenuItem*> *c_getCMenuList();
	CMenu* cReadTree();



private:
	std::vector<CMenuItem*> c_CMenuItemList{};
	void vSearchMainMenu(std::string sCommand, CMenu* cMenu);
	std::string sCMenuToString(std::string sTree, CMenu* cMenu);
	std::string sCMenuCommandToString(std::string sTree, CMenuCommand* cMenuCommand);
	std::string sGetString();
	CMenu* cReadCMenu(std::string* s_treeAnalised, std::string* s_treeToAnalise, int* pi_error, CMenuItem *pc_parent);
	CMenuCommand * cReadCMenuCommand(std::string * s_treeAnalised, std::string * s_treeToAnalise, int * pi_error, CMenuItem *pc_parent);


};

