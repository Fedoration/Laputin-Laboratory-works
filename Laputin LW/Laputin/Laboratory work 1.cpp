#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe
{
	int id;
	float length;
	float diameter;
	bool is_broken;

};



struct KS
{
	int id;
	string name;
	int num_of_workshops;
	int working_workshops;
	int efficient;
};

Pipe createPipe()
{
	Pipe p;
	cout << "������� ����� �����: ";
	cin >> p.length;
	cout << "������� ������� �����: ";
	cin >> p.diameter;
	p.is_broken = false;
	return p;
}


KS createKS()
{
	KS ks;
	cout << "������� �������� ��: ";
	cin >> ks.name;
	cout << "������� ���-�� �����: ";
	cin >> ks.num_of_workshops;
	cout << "������� ���������� ����� � ������: ";
	cin >> ks.working_workshops;
	cout << "������� ������������� ������������� �������: ";
	cin >> ks.efficient;

	return ks;
}

void Pipe_output(Pipe pipe) {
	cout << "����� ���������� � ����� " << pipe.id << endl;
	cout << "����� �����: " << pipe.length << endl;
	cout << "������� �����: " << pipe.diameter << endl;
	cout << "������ �����: " << pipe.is_broken << endl;
}

void change_Pipe_status(Pipe& pipe) {
	pipe.is_broken = !pipe.is_broken;
	cout << "������ ����� ��� ������ �� " << pipe.is_broken << endl;
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



int main()
{
	setlocale(LC_ALL, "Russian");
	int id = 0;

	Pipe pipe1 = createPipe();
	pipe1.id = id;

	//write_to_file(pipe1);
	Pipe pipe2 = read_from_file();
	Pipe_output(pipe2);

	return 0;	
}