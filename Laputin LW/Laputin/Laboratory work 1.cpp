#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


template <typename T>
T GetCorrectNumber(string text, T min, T max)
{
	T parameter = 0;
	cout << text;
	while (!(cin >> parameter) || parameter < min || parameter > max) {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << text;
	}
	return parameter;
}


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

istream& operator >> (istream& in, Pipe& p)
{
	p.length = GetCorrectNumber("Type pipe length: ", 0.0, 1000.0);
	p.diameter = GetCorrectNumber("Type pipe diameter: ", 0.0, 1000.0);
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

//Pipe createPipe(int id)
//{
//	Pipe p;
//	p.id = id;
//	p.length = Input_double("Type pipe length: ");
//	p.diameter = Input_double("Type pipe diameter: ");
//	p.is_broken = false;
//	
//	return p;
//}
//
//void Pipe_output(const Pipe& pipe) {
//	cout << "Output information about the pipe " << pipe.id << "\n"
//	     << "Pipe length: " << pipe.length << "\n"
//	     << "Pipe diameter: " << pipe.diameter << "\n"
//	     << "Pipe status: " << pipe.is_broken
//		 << endl;
//}

void change_Pipe_status(Pipe& pipe) {
	pipe.is_broken = !pipe.is_broken;
	cout << "Pipe status was changed to: " << pipe.is_broken << endl;
}

Pipe& SelectPipe(vector<Pipe>& v)
{
	string str_number_of_pipes = to_string(v.size()-1);
	string input_text = "Enter ID of the pipe 0-" + str_number_of_pipes;		//string stream
	unsigned int id = GetCorrectNumber(input_text, 0u, v.size()-1);
	return v[id];
	
}

bool pipe_read_from_file(Pipe& p) {
	ifstream fin;
	fin.open("pipe_info.txt", ios::in);
	if (fin.is_open())
	{
		Pipe p;
		fin >> p.id >> p.length >> p.diameter >> p.is_broken;
		fin.close();
		return true;
	}
	else {
		cout << "File pipe_info.txt wasnt open" << endl;
		return false;
	}
}

void pipe_write_to_file(const Pipe& pipe)
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open())
	{
		fout << pipe.id << endl << pipe.length << endl << pipe.diameter << endl << pipe.is_broken << endl;
		fout.close();
		cout << "\nWriting to the file was successful" << endl;
	}
	else {
		cout << "File data.txt wasnt open" << endl;
	}
}


/* CRUD for Compressor station */

istream& operator >> (istream& in, CS& cs)
{
	cout << "Type CS name: " << endl;
	cin.get();
	getline(cin, cs.name);
	cs.count_workshops = GetCorrectNumber("Type number of workshops: ", 0, 100);
	cs.count_running_workshops = GetCorrectNumber("Type number of running workshops: ", 0, 100);
	cs.efficiency = GetCorrectNumber("Type CS efficiency: ", 0.0, 1.0);
	return in;
}

ostream& operator << (ostream& out, const CS& cs)
{
	out << "\nOutput information about the compressor station " << cs.id << "\n"
		<< "CS name: " << cs.name << "\n"
		<< "Count of workshops: " << cs.count_workshops << "\n"
		<< "Count of running workshops: " << cs.count_running_workshops << endl;
	return out;
}

//CS createCS(int id)
//{
//	CS cs;
//	cs.id = id;
//
//	cout << "Type CS name: " << endl;
//	cin.get();
//	getline(cin, cs.name);
//	cs.count_workshops = Input_integer("Type number of workshops: ");
//	cs.count_running_workshops = Input_integer("Type number of running workshops: ");
//	cs.efficiency = Input_integer("Type СS efficiency: ");
//
//	return cs;
//}
//
//void CS_output(const CS& cs) {
//	cout << "Output information about the compressor station " << cs.id << "\n"
//		 << "CS name: " << cs.name << "\n"
//	     << "Count of workshops: " << cs.count_workshops << "\n"
//	     << "Count of running workshops: " << cs.count_running_workshops << endl;
//}

void edit_CS(CS& cs) {
	string input_text = "Type number of running workshops: ";
	int num = GetCorrectNumber(input_text, 0, 100);
	cs.count_running_workshops = num;
	cout << "The number of operating workshops at the compressor station " << cs.id
		 << "\nwas changed to " << cs.count_running_workshops << endl;
}

CS& SelectCS(vector<CS> v)
{
	string str_number_of_CSs = to_string(v.size() - 1);
	string input_text = "Enter ID of the CS 0-" + str_number_of_CSs;		//string stream
	unsigned int id = GetCorrectNumber(input_text, 0u, v.size() - 1);
	return v[id];
}

bool cs_read_from_file(CS& cs)
{
	ifstream fin;
	fin.open("cs_info.txt", ios::in);
	if (fin.is_open())
	{
		CS cs;
		fin >> cs.id >> cs.name >> cs.count_workshops
			>> cs.count_running_workshops >> cs.efficiency;
		fin.close();
		return true;
	}
	else {
		cout << "File data.txt wasn't open" << endl;
		return false;
	}
}

void cs_write_to_file(const CS& cs)
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open())
	{
		fout << cs.id << cs.name << cs.count_workshops
			 << cs.count_running_workshops << cs.efficiency;
		fout.close();
		cout << "\nWriting to the file was successful" << endl;
	}
	else {
		cout << "File data.txt wasn't open" << endl;
	}
}

/*Save Pipe/CS*/
//void SavePipe(ofstream& fout, const Pipe& p)
//{
//	fout << p.id << endl << p.length << endl 
//		 << p.diameter << endl << p.is_broken << endl;
//}
//
//void SaveCS(ofstream& fout, const CS& cs)
//{
//	fout << cs.id << endl << cs.name << endl << cs.count_workshops
//		 << endl << cs.count_running_workshops << endl << cs.efficiency << endl;
//}

void SaveToFile(ofstream& fout, const vector<Pipe>& Pipes, const vector<CS>& CSs)
{
	int number_of_pipes = Pipes.size();
	int number_of_CSs = CSs.size();
	fout << Pipes.size() << endl;
	fout << CSs.size() << endl;

	if (number_of_pipes != 0) {
		for (auto p : Pipes) {
			fout << p.id << endl << p.length << endl
				 << p.diameter << endl << p.is_broken << endl;
		}
	}

	if (number_of_CSs != 0) {
		for (auto cs : CSs) {
			fout << cs.id << endl << cs.name << endl << cs.count_workshops
				 << endl << cs.count_running_workshops 
				 << endl << cs.efficiency << endl;
		}
	}

}


void LoadFromFile(ifstream& fin, vector<Pipe>& Pipes, vector<CS>& CSs)
{
	int number_of_pipes;
	int number_of_CSs;
	fin >> number_of_pipes;
	fin >> number_of_CSs;

	while (number_of_pipes--) {
		Pipe p;
		fin >> p.id >> p.length >> p.diameter >> p.is_broken;
		Pipes.push_back(p);
	}

	while (number_of_CSs--) {
		CS cs;
		fin >> cs.id >> cs.name >> cs.count_workshops
			>> cs.count_running_workshops >> cs.efficiency;
		CSs.push_back(cs);
	}
}


void PrintMenu()
{
	cout << "\n"
		 << "1. Input new Pipe" << "\n"
		 << "2. Input new CS" << "\n"
		 << "3. View all objects" << "\n"
		 << "4. Edit Pipe" << "\n"
		 << "5. Edit CS" << "\n"
		 << "6. Save to file" << "\n"
		 << "7. Load from file" << "\n"
		 << "0. Exit" << endl;	
}


int main()
{
	vector<Pipe> Pipes;
	vector<CS> CSs;
	int pipe_id = 0;
	int cs_id = 0;
	while (1) {

		PrintMenu();
		int i = GetCorrectNumber("Your choice (0-7): ", 0, 7);
		cout << '\n';
		switch (i) 
		{
		case 1: {
			Pipe pipe;
			cin >> pipe;
			pipe.id = pipe_id;
			Pipes.push_back(pipe);
			pipe_id++;
			break;
		}
		case 2: {
			CS cs;
			cin >> cs;
			cs.id = cs_id;
			CSs.push_back(cs);
			cs_id++;
			break;
		}
		case 3: {
			if (Pipes.size() != 0) {
				cout << Pipes[0] << endl;
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}
			
			if (CSs.size() != 0) {
				cout << CSs[0];
			}
			else {
				cout << "You haven't added any compressor stations yet" << endl;
			}
			break;
		}
		case 4: {
			if (Pipes.size() != 0) {
				change_Pipe_status(SelectPipe(Pipes));
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}
			break;
		}
		case 5: {
			if (CSs.size() != 0) {
				edit_CS(SelectCS(CSs));
			}
			else {
				cout << "You haven't added any compressor stations yet" << endl;
			}
			break;
		}
		case 6: {
			ofstream fout;
			fout.open("data.txt", ios::out);
			if (fout.is_open())
			{
				SaveToFile(fout, Pipes, CSs);
				fout.close();
			}
			break;
		}
		case 7: {
			ifstream fin;
			fin.open("data.txt", ios::in);
			if (fin.is_open()) {
				LoadFromFile(fin, Pipes, CSs);
				fin.close();
			}
			break;
		}
		case 0: {
			cout << "Goodbye" << endl;
			return 0;
		}
		default: {
			cout << "Wrong action, please type (0-7)" << endl;
		}
		}
	}


	return 0;	
}


/*
Что нужно изменить в проекте?
Запись и вывод в один файл

*/