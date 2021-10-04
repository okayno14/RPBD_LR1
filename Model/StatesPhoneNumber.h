#pragma once
#include "Model.h"

#include <iostream>
using namespace std;

class PhoneNumber;
class Model;

class StatePhoneNumber 
{
public:
	virtual void find(PhoneNumber* pn)=0;
	virtual void add(PhoneNumber* pn)=0;
	virtual void update(PhoneNumber* pn)=0;
	virtual void delObj(PhoneNumber* pn)=0;
	virtual void sync(PhoneNumber* pn)=0;
protected:
	
	Model* model;
};

class StatePhoneNumber_1 : public StatePhoneNumber 
{
public:
	StatePhoneNumber_1(Model* model) { this->model = model; }
	void find(PhoneNumber* pn) {};
	void add(PhoneNumber* pn) 
	{
		model->phoneNumberList.push_back(*pn);
		cout << "add"; 
	};
	void update(PhoneNumber* pn) {};
	void delObj(PhoneNumber* pn) {};
	void sync(PhoneNumber* pn) {};
};