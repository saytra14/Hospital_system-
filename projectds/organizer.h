#pragma once
using namespace std;
//#include<iostream>
//#include"LinkedQueue.h"
//#include"priQueue.h"
#include"car.h"
#include <fstream>
#include "hospital.h"
#include"cancellation.h"
#include"extpriQueue.h"
class organizer
{
protected:
	
	int Hospitalnumb;
	int carspeed_sc;
	int carspeed_nc;
	int** distancesmatrix;
	int NCnumb;
	int SCnumb;
	int totalrequests;
	int patientID;
	string requesttype;
	int requesttime;
	int nearhospitalID;
	int  hospitalID;
	int  distancenear; //distance to nearest hospital
	int numCancelledrequest;//total
	int  cancellationtime;
	int  cancelled_PID;
	int probabilityfailure;
	int backnumber;
	int outcarsnumber;
	int cancelledpatients;
	int SCCount;
	int NcCount;
	int TIMESTEP ;
	int countFinish;
	int TotalNP;
	int TotalSP;
	int TotalEP;
	hospital** hospital_list;
	LinkedQueue<car*> NC;
	LinkedQueue<car*> SC;
	priQueue<car*>backcars;
	extpriQueue<car*>outcars;
	priQueue<car*>checkup;
	LinkedQueue<patient*>finishedlist;
	LinkedQueue<patient*>requesteplist;
	LinkedQueue<patient*>requestsplist;
	LinkedQueue<patient*>requestnplist;
	LinkedQueue<cancellation*>cancellationlist;

public:
	organizer();
	void load(string filename);
	LinkedQueue<patient*>getrequestnplist();
	//void runsimulation(bool interactive);
	void save();
	void receive(hospital* h);
	void freetoOut(car*c,int t);
	void OutToBack(int t);
	void BackToFree(int t);
	void cancelrequest(int t);
	void handle(patient* p, int s);
	void simulator(bool mode);
	void print(int t);
	void failaction(car* car);
	void printcheckup();
//	void checkuptofree();
//	void backtocheck(car* car);

};


