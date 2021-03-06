#include <iostream>
#include <fstream>
#include <string>
#include "CS.h"
#include "utils.h"
using namespace std;

int CS::MaxID = 0;

CS::CS() {
	id = ++MaxID;
	string name = "Unknown";
	count_workshops = 0;
	count_running_workshops = 0;
	efficiency = 0;
}

int CS::GetId() const
{
	return id;
}

string CS::GetName() const
{
	return name;
}

void CS::edit_CS() {
	count_running_workshops = GetCorrectNumber("Type number of running workshops: ", 0, count_workshops);
}

istream& operator >> (istream& in, CS& cs)
{
	cout << "Type CS name: " << endl;
	cin.get();
	getline(cin, cs.name);
	cs.count_workshops = GetCorrectNumber("Type number of workshops: ", 0, 100);
	cs.count_running_workshops = GetCorrectNumber("Type number of running workshops: ", 0, cs.count_workshops);
	cs.efficiency = GetCorrectNumber("Type CS efficiency: ", 0.0, 1.0);
	return in;
}

ostream& operator << (ostream& out, const CS& cs)
{
	out << "\nOutput information about the compressor station " << cs.id << "\n"
		<< "CS name: " << cs.name << "\n"
		<< "Count of workshops: " << cs.count_workshops << "\n"
		<< "Count of running workshops: " << cs.count_running_workshops << "\n"
		<< "CS efficiency: " << cs.efficiency << endl;
	return out;
}

ifstream& operator>>(std::ifstream& fin, CS& cs)
{
	fin.ignore();
	getline(fin, cs.name);
	fin >> cs.id >> cs.count_workshops
		>> cs.count_running_workshops >> cs.efficiency;
	return fin;
}

ofstream& operator<<(ofstream& fout, const CS& cs)
{
	fout << cs.name << endl << cs.id << endl << cs.count_workshops
		<< endl << cs.count_running_workshops << endl << cs.efficiency << endl;
	return fout;
}

//void CS::SaveCS(ofstream& fout) const {
//	fout << id << endl << name << endl << count_workshops
//		<< endl << count_running_workshops << endl << efficiency << endl;
//}

