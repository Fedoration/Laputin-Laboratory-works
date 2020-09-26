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
	int count_workshops;
	int count_running_workshops;
	int efficiency;
};


/* CRUD for Pipe */
Pipe createPipe()
{
	Pipe p;
	cout << "Type pipe length: ";
	cin >> p.length;
	cout << "Type pipe diameter: ";
	cin >> p.diameter;
	p.is_broken = false;
	return p;
}

void Pipe_output(const Pipe& pipe) {
	cout << "Output information about the pipe " << pipe.id << "\n"
	     << "Pipe length: " << pipe.length << "\n"
	     << "Pipe diameter: " << pipe.diameter << "\n"
	     << "Pipe status: " << pipe.is_broken
		 << endl;
}

void change_Pipe_status(Pipe& pipe) {
	pipe.is_broken = !pipe.is_broken;
	cout << "Статус трубы был изменён на " << pipe.is_broken << endl;
}

Pipe pipe_read_from_file() {
	ifstream fin;
	fin.open("pipe_info.txt", ios::in);
	if (fin.is_open())
	{
		Pipe p;
		fin >> p.id >> p.length >> p.diameter >> p.is_broken;
		fin.close();
		return p;
	}
	else {
		cout << "File pipe_info.txt wasnt open!" << endl;
	}
}

void pipe_write_to_file(Pipe pipe)
{
	ofstream fout;
	fout.open("pipe_info.txt", ios::out);
	if (fout.is_open())
	{
		fout << pipe.id << endl << pipe.length << endl << pipe.diameter << endl << pipe.is_broken << endl;
		fout.close();
		cout << "\nWriting to the file was successful" << endl;
	}
	else {
		cout << "File pipe_info.txt wasnt open!" << endl;
	}
}


/* CRUD for Compressor station */
CS createCS()
{
	CS cs;
	cout << "Type KS name: ";
	cin >> cs.name;
	cout << "Type number of workshops: ";
	cin >> cs.count_workshops;
	cout << "Type number of running workshops: ";
	cin >> cs.count_running_workshops;
	cout << "Type KS efficiency: ";
	cin >> cs.efficiency;

	return cs;
}

void CS_output(const CS& cs) {
	cout << "Output information about the compressor station " << cs.id << "\n"
		 << "CS name: " << cs.name << "\n"
	     << "Count of workshops: " << cs.count_workshops << "\n"
	     << "Count of running workshops: " << cs.count_running_workshops
		 << endl;
}

CS cs_read_from_file()
{
	ifstream fin;
	fin.open("cs_info.txt", ios::in);
	if (fin.is_open())
	{
		CS cs;
		fin >> cs.id >> cs.name >> cs.count_workshops
			>> cs.count_running_workshops >> cs.efficiency;
		fin.close();
		return cs;
	}
	else {
		cout << "File cs_info.txt wasnt open!" << endl;
	}
}

void cs_write_to_file(CS cs)
{
	ofstream fout;
	fout.open("cs_info.txt", ios::out);
	if (fout.is_open())
	{
		fout << cs.id << cs.name << cs.count_workshops
			 << cs.count_running_workshops << cs.efficiency;
		fout.close();
		cout << "\nWriting to the file was successful" << endl;
	}
	else {
		cout << "File cs_info.txt wasnt open!" << endl;
	}
}


int main()
{
	int id = 0;

	Pipe pipe1 = createPipe();
	pipe1.id = id;
	pipe_write_to_file(pipe1);


	return 0;	
}