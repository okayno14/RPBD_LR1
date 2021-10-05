#include "Model.h"
Person::Person(int id, int idAddress)
{
	phoneCount = 0;
	this->id = id;
	this->idAddress = idAddress;
}
bool Person::containPhoneNumber(PhoneNumber* pn)
{
	for (int i = 0; i < phoneNumbers.size(); i++)
	{
		if (pn == phoneNumbers[i]) return true;
	}
	return false;
}