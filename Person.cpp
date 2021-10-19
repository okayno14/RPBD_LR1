#include "Model.h"

bool Person::containPhoneNumber(PhoneNumber* pn)
{
	for (int i = 0; i < phoneNumbers.size(); i++)
	{
		if (pn == phoneNumbers[i]) return true;
	}
	return false;
}