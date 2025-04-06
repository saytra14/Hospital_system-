#pragma once
//#include"patient.h"
#include"car.h"
#include"NPQueue.h"
#include"cancellation.h"
//#include"LinkedQueue.h"
//#include"priQueue.h"
//#include<iostream>

using namespace std;
class organizer;

class hospital {

protected:
	int hospitalID;
	LinkedQueue<patient*> SP;
	priQueue<patient*> EP;
	NPQueue NP;
	LinkedQueue<car*> NC;
	LinkedQueue<car*> SC;
	LinkedQueue<cancellation*>PC;
	LinkedQueue<patient*> SPprint;
	priQueue<patient*> EPprint;
	NPQueue NPprint;
	organizer* org;
public:
	hospital(int HID,organizer*o);
	hospital();
	void sethospitalID(int hid);
	void patientfun(patient P);
	void addscar(car* A);
	void addncar(car* A);
	void addnormalpatient(patient*a);
	void addspecialpatient(patient*a);
	void addemergencypatient(patient* A, int severity);
	int gethospitalid();
	LinkedQueue<patient*>& getsplist(); 
	NPQueue& getnplist();
	priQueue<patient*>& geteplist();
	LinkedQueue<patient*>& getspprintlist();
	NPQueue& getnpprintlist();
	priQueue<patient*>& getepprintlist();
	LinkedQueue<car*>& getnormalcar();
	LinkedQueue<car*>& getspecialcar();
	LinkedQueue<cancellation*>& getcancelledpatient();
	void setnormalcar(LinkedQueue<car*>nc);
	void setspecialcar(LinkedQueue<car*>sc);
	void assign(int t);
	void distribute(patient* p);
	//void sendto(organizer* o,car* c);
	
};

