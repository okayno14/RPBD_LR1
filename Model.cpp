#pragma once
#include "Model.h"

void Model::addRecord()
{
}
void Model::addPhone(PhoneNumber pn)
{
	this->phoneNumberTable.push_back(pn);

	this->pnMap.setBuf(&phoneNumberTable[0]);

	pnMap.insertObj();
	pnMap.deleteObj();
};