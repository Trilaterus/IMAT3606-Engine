#ifndef CPCONTROLLABLE_H
#define CPCONTROLLABLE_H

#include <vector>
#include "EventManager.h"

class CPControllable
{
private:
	std::vector<int> m_viKeys;
	int m_iCurrentKey;

public:
	CPControllable();

	//void setKeyListener(int iKey);

	int onKeyPress();
};

#endif