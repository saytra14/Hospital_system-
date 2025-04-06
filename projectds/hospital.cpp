#include "hospital.h"
#include"LinkedQueue.h"
#include"priQueue.h"
#include "organizer.h"

hospital::hospital(int HID,organizer*o)
{
	hospitalID = HID;
	org = o;
	//o = new organizer();

}

hospital::hospital()
{
	//o = new organizer();
}

void hospital::sethospitalID(int hid)
{
	hospitalID = hid;
}

void hospital::patientfun(patient P)
{
}

void hospital::addscar(car* A)
{
	SC.enqueue(A);
}

void hospital::addncar(car* A)
{
	NC.enqueue(A);
}

void hospital::addnormalpatient(patient*a)
{
	NP.enqueue(a);
}

void hospital::addspecialpatient(patient*a)
{
	SP.enqueue(a);
}

void hospital::addemergencypatient(patient* A, int severity)
{
	EP.enqueue(A, severity);
}

int hospital::gethospitalid()
{
	return hospitalID;
}

LinkedQueue<patient*>& hospital::getsplist()
{
	return SP;
}

NPQueue& hospital::getnplist()
{
	return NP;
}

priQueue<patient*>& hospital::geteplist()
{
	return EP;
}

LinkedQueue<patient*>& hospital::getspprintlist()
{
	return SPprint;
}

NPQueue& hospital::getnpprintlist()
{
	return NPprint;
}


priQueue<patient*>& hospital::getepprintlist()
{
	return EPprint;
}

LinkedQueue<car*>& hospital::getnormalcar()
{
	return NC;
}

LinkedQueue<car*>& hospital::getspecialcar()
{
	return SC;
}

LinkedQueue<cancellation*>& hospital::getcancelledpatient()
{
	return PC;
}

void hospital::setnormalcar(LinkedQueue<car*> nc)
{
	NC = nc;
}

void hospital::setspecialcar(LinkedQueue<car*> sc)
{
	SC = sc;
}

void hospital::distribute(patient* p) {
	if (p->getpatienttype() == "NP") {
		NP.enqueue(p);
	}
	else if (p->getpatienttype() == "SP") {
		SP.enqueue(p);
	}
	else if (p->getpatienttype() == "EP") {
		int s = p->getseverity();
		EP.enqueue(p, s);
	}
}

////void hospital::sendto(organizer* o, car* c)
//{
//	o->receive(this);
//}


void hospital::assign(int t)
{
	int s = 0;
	
	//organizer* o = new organizer();
	//o->load("input.txt");
	car* car1 =nullptr;
	patient* p=nullptr ;
	//while l8ayt mal emergency patients y5laso w hanzl bas law ma5lsosh hawdehom asln msh ha5osh fel np wala sp
	
	while (!EP.isEmpty()) {
		EP.peek(p, s);
		if (p->getrequesttime() <= t) {
			if (!NC.isEmpty()) {
				s = p->getseverity();


				NC.peek(car1);

				car1->setassignedpatient(p);
				EPprint.enqueue(p,s);
				EP.dequeue(p, s);
				org->freetoOut(car1, t);
				NC.dequeue(car1);
			}
			else if (!SC.isEmpty()) {
				s = p->getseverity();

				//EP.dequeue(p, s);
				SC.peek(car1);

				car1->setassignedpatient(p);
				EPprint.enqueue(p, s);
				EP.dequeue(p, s);
				org->freetoOut(car1, t);
				SC.dequeue(car1);
			}

			else {
				s = p->getseverity();
				EPprint.enqueue(p, s);
				EP.dequeue(p, s);
				org->handle(p, s);
				//law mafesh cars available wadeeh l ay hospital tanya
			}
		}
	}
	while (!NC.isEmpty() && !NP.isEmpty())//while feeh cars available w feeh np
	{
		NP.peek(p);
		//NP.dequeue(p);
		if (p->getrequesttime() <= t) {
			NC.peek(car1);

			//NC.dequeue(car1);//sheelo men el normal car list law feeha cars w hoto fel out cars
			car1->setassignedpatient(p);
			NPprint.enqueue(p);
			NP.dequeue(p);
			org->freetoOut(car1, t);
			NC.dequeue(car1);
			//o->sendto(car1);
		}
	}


	while (!SC.isEmpty() && !SP.isEmpty())
	{
		SP.peek(p);
		if (p->getrequesttime() <= t) {
			//SP.dequeue(p);
			SC.peek(car1);
			//SC.dequeue(car1);
			car1->setassignedpatient(p);
			SPprint.enqueue(p);
			SP.dequeue(p);
			org->freetoOut(car1, t);
			SC.dequeue(car1);
		}
	}
}







