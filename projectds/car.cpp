#include "car.h"

car::car()
{
}
int car::busytime = 0;
int car::checkuptimenc = 0;
int car::checkuptimesc = 0;
car::car(string ct, string cs,int carsp,int ID,int HID)
{
	cartype = ct;
	car_status = cs;
	carspeed = carsp;
	this->ID = ID;
	this->HID = HID;
}

void car::setcartype(string ct)
{
	cartype = ct;

}

void car::setcar_status(string cs)
{
	car_status = cs;
}

void car::setscSpeed(int scsp)
{
	scSpeed = scsp;
}

void car::setNcSpeed(int ncsp)
{
	NcSpeed = ncsp;
}

void car::setcarid(int id)
{
	ID = id;
}

int car::getcarid()
{
	return ID;
}

void car::setassignedpatient(patient*p)
{
	assignedPatient = p;
	
}

void car::setbusytime(int x)
{
	if (x == -1) {
		busytime = busytime + calculatetime();
	}
	else {
		busytime = busytime + x;
	}
}

void car::setcheckuptimenc(int t)
{
	checkuptimenc = t;
}

void car::setcheckuptimesc(int t)
{
	checkuptimesc = t;
}

int car::getcheckuptimenc()
{
	return checkuptimenc ;
}

int car::getcheckuptimesc()
{
	return checkuptimesc;
}

int car::getHID()
{
	return HID;
}

string car::getcartype()
{
	return cartype;
}

int car::getbusytime()
{
	return busytime;
}

string car::getcar_status()
{
	return car_status;
}

int car::getscSpeed()
{
	return scSpeed;
}

int car::getNcSpeed()
{
	return NcSpeed;
}
//revise getter
patient* car::getassignedpatient()
{
	return assignedPatient;
}

int car::calculatetime()
{
	/*if (cartype == "NC") {
		return assignedPatient->getdistance() /carspeed;
	}
	else if (cartype == "SC") {*/
		return (assignedPatient->getdistance() / carspeed);
	
}

ostream& operator<<(ostream& os, const car& c)
{
	
	if (c.cartype=="SC") {
		os << "S" << c.ID<<"_H"<<c.assignedPatient->gethospitalID()<<"_P"<<c.assignedPatient->getpatientID();
	return os;
	}
		os << "N" << c.ID << "_H" << c.assignedPatient->gethospitalID() << "_P" << c.assignedPatient->getpatientID();
	
	return os;
}
