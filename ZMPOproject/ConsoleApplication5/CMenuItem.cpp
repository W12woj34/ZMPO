#include "pch.h"
#include "CMenuItem.h"



CMenuItem::CMenuItem()
{
	s_name = c_DEFAULT_NAME;
	s_command = c_DEFAULT_COMMAND;
}

CMenuItem::CMenuItem(std::string sName, std::string sCommand, std::string sPath)
{
	s_name = sName;
	s_command = sCommand;
	s_path = sPath + c_ARROW + s_command;
}

CMenuItem::~CMenuItem()
{
}

std::string CMenuItem::sGetName()
{
	return s_name;
}

std::string CMenuItem::sGetCommand()
{
	return s_command;
}

std::string CMenuItem::sGetPath()
{
	return s_path;
}

std::string CMenuItem::sGetInstance()
{
	return s_instance;
}


