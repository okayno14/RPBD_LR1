#pragma once
#include "Model.h"


Person::Person(SQLWCHAR* lastName, SQLWCHAR* firstName, SQLWCHAR* fatherName)
{
	wcscpy_s(this->fatherName, fatherName);
	wcscpy_s(this->lastName, lastName);
	wcscpy_s(this->firstName, firstName);
};
bool Person::isEqual(const Person* b)
{
	const SQLWCHAR* a_lastname = this->lastName;
	const SQLWCHAR* a_firstname = this->firstName;
	const SQLWCHAR* a_fathername = this->fatherName;

	const SQLWCHAR* b_lastname = b->lastName;
	const SQLWCHAR* b_firstname = b->firstName;
	const SQLWCHAR* b_fathername = b->fatherName;

	if
		(
			wcscmp(a_lastname, b_lastname) == 0 &&
			wcscmp(a_firstname, b_firstname) == 0 &&
			wcscmp(a_fathername, b_fathername) == 0
			)
		return true;
	else return false;
};
bool Person::containPhoneNumber(PhoneNumber* pn)
{
	for (int i = 0; i < phoneNumbers.size(); i++)
	{
		if (phoneNumbers[i]->isEqual(pn)) return true;
	}
	return false;
};

bool Person::containAddress(Address* ad)
{
	return this->address->isEqual(ad);
};

void Person::addPhoneNumber(PhoneNumber* pn)
{
	this->phoneNumbers.push_back(pn);
	this->idPhones.push_back(phoneNumbers.back()->getId());
};
void Person::setPhoneNumber(int pos, PhoneNumber* pn)
{
	if (pos < phoneNumbers.size())
	{
		phoneNumbers[pos] = pn;
		idPhones[pos] = pn->getId();
	}
}
SQLWCHAR* Person::getLastName()
{
	return this->lastName;
}
SQLWCHAR* Person::getFirstName()
{
	return this->firstName;
}
SQLWCHAR* Person::getFatherName()
{
	return this->fatherName;
};

void Person::setAddress(Address* add)
{
	this->address = add;
	this->idAddress = add->getId();
}
std::vector<PhoneNumber*> Person::getNumbers()
{
	return phoneNumbers;
};
