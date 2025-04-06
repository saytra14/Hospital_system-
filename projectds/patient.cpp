#include "patient.h"
#include"LinkedQueue.h"
#include"priQueue.h"
#include<iostream>

patient::patient()
{

}

patient::patient(string type, int reqtime, int pID, int NHID, int dist)
{
	patienttype = type;
	requesttime = reqtime;
	patientID = pID;
	hospitalID = NHID;
	distance = dist;
	waitime = 0;
	picktime = 0;
}

patient::patient(string type, int reqtime, int pID, int NHID, int dist, int sev)
{

	patienttype = type;
	requesttime = reqtime;
	patientID = pID;
	hospitalID = NHID;
	distance = dist;
	severity = sev;
	waitime = 0;
	picktime = 0;
}
//OPERATOR OVERLOADER
// ostream& operator<<(ostream& os, const patient & p)
//{
//	 cout<<"patient type = "<< p.patienttype
//}

void patient::setpatientID(int pid)
{
	patientID = pid;
}

void patient::sethospitalID(int hid)
{
	hospitalID = hid;
}

void patient::setpatienttype(string type)
{
	patienttype = type;
}

void patient::setpicktime(int pt)
{
	picktime = pt;

}

void patient::setrequesttime(int st)
{
	requesttime = st;
}

void patient::setdistance(int dis)
{
	distance = dis;
}

void patient::setwaittime()
{
	waitime = -(picktime - requesttime);
}

void patient::setfinishedtime(int time)
{
	finishedtime = time;
}

int patient::getpatientID()
{
	return patientID;
}

int patient::getwaittime()
{
	return waitime;
}

int patient::getfinishedtime()
{
	return finishedtime;
}

int patient::gethospitalID()
{
	return hospitalID;
}

string patient::getpatienttype()
{
	return patienttype;
}



int patient::getpicktime()
{
	return picktime ;
}

int patient::getrequesttime()
{
	return requesttime;
}

int patient::getdistance()
{
	return distance;
}

int patient::getseverity()
{
	return severity;
}

ostream& operator<<(ostream& os, const patient& p)
{
	//cout << "patient type : " << p.patienttype << endl;
	cout << p.patientID<<",";
	//cout << " request time :" << p.requesttime << endl;
	//cout << "distance: " << p.distance << endl;
	//if (p.patienttype == "EP") {
	//	cout << " severity : " << p.severity << endl;
	//}
	//cout << "nearest hospital id:" << p.hospitalID << endl;
	return os;
}
