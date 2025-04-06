#include "cancellation.h"

cancellation::cancellation()
{
}

cancellation::cancellation(int pID, int hID, int cT)
{
	patientid = pID;
	hospitalid = hID;
	canceltime = cT;
}

void cancellation::setpatientID(int pid)
{
	patientid = pid;
}

void cancellation::sethospitalid(int hid)
{
	hospitalid = hid;

}

void cancellation::setcanceltime(int reqtime)
{
	canceltime = reqtime;

}

int cancellation::getpatientid()
{
	return patientid;
}

int cancellation::gethospitalid()
{
	return hospitalid;
}

int cancellation::getcanceltime()
{
	return canceltime;
}
