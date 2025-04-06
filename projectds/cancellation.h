#pragma once
#include"LinkedQueue.h"
#include"priQueue.h"
#include<iostream>
using namespace std;
class cancellation
{
protected:
	int patientid;
	int hospitalid;
	int canceltime;
public:
	cancellation();
	cancellation(int pID, int hID, int cancelTime);
	void setpatientID(int pid);
	void sethospitalid(int hid);
	void setcanceltime(int reqtime);
	int getpatientid();
	int gethospitalid();
	int getcanceltime();
};

