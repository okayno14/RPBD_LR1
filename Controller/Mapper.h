#pragma once
#include "..\Model\Model.h"
class AbstractMapper 
{
	virtual void insertObj();
	virtual void updateObj();
	virtual void deleteObj();
	virtual void findObj();
};

class PersonMapper : public AbstractMapper 
{

};

class AddressMapper : public AbstractMapper 
{

};

class PhoneMapper :public AbstractMapper 
{

};
