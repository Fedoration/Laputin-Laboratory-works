#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Pipe
{
	int id;
	double length;
	double diameter;
	bool is_broken;
};


struct CS
{
	int id;
	string name;
	int num_workshops;
	int num_running_workshops;
	int efficiency;
};


// CRUD for Pipe
Pipe createPipe()
{
	Pipe p;
	cout << "Type pipe length: ";
	cin >> p.length;
	cout << "Type pipe diametеr: ";
	cin >> p.diameter;
	p.is_broken = false;
	return p;
}

void Pipe_output(Pipe pipe) {
	cout << "Output information about the pipe " << pipe.id << endl;
	cout << "Pipe length: " << pipe.length << endl;
	cout << "Pipe diameter: " << pipe.diameter << endl;
	cout << "Pipe status: " << pipe.is_broken << endl;
}

void change_Pipe_status(Pipe& pipe) {
	pipe.is_broken = !pipe.is_broken;
	cout << "Статус трубы был изменён на " << pipe.is_broken << endl;
}

Pipe read_from_file() {
	ifstream fin;
	fin.open("Info.txt", ios::in);
	if (fin.is_open())
	{
		Pipe p;
		fin >> p.id >> p.length >> p.diameter >> p.is_broken;
		fin.close();
		return p;
	}
}

void write_to_file(Pipe pipe) {
	ofstream fout;
	fout.open("Info.txt", ios::out);
	fout << pipe.id << endl << pipe.length << endl << pipe.diameter << endl << pipe.is_broken << endl;
	fout.close();
}


// CRUD for Compressor station
CS createCS()
{
	CS cs;
	cout << "Type KS name: ";
	cin >> cs.name;
	cout << "Type number of workshops: ";
	cin >> cs.num_workshops;
	cout << "Type number of running workshops: ";
	cin >> cs.num_running_workshops;
	cout << "Type KS efficiency: ";
	cin >> cs.efficiency;

	return cs;
}


int main()
{
	int id = 0;

	Pipe pipe1 = createPipe();
	pipe1.id = id;

	//write_to_file(pipe1);
	Pipe pipe2 = read_from_file();
	Pipe_output(pipe2);

	return 0;	
}