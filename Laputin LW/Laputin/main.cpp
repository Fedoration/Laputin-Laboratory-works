#include <math.h>

#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <map>

#include "Pipe.h"
#include "CS.h"
#include "utils.h"
#include <unordered_map>


using namespace std;

void Print_secondary_menu(string clause1, string clause2);

/*FILTER*/

template<class T, typename T_param>
using Filter = bool(*)(const T & obj, T_param param);

template<class T, typename T_param>
vector<int> FindObjectsByFilter(const unordered_map<int, T>& m, Filter<T, T_param> f, T_param param) {
	
	vector <int> result;
	for (const auto& item : m) {
		if (f(item.second, param))
			result.push_back(item.first);
	}
	return result;
}


template <class T>
bool CheckByID(const T& p, unsigned int param) {
	return p.id == param;
}

bool CheckByIsBroken(const Pipe& p, bool param) {
	return p.is_broken == param;
}

bool CheckByName(const CS& cs, string param) {
	return cs.name == param;
}

bool CheckByPercentOfWorkshops(const CS& cs, double param) {
	double percentage_of_number_workshops = 1.0 - cs.count_running_workshops / (double)cs.count_workshops;
	return (abs(percentage_of_number_workshops - param / 100.0) < 0.0001);
}


//template <class T_vect>
//T_vect& SelectedPipeCS(vector <T_vect>& v) {
//	unsigned int id = GetCorrectNumber("Enter ID: ", 0u, 10000u);
//	for (int i : FindObjectsByFilter<T_vect,unsigned int>(v, CheckByID, id)) {
//		return v[i];
//	}
//}


//template <typename T_id, class T_class>
//T& SelectPipeCS(map <T_id, T_class>& m) {
//  
//}

template<class T>
void DeletePipeCS(unordered_map<int, T>& m) {
	unsigned int id = GetCorrectNumber("Enter ID: ", 0u, 10000u);
	if (m.count(id) == 0) {
		cout << "\nThere is no object with id [" << id << "]" << endl;
	}
	else {
		m.erase(id);
	}
	
}


void EditingPipes(unordered_map<int, Pipe>& m) {

	int answer;
	while (true) {
		
		Print_secondary_menu("All", "Slice");
		answer = GetCorrectNumber("Your choice (0-2): ", 0, 2);
		
		if (answer == 1) {
			for (auto& item : m) {
				item.second.change_Pipe_status();				
			}
			break;
		}
		else if (answer == 2) {
			int begin_slice = GetCorrectNumber("Type start index the slice: ", 0, Pipe::MaxID);
			int end_slice = GetCorrectNumber("Type end index of the slice: ", begin_slice, Pipe::MaxID);
			int n = 0;
			for (auto& item : m) {
				if (item.second.id >= begin_slice && item.second.id <= end_slice) {
					item.second.change_Pipe_status();
				}
				n++;
			}
		}
		else {
			break;
		}
	}
}

vector<int>  CreateBatchCSs(unordered_map<int, CS>& m) {
	int mycapacity = GetCorrectNumber("How much CSs do u want to add: ", 1u, m.size());
	vector<int> result(mycapacity);
	for (auto& i : result) {
		i = GetCorrectNumber("Type CS id: ", 1u, m.size());
	}
	return result;
}



/*Save Pipe/CS*/
void SavePipe(ofstream& fout, const Pipe& p)
{
	fout << p.id << endl << p.length << endl 
		 << p.diameter << endl << p.is_broken << endl;
}

void SaveCS(ofstream& fout, const CS& cs)
{
	fout << cs.id << endl << cs.name << endl << cs.count_workshops
		 << endl << cs.count_running_workshops << endl << cs.efficiency << endl;
}

/*Load Pipe/CS*/
Pipe LoadPipe(ifstream& fin)
{
	Pipe p;
	fin >> p.id >> p.length >> p.diameter >> p.is_broken;
	return p;
}

CS LoadCS(ifstream& fin)
{
	CS cs;
	fin >> cs.id >> cs.name >> cs.count_workshops
		>> cs.count_running_workshops >> cs.efficiency;
	return cs;
}

void SaveToFile(ofstream& fout, const unordered_map<int, Pipe>& Pipes, const unordered_map<int, CS>& CSs)
{
	fout << Pipes.size() << endl;
	fout << CSs.size() << endl;

	if (Pipes.size() != 0) {
		for (const auto& item : Pipes) {
			SavePipe(fout, item.second);
		}
	}

	if (CSs.size() != 0) {
		for (const auto& item : CSs) {
			SaveCS(fout, item.second);
		}
	}

	fout << Pipe::MaxID << endl;
	fout << CS::MaxID << endl;
}


void LoadFromFile(ifstream& fin, unordered_map<int, Pipe>& Pipes, unordered_map<int, CS>& CSs)
{
	int number_of_pipes;
	int number_of_CSs;
	fin >> number_of_pipes;
	fin >> number_of_CSs;
	

	if (number_of_pipes > 0 or number_of_CSs > 0) {
		
		Pipes.clear();
		CSs.clear();

		while (number_of_pipes--) {
			Pipe p = LoadPipe(fin);
			Pipes[p.id] = p;
		}

		CSs.clear();
		while (number_of_CSs--) {
			CS cs = LoadCS(fin);
			CSs[cs.id] = cs;
		}

		fin >> Pipe::MaxID;
		fin >> CS::MaxID;
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
		 << "10. Create Gaz Transport Network" << "\n"
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
	unordered_map<int, Pipe> Pipes;
	unordered_map<int, CS> CSs;
	while (true) {

		PrintMenu();
		int choice = GetCorrectNumber("Your choice (0-10): ", 0, 10);
		cout << '\n';
		switch (choice) 
		{
		case 1: {
			while (true) {
				Print_secondary_menu("Pipe", "CS");
				int choice1 = GetCorrectNumber("Your choice (0-2): ", 0, 2);
				if (choice1 == 1){
					
					int id = Pipe::MaxID;
					Pipes.emplace(id, Pipe());
					cin >> Pipes[id];

				} else if(choice1 == 2){
					
					int id = CS::MaxID;
					CSs.emplace(id, CS());
					cin >> CSs[id];

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
				for (const auto& item: Pipes) {
					cout << item.second << endl;
				}
			}
			else {
				cout << "You haven't added any pipes yet" << endl;
			}

			if (CSs.size() != 0) {
				for (const auto& item: CSs) {
					cout << item.second << endl;
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
						int selected_id = GetCorrectNumber("Type Pipe id: ", 1u, 10000u);
						if (Pipes.count(selected_id) != 0) {
							Pipes[selected_id].change_Pipe_status();
						}
						else {
							cout << "There is no pipe with id: " << selected_id << endl;
						}
					}
					else {
						cout << "You haven't added any pipes yet" << endl;
					}
				}
				else if (choice3 == 2) {
					if (CSs.size() != 0) {
						int selected_id = GetCorrectNumber("Type CS id: ", 1u, 10000u);
						if (CSs.count(selected_id) != 0) {
							CSs[selected_id].edit_CS();
						}
						else {
							cout << "There is no cs with id: " << selected_id << endl;
						}
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
					for (int i : FindObjectsByFilter(Pipes, CheckByID, id_to_find)) {
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
				Print_secondary_menu("Find by name", "Find by percent of idle workshops");
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
					percentage_to_find = GetCorrectNumber("Type percentage(0-100%): ", 0.0, 100.0);
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
		case 10: {
			
			break;
		}
		case 0: {
			cout << "Goodbye" << endl;
			return 0;
		}
		default: {
			cout << "Wrong action, please type (0-10)" << endl;
		}
		}
	}

	return 0;	
}


/*
Что нужно изменить в проекте?
GTN_adjacency - ГТС матрица смежностей
GTN_adjacency
*/