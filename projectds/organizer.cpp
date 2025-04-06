#include "organizer.h"
//#include"LinkedQueue.h"
#include"NPQueue.h"
#include<cstdlib>
#include"car.h"
//#include"hospital.h"
//#include"patient.h"
//#include"string.h"


organizer::organizer()
{
	NCnumb = 0;
	SCnumb = 0;
	Hospitalnumb = 0;
	carspeed_sc = 0;
	carspeed_nc = 0;
	patientID = 0;
	requesttime = 0;
	hospitalID = 1;
	requesttype;
	distancenear = 0;
	cancellationtime = 0;
	cancelled_PID = 0;
	nearhospitalID = 0;
	totalrequests = 0;
	numCancelledrequest = 0;
	backnumber = 0;
	outcarsnumber = 0;
	cancelledpatients = 0;
	NcCount = 0;
	SCCount = 0;
	countFinish = 0;
	TIMESTEP = 0;
}

void organizer::load(string filename)
{

	ifstream file(filename);
	if (!file)
		cout << "error no file" << endl;
	file >> Hospitalnumb;
	file >> carspeed_sc >> carspeed_nc;
	distancesmatrix = new int* [Hospitalnumb];
	hospital_list = new hospital * [Hospitalnumb];
	for (int i = 0; i < Hospitalnumb; i++) {
		hospital_list[i] = new hospital(Hospitalnumb, this);
	}
	for (int i = 0; i < Hospitalnumb; i++)
	{
		distancesmatrix[i] = new int[Hospitalnumb];
		for (int j = 0; j < Hospitalnumb; j++)
		{
			file >> distancesmatrix[i][j];
		}

	}
	for (int i = 1; i < Hospitalnumb + 1; i++)
	{
		file >> SCnumb >> NCnumb;
		//hospital_list[i].sethospitalID(i+1);
			// hospital_list[i] = special car list of length SCnumb AND normal car list of NCNumb
		car* sc;
		for (int j = 0; j < SCnumb; ++j) {
			sc = new car("SC", "free", 110,SCCount,i);
			SCCount++;
			//	SC.enqueue(sc);
			hospital_list[i - 1]->addscar(sc);
		}
		car* nc;
		for (int j = 0; j < NCnumb; ++j) {
			nc = new car("NC", "free", 75,NcCount,i);
			NcCount++;
			//NC.enqueue(nc);
			hospital_list[i - 1]->addncar(nc);
		}
	}

	/*string h;
	string st_free;
	car* c ;
	if ( h == "nc") {
		c = new car(h, st_free);

	}
	if (h == "sc") {
		c = new car(h, st_free);
		hospital_list[i].getspecialcar().enqueue(c);

	}*/
	file >> probabilityfailure;
	//int checkuptimenc=0;
	//	int checkuptimesc=0;
	//file >> checkuptimenc, checkuptimesc;
	//car::setcheckuptimenc(checkuptimenc);
	//car::setcheckuptimesc(checkuptimesc);
	file >> totalrequests;
	for (int i = 0; i < totalrequests; i++) {

		int x = -1;
		string s;
		file >> s;
		requesttype = s;

		if (s == "EP") {

			file >> requesttime;
			file >> patientID;
			file >> hospitalID;
			file >> distancenear;
			file >> x;
			patient* p = new patient(s, requesttime, patientID, hospitalID, distancenear, x);
			requesteplist.enqueue(p);
			TotalEP++;


		}
		else if (s == "SP") {
			file >> requesttime;
			file >> patientID;
			file >> hospitalID;
			file >> distancenear;
			patient* p = new patient(s, requesttime, patientID, hospitalID, distancenear);
			requestsplist.enqueue(p);
			TotalSP++;
		}
		else if (s == "NP") {
			file >> requesttime;
			file >> patientID;
			file >> hospitalID;
			file >> distancenear;
			patient* p = new patient(s, requesttime, patientID, hospitalID, distancenear);
			requestnplist.enqueue(p);
			TotalNP++;
		}
	}

	file >> numCancelledrequest;
	for (int i = 0; i < numCancelledrequest; i++) {
		file >> cancellationtime;
		file >> cancelled_PID;
		file >> hospitalID;
		cancellation* c = new cancellation(cancelled_PID, hospitalID, cancellationtime);
		cancellationlist.enqueue(c);
	}
}

LinkedQueue<patient*> organizer::getrequestnplist()
{
	return requestnplist;
}

void organizer::save()
{
	int sum = 0;
	int sumc = 0;
	int sumwt = 0;
	int sumbt = 0;
	car* c = nullptr;
	patient* p = nullptr;
	sum = totalrequests-cancelledpatients;
	sumc = (SCCount+NcCount);
	ofstream outfile("outfile.txt");
	if (outfile.is_open()) {
		outfile << "FT    " << "PID    " << "OT    " << "WT" << endl;
		while (!finishedlist.isEmpty()) {
			finishedlist.dequeue(p);
			outfile << p->getfinishedtime() << "    " << p->getpatientID() << "    " << p->getrequesttime() << "    " << p->getwaittime() << endl;
			sumwt += p->getwaittime();
			sumbt += c->getbusytime();
		}
		outfile << "patients: " << sum << "    [NP: " << TotalNP<< ", SP: " << TotalSP << ", EP: " << TotalEP << "]" << endl;
		outfile << "Hospitals= " << Hospitalnumb << endl;
		outfile << "cars: " << sumc << "    [SCar: " <<  SCCount<< ", NCar: " << NcCount << "]" << endl;
		outfile << "Avg wait time= " << (sumwt / sum) << endl;
		outfile << "Avg busy time= " << (sumbt / sumc) << endl;
		outfile << "Avg utilization= " << ((sumbt / sumc) / TIMESTEP)<<"%" << endl;//50 total timestep l8ayt matzbot
		

	}
}

void organizer::receive(hospital* h)
{

}

void organizer::freetoOut(car* c, int t)
{

	int time = c->calculatetime() + t;
	outcars.enqueue(c, -time);
	c->setcar_status("busy");
	outcarsnumber++;

}

void organizer::OutToBack(int t)
{
	car* c;
	int time = 0;
	while (outcars.peek(c, time)) {// && t==-time) {
		if (t == -time) {
			c->getassignedpatient()->setpicktime(t);
			outcars.dequeue(c, time);
			time = c->calculatetime() + t;
			backcars.enqueue(c, -time);
			c->setbusytime(c->calculatetime());
			backnumber++;
			outcarsnumber--;
		}
		else {
			break;
		}
	}

}

void organizer::BackToFree(int t)
{
	car* c;
	patient* p = nullptr;
	int time = 0;
	while (backcars.peek(c, time)) {//&& t == -time) {
		if (t <= -time) {
			backcars.dequeue(c, time);
			if (c->getassignedpatient()) {
			c->getassignedpatient()->setfinishedtime(t);
			}
			if (c->getcartype() == "NC")
				hospital_list[c->getHID()-1]->getnormalcar().enqueue(c);
			else if (c->getcartype() == "SC")
				hospital_list[c->getHID()-1]->getspecialcar().enqueue(c);
			if (c->getassignedpatient()) {

			finishedlist.enqueue(c->getassignedpatient());
			}
			countFinish++;
			c->setcar_status("free");
			if (!c->getassignedpatient()) {
				c->setbusytime(0);
			}
			else {
				c->setbusytime(-1);
			}
			backnumber--;
		}
		else {
			break;
		}
	}


}

void organizer::cancelrequest(int t)
{
	cancellation* CP;
	int time = 0;
	while (cancellationlist.peek(CP) && CP->getcanceltime() <= t) {
		cancellationlist.dequeue(CP);

		if (hospital_list[CP->gethospitalid()-1]->getnplist().cancelfunction(CP->getpatientid())) {
			cancelledpatients++;
		}
		car* c = outcars.carcancelledID(CP->getpatientid(), time);
		if (c) {
			time = -1 * time - c->calculatetime();//calculating busy time 
			c->setbusytime(t - time);
			backcars.enqueue(c, -((t - time)+t));
			c->setassignedpatient(nullptr);
			CP = nullptr;
			cancelledpatients++;
		}

		//if (hospital_list[CP->gethospitalid()]->getnplist().cancelfunction(CP->getpatientid())) {
		//car*c=outcars.carcancelledID(CP->getpatientid(),time);
		//time=time - c->calculatetime();//calculating busy time 
		//c->setbusytime(t - time);
		//backcars.enqueue(c, t - time);
		//CP = nullptr;
		//}
	}
}

void organizer::handle(patient* p, int s)
{
	int random_number = std::rand() % Hospitalnumb ;
	
	hospital_list[random_number]->geteplist().enqueue(p, s);
	

}

void organizer::simulator(bool mode)
{
	//load("input.txt");
	if (mode) {
		
		int x = 5;
		car* c = nullptr;
		hospital* h = nullptr;
		patient* p = nullptr;
		organizer* o = new organizer();
		//ehna el mafrod hankhosh 3la el hospitals kolha mafehash had w el cars kolha tkon reg3at wel patients kolha khalst 




		//while (!hospital_list[i].geteplist().isEmpty() || !hospital_list[i].getnplist().isEmpty() || !hospital_list[i].getsplist().isEmpty()) {
		//while (sum != finishedlist.countinqueue()) {
		while (!((totalrequests - cancelledpatients) == finishedlist.countinqueue())) {
			for (int i = 1; i < Hospitalnumb + 1; i++) {
				//TIMESTEP++;
				cout << "Current Timestep: " << TIMESTEP << endl;
				cout << "==========     HOSPITAL #" << i << "   data" << endl;
				cout << " =============" << endl;

	/*		srand(time(0));
						int randnum = rand() % 10 + 1;
						if (randnum == probabilityfailure)
						{
							car* c = nullptr;
							failaction(c);
						}*/

				while (requesteplist.peek(p) && p->getrequesttime() <= TIMESTEP) {
					hospital_list[p->gethospitalID() - 1]->addemergencypatient(p, p->getseverity());
					//hospital_list[p->gethospitalID() - 1]->assign(TIMESTEP);
					p->setwaittime();
					
					requesteplist.dequeue(p);
					p = nullptr;
				}
				while (requestnplist.peek(p) && p->getrequesttime() <= TIMESTEP) {
					hospital_list[p->gethospitalID() - 1]->addnormalpatient(p);
					//hospital_list[p->gethospitalID() - 1]->assign(TIMESTEP);
					p->setwaittime();
					
					requestnplist.dequeue(p);
					p = nullptr;
				}
				while (requestsplist.peek(p) && p->getrequesttime() <= TIMESTEP) {
					hospital_list[p->gethospitalID() - 1]->addspecialpatient(p);
					//hospital_list[p->gethospitalID() - 1]->assign(TIMESTEP);
					p->setwaittime();
					
					requestsplist.dequeue(p);
					p = nullptr;
				}
				for (int j = 0; j < Hospitalnumb; j++)
				{
					hospital_list[j]->assign(TIMESTEP);
				}
				cancelrequest(TIMESTEP);
				OutToBack(TIMESTEP);
				BackToFree(TIMESTEP);
				print(i - 1);
				cout << "==========     HOSPITAL #" << i << "   data  end" << endl;
				cout << " =============" << endl;

			}
			TIMESTEP++;			//cout << "==========     HOSPITAL #" << i << "   data  end" << endl;
			//cout << " =============" << endl;
			if ((totalrequests - cancelledpatients) == finishedlist.countinqueue()) {
				break;
			}
		}
	}
	else {
		cout << "Silent Mode , Simulation Starts..." << endl << "Simulation end, Output file created";
	}

}

void organizer::print(int m)
{
	patient* p = nullptr;
	car* C = nullptr;
	int numOfEp = hospital_list[m]->geteplist().countpri();
	int numOfNp = hospital_list[m]->getnplist().countinqueue();
	int numOfSp = hospital_list[m]->getsplist().countinqueue();
	/*int a = outcars.countpri();
	int b = backcars.countpri();*/
	int NcNum = hospital_list[m]->getnormalcar().countinqueue();
	int ScNum = hospital_list[m]->getspecialcar().countinqueue();
	//int i = 0;
	cout << numOfEp << " EP REQUESTS:";
	hospital_list[m]->geteplist().printpri();
	cout << endl;
	cout << numOfSp << " SP REQUESTS:";
	hospital_list[m]->getsplist().print();
	cout << endl;
	cout << numOfNp << " NP REQUESTS: ";
	hospital_list[m]->getnplist().print();
	cout << endl;
	cout << "free cars: " << ScNum << " SCars,  " << NcNum << " NCars" << endl;


	cout << outcars << endl;
	cout << backcars.countpri() << " <== back Cars: ";
	backcars.printpri();
	cout << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Finished List: ";
	finishedlist.print();
	cout << "----------------" << endl;
	//for (int i = 0; i < a; i++) {
	//	int p = C->getassignedpatient()->getpatientID();
	//	if (C->getcartype() == "SC") {
	//		//cout << "S_" << "H" <<  << "P" << p;
	//	}
	//	else if (C->getcartype() == "NC") {
	//	}
	//}


}

void organizer::failaction(car* car)
{
	if (!outcars.isEmpty())
	{
		int priority = 0;


		backcars.enqueue(car, car->getbusytime());
		patient* pat = car->getassignedpatient();
		if (pat != nullptr)
			if (pat->getpatienttype() == "SP")
			{
				LinkedQueue<patient*>temp;
				patient* tempPatient = nullptr;
				while (hospital_list[pat->gethospitalID() - 1]->getsplist().dequeue(tempPatient)) // ba dequeue kolo w bahtohom fe temp
				{
					temp.enqueue(tempPatient);
				}
				hospital_list[pat->gethospitalID() - 1]->getsplist().enqueue(pat);
				while (temp.dequeue(tempPatient))
				{
					hospital_list[pat->gethospitalID() - 1]->getsplist().enqueue(tempPatient);
				}
			}
			else if (pat->getpatienttype() == "EP")
			{
				int maxp = 0;
				priQueue<patient*> temp = hospital_list[pat->gethospitalID() - 1]->geteplist();
				patient* tempPatient = nullptr;
				while (temp.dequeue(tempPatient, priority))
				{
					if (priority > maxp)
					{
						maxp = priority;
					}
				}
				hospital_list[pat->gethospitalID() - 1]->geteplist().enqueue(tempPatient, maxp + 1);
			}
			else if (pat->getpatienttype() == "NP")
			{
				LinkedQueue<patient*>temp;
				patient* tempPatient = nullptr;

				while (hospital_list[pat->gethospitalID() - 1]->getnplist().dequeue(tempPatient))
				{
					temp.enqueue(tempPatient);
				}
				hospital_list[pat->gethospitalID() - 1]->getnplist().enqueue(pat);
				while (temp.dequeue(tempPatient))
				{
					hospital_list[pat->gethospitalID() - 1]->getnplist().enqueue(tempPatient);
				}

			}


	}
}

void organizer::printcheckup()
{
	car* c = nullptr;
	priQueue<car*> temp = checkup;
	int pri = 0;
	if (!temp.isEmpty())

		while (temp.dequeue(c, pri))
		{
			cout << "car type:" << c->getcartype() << ",remainig time:" << pri << "car id:"; //<<// c->getcarid();


		}


}

//void organizer::checkuptofree()
//{
//
//	car* c = nullptr;
//	priQueue<car*> temp = priQueue<car*>(checkup);
//	int timeremaines = 0;
//	if (checkup.countpri() == 0)
//	{
//		return;
//	}
//	while (checkup.dequeue(c, timeremaines))
//	{
//		if (timeremaines == 0)
//		{
//			if (c->getcartype() == "NC")
//			{
//				hospital_list[c->getassignedpatient()->gethospitalID() - 1]->getnormalcar().enqueue(c);
//			}
//			else
//			{
//				hospital_list[c->getassignedpatient()->gethospitalID() - 1]->getspecialcar().enqueue(c);
//			}
//			c->getassignedpatient() == nullptr;
//
//		}
//		else
//		{
//			timeremaines--;
//			temp.enqueue(c, timeremaines);
//
//		}
//
//	}
//	while (temp.dequeue(c, timeremaines))
//	{
//		checkup.enqueue(c, timeremaines);
//	}
//
//}
//void organizer::backtocheck(car* car)
//{
//	if (car->getcartype() == "SC")
//	{
//		checkup.enqueue(car, car->getcheckuptimesc());
//	}
//	else if (car->getcartype() == "NC")
//	{
//		checkup.enqueue(car, car->getcheckuptimenc());
//	}
//}
// we deleted from the file text 3,4 checkup nc w sc //
