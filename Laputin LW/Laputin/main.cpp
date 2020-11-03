#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include "Pipe.h"
#include "CS.h"
#include "utils.h"

using namespace std;

void Print_secondary_menu(string clause1, string clause2);

/*FILTER*/

template<typename T_param, class T>
using Filter = bool(*)(const T & obj, T_param param);

template<typename T_param, class T>
vector<int> FindObjectsByFilter(const vector<T>& v, Filter<T_param, T> f, T_param param) {
	
	vector <int> res;
	int i = 0;
	for (auto& obj : v) {
		if (f(obj, param))
			res.push_back(i);
		i++;
	}
	return res;
}


bool CheckByPipeID(const Pipe& p, unsigned int param) {
	return p.id == param;
}

bool CheckByIsBroken(const Pipe& p, bool param) {
	return p.is_broken == param;
}

bool CheckByName(const CS& cs, string param) {
	return cs.name == param;
}

bool CheckByPercentOfWorkshops(const CS& cs, double param) {
	double percentage_of_number_workshops = cs.count_running_workshops / (double)cs.count_workshops;
	return percentage_of_number_workshops == param;
}


template <class T_vect>
T_vect& SelectedPipeCS(vector <T_vect>& v) {
	unsigned int id = GetCorrectNumber("Enter ID: ", 0u, 10000u);
	for (int i : FindObjectsByFilter<T_vect, unsigned int>(v, CheckByPipeID, id)) {
		return v[i];
	}
}


//template <class T>
//T& SelectPipeCS(vector <T>& v) {
//	while (true) {
//		unsigned int id = GetCorrectNumber("Enter ID: ", 0u, 10000u);
//		int n = 0;
//		for (auto& obj : v) {
//			if (obj.id == id) {
//				return v[n];
//			}
//			n++;
//		}
//	}
//}

template<class T>
void DeletePipeCS(vector<T>& v) {
	unsigned int id = GetCorrectNumber("Enter ID: ", 0u, 10000u);
	int n = 0;
	bool is_finded = false;
	for (auto& obj : v) {
		if (obj.id == id) {
			v.erase(v.begin() + n);
			is_finded = true;
			break;
		}
		n++;
	}
	if (!(is_finded))
		cout << "\nThere is no object with id [" << id << "]" << endl;
}


void EditingPipes(vector<Pipe>& v) {

	int answer;
	while (true) {
		
		Print_secondary_menu("ALL", "Slice");
		answer = GetCorrectNumber("Your choice (0-2): ", 0, 2);
		
		if (answer == 1) {
			for (auto& p : v) {
				p.change_Pipe_status();				
			}
			break;
		}
		else if (answer == 2) {
			int begin_slice = GetCorrectNumber("Type start index the slice: ", 0, Pipe::MaxID);
			int end_slice = GetCorrectNumber("Type end index of the slice: ", begin_slice, Pipe::MaxID);
			int n = 0;
			for (auto& p : v) {
				if (p.id >= begin_slice && p.id <= end_slice) {
					p.change_Pipe_status();
				}
				n++;
			}
		}
		else {
			break;
		}
	}
}


/*Save Pipe/CS*/
void SavePipe(ofstream& fout, const Pipe& p)
{
	fout << p.length << endl 
		 << p.diameter << endl << p.is_broken << endl;
}

void SaveCS(ofstream& fout, const CS& cs)
{
	fout << cs.name << endl << cs.count_workshops
		 << endl << cs.count_running_workshops << endl << cs.efficiency << endl;
}

/*Load Pipe/CS*/
Pipe LoadPipe(ifstream& fin)
{
	Pipe p;
	fin >> p.length >> p.diameter >> p.is_broken;
	return p;
}

CS LoadCS(ifstream& fin)
{
	CS cs;
	fin >> cs.name >> cs.count_workshops
		>> cs.count_running_workshops >> cs.efficiency;
	return cs;
}

void SaveToFile(ofstream& fout, const vector<Pipe>& Pipes, const vector<CS>& CSs)
{
	fout << Pipes.size() << endl;
	fout << CSs.size() << endl;

	if (Pipes.size() != 0) {
		for (auto p : Pipes) {
			SavePipe(fout, p);
		}
	}

	if (CSs.size() != 0) {
		for (auto cs : CSs) {
			SaveCS(fout, cs);
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
		Pipes.push_back(LoadPipe(fin));
	}

	while (number_of_CSs--) {
		CSs.push_back(LoadCS(fin));
	}
}


void PrintMenu()
{
	cout << "-------------------\n"
		 << "1. Input new Pipe/CS" << "\n"
		 << "2. View all objects" << "\n"
		 << "3. Edit Pipe/CS" << "\n"
		 << "4. Delete Pipe/CS" << "\n"
		 << "5. Pipe Filter" << "\n"
		 << "6. CS Filter" << "\n"
		 << "7. Batch editing of pipes" << "\n"
		 << "8. Save to file" << "\n"
		 << "9. Load from file" << "\n"
		 << "0. Exit" << "\n"
		 << "-------------------" << endl;;
}

void Print_secondary_menu(string clause1, string clause2)
{
	cout << "-------------------\n"
		<< "0. Back" << "\n"
		<< "1. " << clause1 << "\n"
		<< "2. " << clause2 << "\n"
		<< "-------------------" << endl;
}


int main()
{
	vector<Pipe> Pipes;
	vector<CS> CSs;;
	while (true) {

		PrintMenu();
		int choice = GetCorrectNumber("Your choice (0-9): ", 0, 9);
		cout << '\n';
		switch (choice) 
		{
		case 1: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice1 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice1 == 1){
					Pipe pipe;
					cin >> pipe;
					Pipes.push_back(pipe);
				} else if(choice1 == 2){
					CS cs;
					cin >> cs;
					CSs.push_back(cs);
				} else if(choice1 == 0){
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}				
			}
			break;
		}
		case 2: {
			if (Pipes.size() != 0) {
				for (auto& p : Pipes) {
					cout << p << endl;
				}
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}

			if (CSs.size() != 0) {
				for (auto& cs : CSs) {
					cout << cs << endl;
				}
			}
			else {
				cout << "You haven't added any compressor stations yet" << endl;
			}
			break;
		}
		case 3: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice3 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice3 == 1) {
					if (Pipes.size() != 0) {
						SelectedPipeCS(Pipes).change_Pipe_status();
					}
					else {
						cout << "You haven't added any pipes yet" << endl;
					}
				}
				else if (choice3 == 2) {
					if (CSs.size() != 0) {
						SelectedPipeCS(CSs).edit_CS();
					}
					else {
						cout << "You haven't added any compressor stations yet" << endl;
					}
				}
				else if (choice3 == 0) {
					cout << '\n';
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 4: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice1 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice1 == 1) {
					if (Pipes.size() != 0) {
						DeletePipeCS(Pipes);
					}
					else {
						cout << "You haven't added any pipes yet" << endl;
					}
				}
				else if (choice1 == 2) {
					if (CSs.size() != 0) {
						DeletePipeCS(CSs);
					}
					else {
						cout << "You haven't added any compressor stations yet" << endl;
					}
				}
				else if (choice1 == 0) {
					cout << '\n';
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 5: {
			while (true) {
				Print_secondary_menu("Find by id", "Find by status is broken");
				int choice5 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice5 == 1) {
					unsigned int id_to_find;
					id_to_find = GetCorrectNumber("Type id: ", 0u, 10000u);
					for (int i : FindObjectsByFilter(Pipes, CheckByPipeID, id_to_find)) {
						cout << Pipes[i] << endl;
					}
				}
				else if (choice5 == 2) {
					bool is_broken_status_to_find;
					is_broken_status_to_find = GetCorrectNumber("Is broken? [yes-1/no-0]: ", false, true);
					for (int i : FindObjectsByFilter(Pipes, CheckByIsBroken, is_broken_status_to_find)) {
						cout << Pipes[i] << endl;
					}
				}
				else if (choice5 == 0) {
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 6: {
			while (true) {
				Print_secondary_menu("Find by name", "Find by percent of workshops");
				int choice6 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice6 == 1) {
					string name_to_find;
					cout << "Type cs name: ";
					cin.get();
					getline(cin, name_to_find);
					for (int i : FindObjectsByFilter(CSs, CheckByName, name_to_find)) {
						cout << CSs[i] << endl;
					}
				}
				else if (choice6 == 2) {
					double percentage_to_find;
					percentage_to_find = GetCorrectNumber("Type percentage(0-1): ", 0.0, 1.0);
					for (int i : FindObjectsByFilter(CSs, CheckByPercentOfWorkshops, percentage_to_find)) {
						cout << CSs[i] << endl;
					}
				}
				else if (choice6 == 0) {
					break;
				}
				else {
					cout << "Wrong action, please type (0-2)" << endl;
				}
			}
			break;
		}
		case 7: {
			if (Pipes.size() != 0) {
				EditingPipes(Pipes);
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}
			break;
		}
		case 8: {
			ofstream fout;
			fout.open("data.txt", ios::out);
			if (fout.is_open())
			{
				SaveToFile(fout, Pipes, CSs);
				fout.close();
			}
			break;
		}
		case 9: {
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
			cout << "Wrong action, please type (0-9)" << endl;
		}
		}
	}

	return 0;	
}


/*
Что нужно изменить в проекте?

*/