#pragma once
#include <iostream>
#include "Constants.h"

class CCommand
{
public:
	CCommand();
	virtual ~CCommand();
	virtual void vRunCommand();


protected:
	virtual int iGetNumber();
	virtual int iGetNumberWithoutNegatives();
	virtual std::string sGetString();

};

