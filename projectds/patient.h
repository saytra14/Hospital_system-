#pragma once
#include"LinkedQueue.h"
#include"priQueue.h"
#include<iostream>
using namespace std;
class patient
{
protected:
	int	patientID;
	int hospitalID;
	string patienttype;
	int picktime;
	int requesttime;
	int distance;
	 int waitime;
	 int finishedtime;
	int severity;
public:
	patient();
	patient(string type,int reqtime,int pID,int NHID,int dist);
	patient(string type, int reqtime, int pID, int NHID, int dist,int sev);
	//setters
	void setpatientID(int pid);
	void sethospitalID(int hid);
	void setpatienttype(string type);
	void setpicktime(int pt);
	void setrequesttime(int st);
	void setdistance(int dis);
	void setwaittime();
	void setfinishedtime(int time);
	//getters
	int	getpatientID();
	int getwaittime();
	int getfinishedtime();
	int gethospitalID();
	string getpatienttype();
	int getpicktime();
	int getrequesttime();
	int getdistance();
	int getseverity();
	friend ostream& operator<<(ostream& os, const patient& p);



};

