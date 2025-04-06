#include"LinkedQueue.h"
#include"priQueue.h"
#include "organizer.h"
#include "UI.h"
int main() {
	organizer o;
	UI H;
	hospital* l ;
	o.load("input.txt");
	bool exit=true;
	o.simulator(true);
	o.save();
	//o.OutToBack(6);
	//o.runsimulation(exit);
	//H.printinterface(l);
}
