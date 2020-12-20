#include "Pipe.h"
#include "utils.h"

#include <iostream>
#include <fstream>
using namespace std;


int Pipe::MaxID = 0;

Pipe::Pipe() {
	id = ++MaxID;
	length = 0;
	diameter = 0;
	is_broken = false;
	source = 0;
	destination = 0;
}

int Pipe::GetId() const {
	return id;
}

bool Pipe::GetStatus() const {
	return is_broken;
}

int Pipe::GetWeight() {
	return length;
}

void Pipe::change_Pipe_status()
{
	is_broken = !is_broken;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.length = GetCorrectNumber("Type pipe length: ", 0, 1000);
	p.diameter = GetCorrectNumber("Type pipe diameter: ", 0, 2500);
	p.is_broken = false;
	return in;
}


ostream& operator << (ostream& out, const Pipe& p)
{
	out << "\nOutput information about the pipe " << p.id << "\n"
		<< "Pipe length: " << p.length << "\n"
		<< "Pipe diameter: " << p.diameter << "\n"
		<< "Pipe status: " << p.is_broken << "\n"
		<< "Pipe source: " << p.source << "\n"
		<< "Pipe destination: " << p.destination
		<< endl;
	return out;
}


ifstream& operator>>(ifstream& fin, Pipe& p)
{
	fin >> p.id >> p.length >> p.diameter >> p.is_broken >> p.source >> p.destination;
	return fin;
}

ofstream& operator<<(ofstream& fout, const Pipe& p)
{
	fout << p.id << endl << p.length << endl << p.diameter
		<< endl << p.is_broken << endl << p.source << endl << p.destination << endl;
	return fout;
}

//Pipe LoadPipe(ifstream& fin)
//{
//	Pipe p;
//	fin >> p.id >> p.length >> p.diameter >> p.is_broken;
//	return p;
//}
//
//void Pipe::SavePipe(ofstream& fout) const {
//	fout << id << endl << length << endl
//		<< diameter << endl << is_broken << endl;
//}
