#pragma once
//#include "LinkedQueue.h"
//#include "organizer.h"
//#include"NPQueue.h"
#include"hospital.h"
//#include"patient.h"
#include"string.h"



class NPQueue :
	public LinkedQueue<patient*>
{
public:
	bool cancelfunction(int	patientID) {
		Node<patient*>* temp = frontPtr;
		while (temp&&temp->getNext()) {
			if (temp->getNext()->getItem()->getpatientID() == patientID) {
				Node<patient*>* patient = temp->getNext();
				temp->setNext(patient->getNext());
				delete patient;
				return true;
			}
			temp = temp->getNext();
		}
		return false;
	}



};

