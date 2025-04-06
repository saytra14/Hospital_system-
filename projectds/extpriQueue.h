#pragma once
#include "priQueue.h"
using namespace std;
#include"patient.h"
#include"car.h"
#include"string.h"
#include<iostream>
template <typename T>


class extpriQueue :
	public priQueue<car*>
	/* int ncars;
 int spcarsn;
 int npcarsn;*/

{
public:
	car* carcancelledID(int patientID, int& x) {//func return ptr to car kan ma3aha el patient
		priNode<car*>* current = head;
		priNode<car*>* prev = nullptr;

		while (current) {
			if (current->getItem(x)->getassignedpatient()->getpatientID() == patientID) {
				if (prev == nullptr) {
					head = current->getNext();
				}
				else {
					prev->setNext(current->getNext());
				}
				return current->getItem(x);

			}
			prev = current;
			current = current->getNext();
		}
		return nullptr;
	}

	int getcount() {
		priNode<car*>* current = head;
		int count = 0;
		while (current) {
			count = count + 1;
			current = current->getNext();
		}
		return count;
	}
	void print() {
		int trashcan;
		priNode<car*>* temp = head;//pointer to head
		int NC = 0;//intillization
		int NSC = 0;//intillization
		int NNC = 0;//inizillization
		while (temp) {//while temp not pointing to not null
			if (temp->getItem(trashcan)->getcartype() == "SC") {


				NSC = NSC + 1;
				NC = NC + 1;
			}
			else {
				NNC = NNC + 1;
				NC = NC + 1;
			}
			temp = temp->getNext();
		}
	}
	//  cout << "cars: " << NC << " " << "Special cars :   " << NSC << ", Normal cars: " << NNC << "" << endl;
	friend ostream& operator<<(ostream& os, const extpriQueue& outc);

};

inline ostream& operator<<(ostream& os, const extpriQueue<car*>& outc)
{
	priNode<car*>* current = outc.head;
	int trashcan;
	cout << outc.countpri() << " ==> Out Cars: ";
	while (current) {
		cout << *(current->getItem(trashcan))<<" , ";
		current = current->getNext();
	}
	return os;
}