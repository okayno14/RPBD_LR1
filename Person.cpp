#include "Model.h"

bool Person::containPhoneNumber(PhoneNumber* pn)
{
	for (int i = 0; i < phoneNumbers.size(); i++)
	{
		if (phoneNumbers[i]->isEqual(pn)) return true;
	}
	return false;
}