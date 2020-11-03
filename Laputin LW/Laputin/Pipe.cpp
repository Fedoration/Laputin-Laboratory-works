#include "Pipe.h"
#include "utils.h"
using namespace std;


int Pipe::MaxID = 0;

Pipe::Pipe() {
	id = ++MaxID;
	length = 0;
	diameter = 0;
	is_broken = false;

}

void Pipe::change_Pipe_status()
{
	is_broken = !is_broken;
}

istream& operator >> (istream& in, Pipe& p)
{
	p.length = GetCorrectNumber("Type pipe length: ", 0.0, 1000.0);
	p.diameter = GetCorrectNumber("Type pipe diameter: ", 0, 2500);
	p.is_broken = false;
	return in;
}


ostream& operator << (ostream& out, const Pipe& p)
{
	out << "\nOutput information about the pipe " << p.id << "\n"
		<< "Pipe length: " << p.length << "\n"
		<< "Pipe diameter: " << p.diameter << "\n"
		<< "Pipe status: " << p.is_broken
		<< endl;
	return out;
}
