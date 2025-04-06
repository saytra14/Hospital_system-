#pragma once
#include"patient.h"
using namespace std;
//#include<iostream>
//#include"LinkedQueue.h"
//#include"priQueue.h"
class car
{
protected:
	string cartype;
	string car_status;
	int carspeed;
	int scSpeed;
	int NcSpeed;
	int ID;
	int HID;
	static int checkuptimenc;
	static int checkuptimesc;
	static int busytime;
	//int carid;
	patient* assignedPatient;
public:
	car();
	car(string ct, string cs,int carsp,int ID,int HID);
	//setters
	void setcartype(string ct);
	void setcar_status(string cs);//da eh
	void setscSpeed(int scsp);
	void setNcSpeed(int ncsp);
	void setcarid(int id);
	int getcarid();
	void setassignedpatient(patient* p);
	void setbusytime(int x);
	static void setcheckuptimenc(int t);
	static void setcheckuptimesc(int t);
	int getcheckuptimenc();
	int getcheckuptimesc();
	int getHID();
	//void setcarid(int ci);
	//getters
	string getcartype();

	//int get
	int getbusytime();
	string getcar_status();
	int getscSpeed();
	int getNcSpeed();
	patient* getassignedpatient();
	friend ostream& operator<<(ostream& os, const car& c);
	int calculatetime();



};

